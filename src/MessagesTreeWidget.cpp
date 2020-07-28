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

#include "MessagesTreeWidget.hpp"
#include "Icons.hpp"
#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QFont>

const int TEXT_COLUMN = 0;
const int ICON_COLUMN = 0;
const int ERROR_COLUMN = 1;

MessagesTreeWidget::MessagesTreeWidget(QWidget *parent) :
	QTreeWidget(parent)
{
	setColumnCount( 2 );
	setHeaderLabels({ tr("Name"), tr("Error") });
	setAlternatingRowColors( true );
}

//==================================================================================================

void MessagesTreeWidget::addItem( const QFileInfo &parentDirectory, const QFileInfo &currentEntry )
{
	auto currentTreeItem = new QTreeWidgetItem;
	currentTreeItem->setText( TEXT_COLUMN, currentEntry.fileName() );
	resizeColumnToContents( TEXT_COLUMN );

//	if ( currentEntry.isDir() )
//		currentTreeItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
	items_.insert( currentEntry.filePath(), currentTreeItem );

	auto parentItemIterator = items_.find( parentDirectory.filePath() );
	if ( parentItemIterator != items_.end() )
		( *parentItemIterator )->addChild( currentTreeItem );
	else
		addTopLevelItem( currentTreeItem );

	scrollToItem( currentTreeItem );

	// Is not getting expanded because of: https://bugreports.qt-project.org/browse/QTBUG-28312

	currentTreeItem->setExpanded( true );
}

//==================================================================================================

QTreeWidgetItem *MessagesTreeWidget::findItem( const QFileInfo &fileInfo ) const
{
	auto itemIterator = items_.find( fileInfo.filePath() );
	Q_ASSERT( itemIterator != items_.end() );
	return *itemIterator;
}

//==================================================================================================

void MessagesTreeWidget::visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory )
{
	addItem( parentDirectory, currentDirectory );
}

//==================================================================================================

void MessagesTreeWidget::visitFile(const QFileInfo &parentDirectory, const QFileInfo &currentFile)
{
	addItem( parentDirectory, currentFile );
}

//==================================================================================================

void MessagesTreeWidget::leaveDirectory(const QFileInfo & /* parentDirectory */, const QFileInfo &currentDirectory)
{
	items_.remove( currentDirectory.filePath() );
}

//==================================================================================================

void MessagesTreeWidget::showSkippedEntry( const QFileInfo & /* parent */, const QFileInfo &entry )
{
	findItem( entry )->setIcon( ICON_COLUMN, Icons[ Icons::Clock ]);
}

//==================================================================================================

void MessagesTreeWidget::showRemovedEntry(const QFileInfo & /* parent */, const QFileInfo &entry )
{
	auto item = findItem( entry );

//	item->setIcon( ICON_COLUMN, Icons[ Icons::Trash ]);
	item->setIcon( ICON_COLUMN, Icons[ Icons::Success ]);
}

//==================================================================================================

void MessagesTreeWidget::showRemovingEntryFailed( const QFileInfo & /* parent */, const QFileInfo &entry,
	const QString &errorMessage )
{
	auto item = findItem( entry );
	item->setIcon( ICON_COLUMN, Icons[ Icons::Failure ]);
	item->setText( ERROR_COLUMN, errorMessage );
}
