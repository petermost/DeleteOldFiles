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

#include "MessagesWidget.hpp"
#include <QColor>
#include "Icons.hpp"

class MessagesWidgetItem : public QListWidgetItem {
	public:
		MessagesWidgetItem( const QIcon &icon, const QString &message )
			: QListWidgetItem( icon, message )
		{
		}
};

class InformationWidgetItem : public MessagesWidgetItem {
	public:
		InformationWidgetItem( const QString &message )
			: MessagesWidgetItem( Icons[ Icons::Information ], message )
		{
		}
};

class WarningWidgetItem : public MessagesWidgetItem {
	public:
		WarningWidgetItem( const QString &message )
			: MessagesWidgetItem( Icons[ Icons::Warning ], message )
		{
		}
};

class ErrorWidgetItem : public MessagesWidgetItem {
	public:
		ErrorWidgetItem( const QString &message )
			: MessagesWidgetItem( Icons[ Icons::Error ], message )
		{
		}
};

class DebugWidgetItem : public MessagesWidgetItem {
	public:
		DebugWidgetItem( const QString &message )
			: MessagesWidgetItem( Icons[ Icons::Debug ], message )
		{
		}
};

static void showItem( MessagesWidget *widget, MessagesWidgetItem *item )
{
	widget->addItem( item );
	widget->scrollToItem( item );
}

MessagesWidget::MessagesWidget(QWidget *parent) :
	QListWidget(parent)
{
}

void MessagesWidget::showInformation( const QString &message )
{
	showItem( this, new InformationWidgetItem( message ));
}

void MessagesWidget::showWarning( const QString &message )
{
	showItem( this, new WarningWidgetItem( message ));
}

void MessagesWidget::showError( const QString &message )
{
	showItem( this, new ErrorWidgetItem( message ));
}

void MessagesWidget::showDebug(const QString &message)
{
	showItem( this, new DebugWidgetItem( message ));
}
