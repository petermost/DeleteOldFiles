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

#include "MainWindow.hpp"
#include "Icons.hpp"
#include "MessagesTreeWidget.hpp"
#include "DirectoryTreeRemover.hpp"
#include "DirectoryTreeRemoverThread.hpp"
#include "Settings.hpp"

#include <pera_software/aidkit/qt/widgets/MessagesWidget.hpp>
#include <pera_software/aidkit/containers.hpp>
#include <pera_software/aidkit/qt/core/Strings.hpp>

#include <QDir>
#include <QDate>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileInfo>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>

#include <sstream>

using namespace std;
using namespace pera_software;
using namespace aidkit;
using namespace containers;

using qt::operator<<;

MainWindow::MainWindow(QSharedPointer<Settings> settings, QWidget *parent)
	: PERAMainWindow(settings, parent), settings_(settings)
{
	// Add default menus:

	addFileMenu();
	addHelpMenu();

	// We need to show and therefore create the status bar here so that another thread can show
	// messages. If the thread tries to do that we get a "QObject::setParent: Cannot set parent, new
	// parent is in a different thread" error message!

	statusBar(); // ->showMessage( "" );

	splitter_ = new QSplitter(Qt::Vertical, this);
	messagesTreeWidget_ = new MessagesTreeWidget(splitter_);
	messagesWidget_ = new aidkit::qt::MessagesWidget(splitter_);
	setCentralWidget(splitter_);

	settings_->readSplitterState(splitter_);
}

MainWindow::~MainWindow()
{
	settings_->writeSplitterState(splitter_);
}

void MainWindow::removeOldFiles()
{
	// Show an error message and the usage when the start directory is missing:

	startDirectories_ = settings_->startDirectories();
	if (startDirectories_.length() <= 0) {
		messagesWidget_->showError(tr("Missing start directory name(s)!"));
		messagesWidget_->showInformation(tr("Usage: %1 <start directory name> [<start directory name>]").arg(QApplication::applicationDisplayName()));

		return;
	}
	// Setup the remover:

	QDate today = QDateTime::currentDateTime().date();
	auto removeCondition = [=](const QFileInfo &fileInfo) {
		auto creationDate = fileInfo.birthTime().date();

		return creationDate != today;
	};
	auto remover = make_unique<DirectoryTreeRemover>(settings_->removeMode(), removeCondition);

	// Show the removed files in the tree:

	connect(remover.get(), &DirectoryTreeRemover::visitingDirectory, messagesTreeWidget_, &MessagesTreeWidget::visitDirectory, Qt::BlockingQueuedConnection);
	connect(remover.get(), &DirectoryTreeRemover::visitingFile, messagesTreeWidget_, &MessagesTreeWidget::visitFile, Qt::BlockingQueuedConnection);
	connect(remover.get(), &DirectoryTreeRemover::leavingDirectory, messagesTreeWidget_, &MessagesTreeWidget::leaveDirectory, Qt::BlockingQueuedConnection);

	// Show the status messages from the remover:

	connect(remover.get(), &DirectoryTreeRemover::entryRemoved, this, &MainWindow::showRemovedEntry, Qt::BlockingQueuedConnection);
	connect(remover.get(), &DirectoryTreeRemover::entrySkipped, this, &MainWindow::showSkippedEntry, Qt::BlockingQueuedConnection);
	connect(remover.get(), &DirectoryTreeRemover::removingEntryFailed, this, &MainWindow::showRemovingEntryFailed, Qt::BlockingQueuedConnection);

	// Setup the remover thread:

	auto removerThread = new DirectoryTreeRemoverThread(std::move(remover), startDirectories_ );

	// Show a message when we start/finished removing files:

	connect( removerThread, &QThread::started, this, &MainWindow::showRemovingStarted, Qt::BlockingQueuedConnection );
	connect( removerThread, &QThread::finished, this, &MainWindow::showRemovingFinished, Qt::BlockingQueuedConnection );
	connect( removerThread, &QThread::finished, removerThread, &QObject::deleteLater, Qt::BlockingQueuedConnection );

	removerThread->start();
}

static ostream &operator<<(ostream &output, const QFileInfo &fileInfo)
{
	return output << fileInfo.absoluteFilePath();
}

static QString printStartDirectories(const QFileInfoList &startDirectories)
{
	return QString::fromStdString(join(startDirectories, "\'", ", ", "\'"));
}

void MainWindow::showRemovingStarted()
{
	auto removingStartMessage = tr("Removing old files in directories: %1...").arg(printStartDirectories(startDirectories_));
	messagesWidget_->showInformation(removingStartMessage);
	statusBar()->showMessage(removingStartMessage);
}

void MainWindow::showRemovingFinished()
{
	auto removingFinishedMessage = tr("Finished removing old files in directories: %1.").arg(printStartDirectories(startDirectories_));
	messagesWidget_->showInformation(removingFinishedMessage);
	statusBar()->showMessage(removingFinishedMessage);
}

void MainWindow::showRemovedEntry(const QFileInfo &parent, const QFileInfo &removedEntry)
{
	// messagesWidget_->showInformation( QString( "Removed entry: %1/%2." ).arg( parent.fileName() ).arg( removedEntry.fileName() ));
	messagesTreeWidget_->showRemovedEntry(parent, removedEntry);
}

void MainWindow::showSkippedEntry(const QFileInfo &parent, const QFileInfo &skippedEntry)
{
	messagesWidget_->showWarning(tr("Skipping today's entry: %1/%2.").arg(parent.fileName()).arg(skippedEntry.fileName()));
	messagesTreeWidget_->showSkippedEntry(parent, skippedEntry);
}

void MainWindow::showRemovingEntryFailed(const QFileInfo &parent, const QFileInfo &failedEntry, const QString &errorMessage)
{
	messagesWidget_->showError(tr("Removing entry: %1/%2 failed because: %3!").arg(parent.fileName()).arg(failedEntry.fileName()).arg(errorMessage));
	messagesTreeWidget_->showRemovingEntryFailed(parent, failedEntry, errorMessage);
}
