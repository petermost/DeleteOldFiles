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

#include "MainWindow.hpp"

#include <pera_software/aidkit/qt/widgets/PERAApplication.hpp>

class Settings;

class Application : public pera_software::aidkit::qt::PERAApplication {
	Q_OBJECT
	public:
		static const QString NAME;

		Application(QSharedPointer<Settings> settings, int *argc, char *argv[]);

	Q_SIGNALS:

	public Q_SLOTS:
		void removeOldFiles();

	private:
		MainWindow mainWindow_;
};
