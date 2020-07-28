// Copyright 2014 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the DeleteOldFiles program.
//
// DeleteOldFiles is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DeleteOldFiles is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DeleteOldFiles.  If not, see <http://www.gnu.org/licenses/>.

#include "DirectoryTreeRemover.hpp"
#include "FileRemover.hpp"
#include <QFileInfo>

using namespace std;
using namespace pera_software::aidkit::qt;


DirectoryTreeRemover::DirectoryTreeRemover( const function< bool ( const QFileInfo & )> &removeCondition, QObject *parent )
	: DirectoryVisitor( parent )
{
	removeCondition_ = removeCondition;
}



bool DirectoryTreeRemover::visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory )
{
	Q_EMIT visitingDirectory( parentDirectory, currentDirectory );

	// We don't check the date of the directory, because at least under Linux the creation date seems
	// to get updated whenever a file in the directory has been created. But it still might contain
	// entries which are very well old enough to be deleted.

	return true;
}



bool DirectoryTreeRemover::visitFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile )
{
	Q_EMIT visitingFile( parentDirectory, currentFile );

	// Skip files which have been created today:

	if ( removeCondition_( currentFile )) {
		QString errorMessage;
		if ( fileRemover_.remove( currentFile, &errorMessage )) // || fileRemover_.forceRemove( currentFile, &errorMessage )
			Q_EMIT entryRemoved( parentDirectory, currentFile );
		else
			Q_EMIT removingEntryFailed( parentDirectory, currentFile, errorMessage );
	} else
		Q_EMIT entrySkipped( parentDirectory, currentFile );

	return true;
}



bool DirectoryTreeRemover::leaveDirectory( const QFileInfo &parentDirectory , const QFileInfo &currentDirectory )
{
	QString errorMessage;

	if ( removeCondition_( currentDirectory )) {
		if ( fileRemover_.remove( currentDirectory, &errorMessage ))
			Q_EMIT entryRemoved( parentDirectory, currentDirectory );
		else
			Q_EMIT removingEntryFailed( parentDirectory, currentDirectory, errorMessage );
	} else
		Q_EMIT entrySkipped( parentDirectory, currentDirectory );

	Q_EMIT leavingDirectory( parentDirectory, currentDirectory );

	return true;
}
