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

#include <QTreeWidget>
#include <QMap>

class QFileInfo;
class QTreeWidgetItem;
class QIcon;

class MessagesTreeWidget : public QTreeWidget {
	Q_OBJECT
	public:
		explicit MessagesTreeWidget(QWidget *parent = 0);

		void visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
		void visitFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile );
		void leaveDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );

		void showSkippedEntry( const QFileInfo &parent, const QFileInfo &entry );
		void showRemovedEntry( const QFileInfo &parent, const QFileInfo &entry );
		void showRemovingEntryFailed( const QFileInfo &parent, const QFileInfo &entry, const QString &errorMessage );

	signals:

	public slots:

	private:
		void addItem(const QFileInfo &parentDirectory, const QFileInfo &currentEntry);
		QTreeWidgetItem *findItem( const QFileInfo &fileInfo ) const;

		QMap< QString, QTreeWidgetItem * > items_;
};
