#include "Settings.hpp"

#include <pera_software/aidkit/qt/core/Strings.hpp>

#include <QStringList>

#include <gtest/gtest.h>

using namespace std;
using namespace pera_software::aidkit::qt;

TEST(SettingsTest, testProcess)
{
	Settings settings;
	QStringList arguments = { "DeleteOldFiles"_qs, "--real"_qs, "."_qs, "/tmp/"_qs };

	ASSERT_TRUE(settings.parse(arguments));
	ASSERT_EQ(settings.removeMode(), RemoveMode::Real);
	ASSERT_EQ(settings.startDirectories().length(), 2);
	ASSERT_EQ(settings.startDirectories()[0], "."_qs);
	ASSERT_EQ(settings.startDirectories()[1], "/tmp/"_qs);
}
