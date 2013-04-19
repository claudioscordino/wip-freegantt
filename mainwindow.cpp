#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QAction>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <iostream>

#define VERSION "0.3"

// ==============================================
//		COMMON PARTS
// ==============================================


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	project_(0),
	resourceTable_(0),
	options_(this),
	taskPage_(0),
	ui(new Ui::MainWindow),
	mainToolbar_(0),
	mainTab_(0)
{
	ui->setupUi(this);
	createActions();
	createMainMenu();
	createMainToolbar();
	enableDisableMenu();

	setWindowIcon(QIcon(":/images/gantt-hi.png"));
	updateWindowTitle();
	options_.setHidden(true);
	setWindowModified(false);
}



void MainWindow::createActions()
{
	// File menu:
	newProjectAction_ = new QAction(tr("&New Project"), this);
	newProjectAction_->setIcon(QIcon(":images/document-new.svg"));
	newProjectAction_->setShortcut(QKeySequence::New);
	newProjectAction_->setStatusTip(tr("Create a new project"));
	connect(newProjectAction_, SIGNAL(triggered()), this, SLOT(newProject()));

	openProjectAction_ = new QAction(tr("&Open Project"), this);
	openProjectAction_->setIcon(QIcon(":images/document-open.svg"));
	openProjectAction_->setShortcut(QKeySequence::Open);
	openProjectAction_->setStatusTip(tr("Open a new project"));
	connect(openProjectAction_, SIGNAL(triggered()), this, SLOT(openProject()));

	saveProjectAction_ = new QAction(tr("&Save Project"), this);
	saveProjectAction_->setIcon(QIcon(":images/document-save.svg"));
	saveProjectAction_->setShortcut(QKeySequence::Save);
	saveProjectAction_->setStatusTip(tr("Save the current project"));
	connect(saveProjectAction_, SIGNAL(triggered()), this, SLOT(saveProject()));

	saveAsProjectAction_ = new QAction(tr("&Save Project as"), this);
	saveAsProjectAction_->setIcon(QIcon(":images/document-save-as.svg"));
	saveAsProjectAction_->setShortcut(QKeySequence::SaveAs);
	saveAsProjectAction_->setStatusTip(tr("Save the current project with a new name"));
	connect(saveAsProjectAction_, SIGNAL(triggered()), this, SLOT(saveProjectAs()));

	for (int i = 0; i < maxRecentFiles; ++i){
		recentFilesActions_[i] = new QAction(this);
		recentFilesActions_[i]->setVisible(false);
		recentFilesActions_[i]->setIcon(QIcon(":images/document-open-recent.png"));
		recentFilesActions_[i]->setStatusTip(tr("Open a recent project"));
		connect(recentFilesActions_[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
	}

	exportProjectAction_ = new QAction(tr("&Export project"), this);
	exportProjectAction_->setIcon(QIcon(":images/document-save.svg"));
	exportProjectAction_->setStatusTip(tr("Export the current project"));

	printProjectAction_ = new QAction(tr("&Print project"), this);
	printProjectAction_->setIcon(QIcon(":images/printer.png"));
	printProjectAction_->setShortcut(QKeySequence::Print);
	printProjectAction_->setStatusTip(tr("Print the current project"));

	optionsPanelAction_ = new QAction(tr("&Options"), this);
	optionsPanelAction_->setShortcut(QKeySequence::Close);
	optionsPanelAction_->setIcon(QIcon(":images/preferences-desktop.svg"));
	optionsPanelAction_->setStatusTip(tr("Set options"));
	connect(optionsPanelAction_, SIGNAL(triggered()), this, SLOT(showOptions()));

	exitAction_ = new QAction(tr("&Exit"), this);
	exitAction_->setIcon(QIcon(":images/exit.svg"));
	exitAction_->setShortcut(QKeySequence::Close);
	exitAction_->setStatusTip(tr("Exit"));
	connect(exitAction_, SIGNAL(triggered()), this, SLOT(exitProgram()));

	newTaskAction_ = new QAction(tr("&New Task"), this);
	newTaskAction_->setIcon(QIcon(":images/add.png"));
	newTaskAction_->setStatusTip(tr("Add a new task"));

	deleteTaskAction_ = new QAction(tr("&Delete Task"), this);
	deleteTaskAction_->setIcon(QIcon(":images/list-remove.svg"));
	deleteTaskAction_->setStatusTip(tr("Delete the selected task"));

	indentTaskAction_ = new QAction(tr("&Indent Task"), this);
	indentTaskAction_->setIcon(QIcon(":images/go-next.png"));
	indentTaskAction_->setStatusTip(tr("Indent the selected task"));

	deindentTaskAction_ = new QAction(tr("&Deindent Task"), this);
	deindentTaskAction_->setIcon(QIcon(":images/go-previous.png"));
	deindentTaskAction_->setStatusTip(tr("Deindent the selected task"));

	newResourceAction_ = new QAction(tr("&New Resource"), this);
	newResourceAction_->setIcon(QIcon(":images/im-user.png"));
	newResourceAction_->setStatusTip(tr("Add a new resource/group"));

	deleteResourceAction_ = new QAction(tr("&Delete resource "), this);
	deleteResourceAction_->setIcon(QIcon(":images/im-kick-user.png"));
	deleteResourceAction_->setStatusTip(tr("Delete the selected resource/group"));

	indentResourceAction_ = new QAction(tr("&Group Resource"), this);
	indentResourceAction_->setIcon(QIcon(":images/go-next.png"));
	indentResourceAction_->setStatusTip(tr("Group resources"));

	deindentResourceAction_= new QAction(tr("&Ungroup Resource"), this);
	deindentResourceAction_->setIcon(QIcon(":images/go-previous.png"));
	deindentResourceAction_->setStatusTip(tr("Ungroup resources"));

	viewResourceAction_ = new QAction(tr("&View Resources"), this);
	viewResourceAction_->setIcon(QIcon(":images/im-user-offline.png"));
	viewResourceAction_->setStatusTip(tr("View current resources"));
	connect(viewResourceAction_, SIGNAL(triggered()), this, SLOT(switchToResourceTab()));

	viewTaskAction_ = new QAction(tr("&View Tasks"), this);
	viewTaskAction_->setIcon(QIcon(":images/showGrid.png"));
	viewTaskAction_->setStatusTip(tr("View current tasks"));
	connect(viewTaskAction_, SIGNAL(triggered()), this, SLOT(switchToTaskTab()));

	aboutAction_ = new QAction(tr("&About"), this);
	aboutAction_->setIcon(QIcon(":images/statusWindow.png"));
	aboutAction_->setStatusTip(tr("About FreeGantt"));
	connect(aboutAction_, SIGNAL(triggered()), this, SLOT(aboutProgram()));

	aboutQtAction_ = new QAction(tr("About &Qt"), this);
	aboutQtAction_->setStatusTip(tr("Show information about Qt"));
	aboutQtAction_->setIcon(QIcon(":images/qt_icon80.png"));
	connect(aboutQtAction_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	switchTabAction_ = new QAction(tr("&Switch Tab"), this);
	switchTabAction_->setShortcut(tr("Ctrl+Tab"));
	connect(switchTabAction_, SIGNAL(triggered()), this, SLOT(switchTab()));
}


void MainWindow::showOptions()
{
	options_.setVisible(true);
}

// 0 = Tasks; 1 = Resources
void MainWindow::switchToTab(int tab_nb)
{
	if (tab_nb == 0)		
		switchToTaskTab();
	else
		switchToResourceTab();
}

void MainWindow::switchTab()
{
	if (mainTab_->currentIndex() == 0)
		switchToTab(1);
	else
		switchToTab(0);
}


void MainWindow::createMainMenu()
{
	// File menu:
	fileMenu_ = menuBar()->addMenu((tr("&File")));
	fileMenu_->addAction(newProjectAction_);
	fileMenu_->addAction(openProjectAction_);
	fileMenu_->addAction(saveProjectAction_);
	fileMenu_->addAction(saveAsProjectAction_);

	// Recent files:
	separatorAction_ = fileMenu_->addSeparator();
	for (int i = 0; i < maxRecentFiles; ++i)
		fileMenu_->addAction(recentFilesActions_[i]);
	fileMenu_->addSeparator();

	fileMenu_->addAction(exportProjectAction_);
	fileMenu_->addAction(printProjectAction_);
	fileMenu_->addSeparator();
	fileMenu_->addAction(exitAction_);

	// Edit menu:
	editMenu_ = menuBar()->addMenu((tr("&Edit")));
	editMenu_->addAction(newTaskAction_);
	editMenu_->addAction(deleteTaskAction_);
	editMenu_->addAction(indentTaskAction_);
	editMenu_->addAction(deindentTaskAction_);
	editMenu_->addSeparator();
	editMenu_->addAction(newResourceAction_);
	editMenu_->addAction(deleteResourceAction_);
	editMenu_->addAction(indentResourceAction_);
	editMenu_->addAction(deindentResourceAction_);

	// View menu:
	viewMenu_ = menuBar()->addMenu((tr("&View")));
	viewMenu_->addAction(viewTaskAction_);
	viewMenu_->addAction(viewResourceAction_);
	viewMenu_->addSeparator();
	viewMenu_->addAction(optionsPanelAction_);

	menuBar()->addSeparator();

	// About menu:
	aboutMenu_ = menuBar()->addMenu((tr("&About")));
	aboutMenu_->addAction(aboutAction_);
	aboutMenu_->addAction(aboutQtAction_);
}



void MainWindow::enableDisableMenu()
{
	if (!project_.isNull()) {
		editMenu_->setEnabled(true);
		viewMenu_->setEnabled(true);
		saveProjectAction_->setEnabled(true);
		saveAsProjectAction_->setEnabled(true);
		exportProjectAction_->setEnabled(true);
	} else {
		editMenu_->setEnabled(false);
		viewMenu_->setEnabled(false);
		saveProjectAction_->setEnabled(false);
		saveAsProjectAction_->setEnabled(false);
		exportProjectAction_->setEnabled(false);
	}
}

void MainWindow::createMainToolbar()
{
	mainToolbar_ = addToolBar(tr("&Main commands"));
	mainToolbar_->addAction(newProjectAction_);
	mainToolbar_->addAction(openProjectAction_);
	mainToolbar_->addAction(saveProjectAction_);
}

void MainWindow::openProject()
{
	if (okToDiscardCurrentProject() > 0) {
		QString fileName = QFileDialog::getOpenFileName(this,
								tr("Open saved projects"), ".",
								tr("FreeGantt files (*.fgt)"));
		if (!fileName.isEmpty()){
			project_->load(fileName.toStdString());
			addToRecentFiles(fileName);
			updateWindowTitle();
			setWindowModified(false);
		}
	}
}

bool MainWindow::saveProject()
{
	if (project_.isNull())
		return false;

	if (project_->getFileName() == "")
		return saveProjectAs();
	else
		return project_->save();
}

bool MainWindow::saveProjectAs()
{
	if (project_.isNull())
		return false;

	QString fileName = QFileDialog::getSaveFileName(this,
							 tr ("Save project as"), ".",
							 tr ("FreeGantt files (*.fgt)"));
	if (fileName.isEmpty())
		return false;

	if (project_->save()){
		project_->setFileName(fileName.toStdString());
		addToRecentFiles(fileName);
		updateWindowTitle();
		setWindowModified(false);
	}
	return true;
}

void MainWindow::updateWindowTitle()
{
	if (project_ == 0)
		setWindowTitle("FreeGantt " VERSION);
	else if (project_->getFileName() == "")
		setWindowTitle("FreeGantt - Untitled [*]");
	else
		setWindowTitle("FreeGantt - " +
		     strippedFileName(QString(project_->getFileName().c_str())) +
		     " [*]");
}

void MainWindow::addToRecentFiles(const QString& filename)
{
	if (!filename.isEmpty()){
		std::cerr << "Fase 2" << std::endl;
		recentFiles_.removeAll(filename);
		std::cerr << "Fase 3" << std::endl;
		recentFiles_.prepend(filename);
		std::cerr << "Fase 4" << std::endl;
		updateRecentFileActions();
	}
}

void MainWindow::updateRecentFileActions()
{
	QMutableStringListIterator i(recentFiles_);
	while (i.hasNext()){
		if (!QFile::exists(i.next()))
			i.remove();
	}

	for (int j = 0; j < maxRecentFiles; ++j){
		if (j < recentFiles_.count()){
			QString text = tr("&%1 %2")
					.arg(j + 1)
					.arg(strippedFileName(recentFiles_[j]));
			recentFilesActions_[j]->setText(text);
			recentFilesActions_[j]->setData(recentFiles_[j]);
			recentFilesActions_[j]->setVisible(true);
		} else {
			recentFilesActions_[j]->setVisible(false);
		}
	}
	separatorAction_->setVisible(!recentFiles_.isEmpty());
}


QString MainWindow::strippedFileName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).baseName();
}

void MainWindow::openRecentFile()
{
	if (okToDiscardCurrentProject() > 0) {
		QAction* action = qobject_cast<QAction*> (sender());
		if (action){
			project_->load(action->data().toString().toStdString());
			updateWindowTitle();
			setWindowModified(false);
		}
	}
}


void MainWindow::newProject()
{
	switch (okToDiscardCurrentProject()){
	case 1:
		saveProject();
		delete mainTab_;
	case 2:
		if (project_.isNull())
			std::cerr << "1. Project == 0" << std::endl;
		project_.reset(new Project());
		if (project_.isNull())
			std::cerr << "2. Project == 0" << std::endl;

		mainTab_ = new QTabWidget(this);
		connect(mainTab_, SIGNAL(currentChanged(int)), this, SLOT(switchToTab(int)));

		// These two calls need mainTab_ already allocated:
		createTaskTab();
		createResourceTab();

		enableDisableMenu();

		updateWindowTitle();
		statusBar()->showMessage(tr("Project created."), 2000);
		setWindowModified(false);
	}
	switchToTaskTab();
}


// 0 = cancel
// 1 = project existing and saved
// 2 = project non existing
int MainWindow::okToDiscardCurrentProject()
{
	if (!project_.isNull()) {
		int ret = QMessageBox::warning(this, tr("Exit"),
					       tr("The project has been modifed.\n"
						  "Do you want to save your changes ?"),
					       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (ret == QMessageBox::Yes)
			return 1;
		else if (ret == QMessageBox::Cancel)
			return 0;
	}
	return 2;
}

void MainWindow::exitProgram()
{
	if (okToDiscardCurrentProject() != 0)
		exit(1);
}


void MainWindow::aboutProgram()
{
	QMessageBox::about(this, tr("About FreeGantt"),
			   "<h2>FreeGantt " VERSION "</h2>"
			   "<p>Copyright &copy; 2013 Claudio Scordino</p>"
			   "<p> FreeGantt is a small application to draw "
			   "Gantt diagrams.</p>");
}


MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateOptions()
{
	taskPage_->setFirstDayOfWeek(options_.getFirstDayOfWeek());
}

// ==============================================
//		TASKS
// ==============================================


void MainWindow::createTaskTab()
{
	taskPage_.reset(new TaskPage(project_.data(), this));

	// Tasks:
	connect(newTaskAction_, SIGNAL(triggered()), taskPage_.data(), SLOT(newItem()));
	connect(deleteTaskAction_, SIGNAL(triggered()), taskPage_.data(), SLOT(removeItem()));
	connect(indentTaskAction_, SIGNAL(triggered()), taskPage_.data(), SLOT(indentItem()));
	connect(deindentTaskAction_, SIGNAL(triggered()), taskPage_.data(), SLOT(deindentItem()));

	// Add the widget to the tab:
	mainTab_->addTab(taskPage_.data(), tr("Tasks"));
	setCentralWidget(mainTab_);
}


void MainWindow::switchToTaskTab()
{
	mainTab_->setCurrentIndex(0);
	newTaskAction_->setEnabled(true);
	deleteTaskAction_->setEnabled(true);
	indentTaskAction_->setEnabled(true);
	deindentTaskAction_->setEnabled(true);
	newResourceAction_->setEnabled(false);
	deleteResourceAction_->setEnabled(false);
	viewResourceAction_->setEnabled(true);
	viewTaskAction_->setEnabled(false);
	indentResourceAction_->setEnabled(false);
	deindentResourceAction_->setEnabled(false);
}







// ==============================================
//		RESOURCES
// ==============================================



void MainWindow::switchToResourceTab()
{
	mainTab_->setCurrentIndex(1);
	newTaskAction_->setEnabled(false);
	deleteTaskAction_->setEnabled(false);
	indentTaskAction_->setEnabled(false);
	deindentTaskAction_->setEnabled(false);
	newResourceAction_->setEnabled(true);
	deleteResourceAction_->setEnabled(true);
	viewResourceAction_->setEnabled(false);
	viewTaskAction_->setEnabled(true);
	indentResourceAction_->setEnabled(true);
	deindentResourceAction_->setEnabled(true);

}


void MainWindow::createResourceTab()
{
	resourcePage_.reset(new ResourcePage(project_.data(), this));

	// Resources:
	connect(newResourceAction_, SIGNAL(triggered()), resourcePage_.data(), SLOT(newItem()));
	connect(deleteResourceAction_, SIGNAL(triggered()), resourcePage_.data(), SLOT(removeItem()));
	connect(indentResourceAction_, SIGNAL(triggered()), resourcePage_.data(), SLOT(indentItem()));
	connect(deindentResourceAction_, SIGNAL(triggered()), resourcePage_.data(), SLOT(deindentItem()));

	// Add the widget to the tab:
	mainTab_->addTab(resourcePage_.data(), tr("Resources"));
	setCentralWidget(mainTab_);
}















