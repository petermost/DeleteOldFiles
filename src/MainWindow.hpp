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

#include <pera_software/aidkit/qt/widgets/PERAMainWindow.hpp>
#include <pera_software/aidkit/qt/widgets/ForwardDeclarations.hpp>
#include <QFileInfoList>

class MessagesTreeWidget;
class QSettings;
class QTreeWidget;
class QFileInfo;
class QSplitter;

class MainWindow : public pera_software::aidkit::qt::PERAMainWindow {
	Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);

		virtual void readSettings( QSettings *settings ) noexcept override;
		virtual void writeSettings( QSettings *settings ) const noexcept override;

	public Q_SLOTS:
		void removeOldFiles( const QStringList &arguments );
		void removeOldFiles(const QFileInfoList &startDirectories );

	private:
		void showRemovingStarted();
		void showRemovingFinished();

		void showRemovedEntry( const QFileInfo &parent, const QFileInfo &removedEntry );
		void showSkippedEntry( const QFileInfo &parent, const QFileInfo &skippedEntry );
		void showRemovingEntryFailed( const QFileInfo &parent, const QFileInfo &failedEntry, const QString &errorMessage );

		QFileInfoList startDirectories_;
		QSplitter *splitter_;
		MessagesTreeWidget *messagesTreeWidget_;
		pera_software::aidkit::qt::MessagesWidget *messagesWidget_;
};
