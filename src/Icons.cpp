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

#include "Icons.hpp"
#include <QIcon>
#include <QFile>

const QString Icons::Success(QStringLiteral(":/Images/dialog-ok-apply-16x16.png"));
const QString Icons::Failure(QStringLiteral(":/Images/dialog-cancel-16x16.png"));

const QString Icons::Clock(QStringLiteral(":/Images/clock-16x16.png"));
//const QString Icons::Trash( ":/Images/trash-empty-16x16.png" );
const QString Icons::Trash(QStringLiteral(":/Images/user-trash-16x16.png"));
const QString Icons::Bug(QStringLiteral(":/Images/script-error-16x16.png"));

Icons::Icons()
{
	Q_INIT_RESOURCE(Images);
}

Icons::~Icons()
{
	Q_CLEANUP_RESOURCE(Images);
}

const QIcon &Icons::operator[](const QString &iconName)
{
	auto it = icons_.find(iconName);
	if (it == icons_.end()) {
		it = icons_.insert(iconName, QIcon(iconName));
	}
	return it.value();
}

class Icons Icons;
