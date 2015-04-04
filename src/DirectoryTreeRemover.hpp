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

#pragma once

#include "FileRemover.hpp"
#include <pera_software/aidkit/qt/core/DirectoryGuide.hpp>
#include <functional>

class QFileInfo;

class DirectoryTreeRemover : public pera_software::aidkit::qt::DirectoryVisitor {
	Q_OBJECT
	public:
		DirectoryTreeRemover( const std::function< bool ( const QFileInfo & )> &removeCondition, QObject *parent = nullptr );

	signals:
		void visitingDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
		void visitingFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile );
		void leavingDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );

		void entrySkipped( const QFileInfo &parent, const QFileInfo &entry );
		void entryRemoved( const QFileInfo &parent, const QFileInfo &entry );
		void removingEntryFailed( const QFileInfo &parent, const QFileInfo &entry, const QString &errorMessage );

	protected:
		virtual bool visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory ) override;
		virtual bool visitFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile ) override;
		virtual bool leaveDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory ) override;

	private:
		std::function< bool ( const QFileInfo & )> removeCondition_;
		FileRemover fileRemover_;

};
