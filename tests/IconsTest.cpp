#include "Icons.hpp"
#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <pera_software/aidkit/compiler.hpp>
#include <QIcon>
#include <QFile>
#include <gtest/gtest.h>

AIDKIT_PRAGMA_GCC_WARNING_DISABLE(shadow-uncaptured-local)

TEST(IconsTest, testArrayOperator)
{
	QString iconNames[] = {
		Icons::Success,
		Icons::Failure,
		Icons::Clock,
		Icons::Trash,
		Icons::Bug
	};

	for (auto iconName : iconNames) {
		auto icon = Icons[iconName];
		ASSERT_FALSE(icon.isNull());
		ASSERT_PRED1([](const QString &iconName) { return QFile::exists(iconName); }, iconName);
	}
}
