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

#include "Application.hpp"
#include "MainWindow.hpp"
#include <QSettings>

using namespace pera_software::company::qt;

const QString Application::NAME(QStringLiteral("DeleteOldFiles"));

Application::Application( int &argc, char *argv[] )
	: PERAApplication(NAME, argc, argv)
{
	mainWindow_ = new MainWindow();
	mainWindow_->show();
}

void Application::readSettings( QSettings *settings ) noexcept {
	mainWindow_->readSettings( settings );
}

void Application::writeSettings( QSettings *settings ) const noexcept {
	mainWindow_->writeSettings( settings );
}



void Application::removeOldFiles()
{
	QStringList startDirectories(arguments().mid(1));
	mainWindow_->removeOldFiles(startDirectories);
}
