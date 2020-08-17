#include "Icons.hpp"
#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <pera_software/aidkit/compiler.hpp>
#include <pera_software/aidkit/qt/TestFixture.hpp>
#include <QIcon>
#include <QFile>
#include <gtest/gtest.h>

AIDKIT_GCC_DISABLE_WARNING(shadow-uncaptured-local)
AIDKIT_GCC_DISABLE_WARNING(weak-vtables)

using namespace pera_software::aidkit;

class IconsTest : public qt::TestFixture {
};

TEST_F(IconsTest, testArrayOperator)
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
