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

#include "FileRemover.hpp"
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>

static bool removeFile(const QString &filePath, QString *errorMessage)
{
	QFile file(filePath);
	if (file.remove())
		return true;
	else {
		*errorMessage = file.errorString()
				.remove(QChar::SpecialCharacter::LineFeed)
				.remove(QChar::SpecialCharacter::CarriageReturn);
		return false;
	}
}

static bool removeDirectory(const QString &filePath, QString *errorMessage)
{
	QDir dir;
	if (dir.rmdir(filePath))
		return true;
	else {
		*errorMessage = FileRemover::tr("Unknown error");
		return false;
	}
}

FileRemover::FileRemover(RemoveMode mode)
	: mode_(mode)
{
}

bool FileRemover::remove(const QFileInfo &fileInfo, QString *errorMessage)
{
	if (mode_ == RemoveMode::Real) {
		QString filePath = fileInfo.filePath();
		if (fileInfo.isFile())
			return removeFile(filePath, errorMessage);
		else if (fileInfo.isDir())
			return removeDirectory(filePath, errorMessage);
		else
			return false;
	} else {
		return true;
	}
}

//bool FileRemover::forceRemove(const QFileInfo &fileInfo, QString *errorMessage)
//{
//	// If the file is readonly then try to make it writable:

//	QFile::Permissions permissions = fileInfo.permissions();
//	if (( permissions & QFile::WriteUser ) == 0 ) {
//		if ( fileInfo.permission( permissions | QFile::WriteUser ))
//			return remove( fileInfo, errorMessage );
//		else {
//			*errorMessage = "File is readonly and setting the permission to 'WriteUser' failed!";
//			return false;
//		}
//	} else {
//		*errorMessage = "Unknown reas";
//		return false;
//	}
//}
