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


Application::Application( int &argc, char *argv[] )
	: PERA::Application( argc, argv )
{
	mainWindow_ = new MainWindow();
	mainWindow_->show();
}



void Application::removeOldFiles()
{
	mainWindow_->removeOldFiles( arguments() );
}