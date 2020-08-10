#include "Settings.hpp"
#include "Application.hpp"

#include <pera_software/aidkit/qt/core/Strings.hpp>

#include <QStringList>
#include <QCommandLineParser>
#include <QSplitter>


using namespace pera_software::aidkit::qt;

const QString STATE_KEY(QStringLiteral("state"));


Settings::Settings()
	: PERASettings(::Application::NAME)
{
}

bool Settings::parse(const QStringList &arguments)
{
	QCommandLineParser parser;
	// parser.addHelpOption();
	// parser.addVersionOption();
	parser.addPositionalArgument("start directory"_qs, ::Application::translate("Settings", "Start directory name(s)"));

	QCommandLineOption realOption("real"_qs, "Delete files for real"_qs);
	parser.addOption(realOption);

	bool success;
	if ((success = parser.parse(arguments))) {
		if (parser.isSet(realOption)) {
			removeMode_ = RemoveMode::Real;
		}
		for (auto argument : parser.positionalArguments()) {
			startDirectories_.append(argument);
		}
	}
	return success;
}

void Settings::writeSplitterState(const QSplitter *splitter)
{
	iniFile_.beginGroup(makeGroupName(splitter));
		iniFile_.setValue(STATE_KEY, splitter->saveState());
	iniFile_.endGroup();
}

void Settings::readSplitterState(QSplitter *splitter)
{
	iniFile_.beginGroup(makeGroupName(splitter));
		splitter->restoreState(iniFile_.value(STATE_KEY).toByteArray());
	iniFile_.endGroup();
}

RemoveMode Settings::removeMode() const
{
	return removeMode_;
}

QFileInfoList Settings::startDirectories() const
{
	return startDirectories_;
}

