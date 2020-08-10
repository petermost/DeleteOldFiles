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
#include <functional>
#include <QObject>

class QFileInfo;

class DirectoryTreeRemover : public QObject {
	Q_OBJECT
	public:
		DirectoryTreeRemover(RemoveMode removeMode, std::function<bool(const QFileInfo &)> removeCondition, QObject *parent = nullptr);

	Q_SIGNALS:
		void visitingDirectory(const QFileInfo &parentDirectory, const QFileInfo &currentDirectory);
		void visitingFile(const QFileInfo &parentDirectory, const QFileInfo &currentFile);
		void leavingDirectory(const QFileInfo &parentDirectory, const QFileInfo &currentDirectory);

		void entrySkipped(const QFileInfo &parent, const QFileInfo &entry);
		void entryRemoved(const QFileInfo &parent, const QFileInfo &entry);
		void removingEntryFailed(const QFileInfo &parent, const QFileInfo &entry, const QString &errorMessage);

	public Q_SLOTS:
		void onDirectoryVisited(const QFileInfo &parentDirectory, const QFileInfo &currentDirectory, bool *stop);
		void onFileVisited(const QFileInfo &parentDirectory, const QFileInfo &currentFile, bool *stop);
		void onDirectoryLeft(const QFileInfo &parentDirectory, const QFileInfo &currentDirectory, bool *stop);

	private:
		FileRemover fileRemover_;
		std::function<bool(const QFileInfo &)> removeCondition_;
};

namespace pera_software::aidkit::qt {
	class DirectoryGuide;
}

void connectDirectoryGuideSignals(const pera_software::aidkit::qt::DirectoryGuide &guide, DirectoryTreeRemover *remover);
