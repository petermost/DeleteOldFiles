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

#include "PERA_MainWindow.hpp"
#include "PERA_AboutDialog.hpp"
#include "Icons.hpp"
#include <QApplication>
#include <QSettings>

namespace PERA {

using namespace PERA;

const QString GROUP_NAME( "MainWindow" );
const QString SIZE_KEY( "size" );
const QString POSITION_KEY( "position" );

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle( QString( "%1 - (c) by %2 - %3" ).arg( QApplication::applicationName() )
		.arg( QApplication::organizationName() ).arg( QApplication::organizationDomain() ));

	setWindowIcon( Icons[ Icons::PERAIcon ] );
}



void MainWindow::showEvent( QShowEvent *showEvent )
{
	QSettings settings;
	readSettings( &settings );

	QMainWindow::showEvent( showEvent );
}



void MainWindow::closeEvent( QCloseEvent *closeEvent )
{
	QSettings settings;
	writeSettings( &settings );

	QMainWindow::closeEvent( closeEvent );
}



void MainWindow::readSettings( QSettings *settings )
{
	settings->beginGroup( GROUP_NAME );
		resize( settings->value( SIZE_KEY, size() ).toSize() );
		move( settings->value( POSITION_KEY, pos() ).toPoint() );
		doReadSettings( settings );
	settings->endGroup();
}



void MainWindow::writeSettings( QSettings *settings ) const
{
	settings->beginGroup( GROUP_NAME );
		settings->setValue( SIZE_KEY, size() );
		settings->setValue( POSITION_KEY, pos() );
		doWriteSettings( settings );
	settings->endGroup();
}

void MainWindow::aboutPERA()
{
	AboutDialog aboutPERADialog;

	aboutPERADialog.exec();
}


}
