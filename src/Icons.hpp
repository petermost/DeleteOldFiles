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

#include <QHash>

class QIcon;
class QString;

class Icons final {
	public:
		static const QString Success;
		static const QString Failure;

		static const QString Clock;
		static const QString Trash;
		static const QString Bug;

		Icons();
		~Icons();

		const QIcon &operator[](const QString &iconName);

	private:
		QHash<QString, QIcon> icons_;
};

extern class Icons Icons;
