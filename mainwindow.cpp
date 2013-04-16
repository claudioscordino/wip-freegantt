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
	taskTable_(0),
	resourceTable_(0),
	ui(new Ui::MainWindow),
	mainTab_(0),
	calendarTaskId_(0)
{
	ui->setupUi(this);
	createActions();
	createMainMenu();
	createMainToolbar();
	enableDisableMenu();

	setWindowIcon(QIcon(":/images/gantt-hi.png"));
	setWindowTitle("FreeGantt " VERSION);
	calendar_.setHidden(true);


	// Tasks:
	connect(newTaskAction_, SIGNAL(triggered()), this, SLOT(newTaskSlot()));
	connect(deleteTaskAction_, SIGNAL(triggered()), this, SLOT(removeTaskSlot()));
	connect(indentTaskAction_, SIGNAL(triggered()), this, SLOT(indentTaskSlot()));
	connect(deindentTaskAction_, SIGNAL(triggered()), this, SLOT(deindentTaskSlot()));

	// Resources:
	connect(newResourceAction_, SIGNAL(triggered()), this, SLOT(newResourceSlot()));
	connect(deleteResourceAction_, SIGNAL(triggered()), this, SLOT(removeResourceSlot()));
	connect(indentResourceAction_, SIGNAL(triggered()), this, SLOT(indentResourceSlot()));
	connect(deindentResourceAction_, SIGNAL(triggered()), this, SLOT(deindentResourceSlot()));

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


	recentProjectsAction_ = new QAction(tr("&Open recent projects"), this);
	recentProjectsAction_->setIcon(QIcon(":images/document-open-recent.png"));
	recentProjectsAction_->setStatusTip(tr("Open a recent project"));

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
	fileMenu_->addAction(recentProjectsAction_);
	fileMenu_->addAction(saveProjectAction_);
	fileMenu_->addAction(saveAsProjectAction_);
	fileMenu_->addAction(exportProjectAction_);
	fileMenu_->addAction(printProjectAction_);
	fileMenu_->addSeparator();
	fileMenu_->addAction(optionsPanelAction_);
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

	menuBar()->addSeparator();

	// About menu:
	aboutMenu_ = menuBar()->addMenu((tr("&About")));
	aboutMenu_->addAction(aboutAction_);
	aboutMenu_->addAction(aboutQtAction_);
}



void MainWindow::enableDisableMenu()
{
	if (project_ != 0) {
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
			setWindowModified(false);
		}
	}

}

bool MainWindow::saveProject()
{
	if (project_.isNull())
		return project_->save();

	if (project_->getFileName() == "")
		return saveProjectAs();
}

bool MainWindow::saveProjectAs()
{
	if (project_.isNull())
		return false;

	QString file_name = QFileDialog::getSaveFileName(this,
							 tr ("Save project as"), ".",
							 tr ("FreeGantt files (*.fgt)"));
	if (file_name.isEmpty())
		return false;
	project_->setFileName(file_name.toStdString());
	return project_->save();
}

void MainWindow::newProject()
{
	switch (okToDiscardCurrentProject()){
	case 1:
		saveProject();
		delete mainTab_;
	case 2:
		project_.reset(new Project("Untitled"));
		mainTab_ = new QTabWidget(this);
		connect(mainTab_, SIGNAL(currentChanged(int)), this, SLOT(switchToTab(int)));

		enableDisableMenu();
		createTaskTab();
		createResourceTab();
		setWindowTitle("FreeGantt " + QString(VERSION) + " - " + QString(project_->getName().c_str()) + " [*]");
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



// ==============================================
//		TASKS
// ==============================================


void MainWindow::createTaskTab()
{
	// Create left table:
	taskTable_ = new QTableWidget(0, 4);
	taskTable_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	taskTable_->setColumnHidden(0, true);
	connect(taskTable_, SIGNAL(cellChanged(int, int)), this, SLOT(taskValueChanged(int, int)));
	connect(taskTable_, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(taskValueClicked(int, int)));
	QStringList labels;
	labels.append("Id");
	labels.append("Name");
	labels.append("Begin");
	labels.append("Duration");
	taskTable_->setHorizontalHeaderLabels(labels);
	taskTable_->verticalHeader()->setVisible(false);
	taskTable_->setMinimumWidth(230);
	taskTable_->setMaximumWidth(230);
	taskTable_->setSelectionBehavior(QAbstractItemView::SelectRows);

	// Set width of the three columns:
	taskTable_->setColumnWidth(0, 50);
	taskTable_->setColumnWidth(1, 80);
	taskTable_->setColumnWidth(2, 80);
	taskTable_->setColumnWidth(3, 70);

	// Create left scene:
	QGraphicsScene* taskScene = new QGraphicsScene(this);
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(0, 0, 100, 10);
	taskScene->addItem(rect);
	QGraphicsView* taskView = new QGraphicsView(taskScene);
	taskView->show();

	QToolBar* taskToolbar = addToolBar(tr("&Task toolbar"));


	taskToolbar->addAction(newTaskAction_);
	taskToolbar->addAction(deleteTaskAction_);
	taskToolbar->addSeparator();

	taskToolbar->setBaseSize(230, 20);

	taskToolbar->addAction(deindentTaskAction_);
	taskToolbar->addAction(indentTaskAction_);

	QVBoxLayout* taskLeftLayout = new QVBoxLayout();
	taskLeftLayout->addWidget(taskToolbar);
	taskLeftLayout->addWidget(taskTable_);
	taskLeftLayout->setSpacing(0);
	taskLeftLayout->setMargin(0);
	taskLeftLayout->setContentsMargins(0, 0, 0, 0);
	QWidget* taskLeftContent = new QWidget();
	taskLeftContent->setLayout(taskLeftLayout);
	taskLeftContent->setContentsMargins(0, 0, 0, 0);
	taskLeftContent->setMinimumHeight(230);
	taskLeftContent->setMaximumWidth(230);

	// Create a layout (HBox) to contain table + scene:
	QHBoxLayout* taskPageLayout = new QHBoxLayout();
	//layout->addWidget(resourceTable);
	taskPageLayout->addWidget(taskLeftContent);
	taskPageLayout->addWidget(taskView);
	taskPageLayout->setSpacing(0);
	taskPageLayout->setMargin(0);
	taskPageLayout->setContentsMargins(0, 0, 0, 0);

	// Use a widget to set the layout:
	QWidget* taskPage = new QWidget();
	taskPage->setLayout(taskPageLayout);
	taskPage->setContentsMargins(0, 0, 0, 0);

	// Add the widget to the tab:
	mainTab_->addTab(taskPage, tr("Tasks"));
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

void MainWindow::refreshTaskTable()
{
	taskTable_->blockSignals(true);

	// Delete table and items:
	for (int r = taskTable_->rowCount(); r >= 0; --r)
		taskTable_->removeRow(r);

	for (int i = 0; i < project_->getTasksSize(); ++i){
		Task* t = project_->getTaskSequentially(i);

		// Children will be printed after their parent:
		if (t->getParent() != 0)
			continue;

		taskTable_->insertRow(taskTable_->rowCount());

		QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
		newItemTaskId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
		newItemTaskId->setText(QString::number(t->getId()));
		taskTable_->setItem(taskTable_->rowCount()-1, 0, newItemTaskId);

		QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
		newItemTaskName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemTaskName->setText(QString::fromStdString(t->getName()));
		taskTable_->setItem(taskTable_->rowCount()-1, 1, newItemTaskName);

		if (t->getChildrenSize() == 0){

			// In case it has no children, print Begin and Duration:

			QTableWidgetItem *newItemBegin = new QTableWidgetItem();
			newItemBegin->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
			newItemBegin->setText(t->getBegin().toString("dd.MM.yyyy"));
			taskTable_->setItem(taskTable_->rowCount()-1, 2, newItemBegin);

			QTableWidgetItem *newItemDuration = new QTableWidgetItem();
			newItemDuration->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
			newItemDuration->setText(QString::number(t->getDuration()));
			taskTable_->setItem(taskTable_->rowCount()-1, 3, newItemDuration);

		} else {
			QFont font = newItemTaskName->font();
			font.setBold(true);
			newItemTaskName->setFont(font);
			newItemTaskId->setFont(font);


			// Print children:
			for (int c = 0; c < t->getChildrenSize(); ++c){
				Task* ch = t->getChildrenSequentially(c);
				std::cout << "Task " << t->getId() << " has child " << ch->getId() << std::endl;


				taskTable_->insertRow(taskTable_->rowCount());

				QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
				newItemTaskId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemTaskId->setText(QString::number(ch->getId()));
				taskTable_->setItem(taskTable_->rowCount()-1, 0, newItemTaskId);

				QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
				newItemTaskName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

				QFont font = newItemTaskName->font();
				font.setItalic(true);
				newItemTaskName->setFont(font);

				newItemTaskName->setText(QString::fromStdString("   " + ch->getName()));
				taskTable_->setItem(taskTable_->rowCount()-1, 1, newItemTaskName);

				QTableWidgetItem *newItemBegin = new QTableWidgetItem();
				//QDateEdit* newItemBegin = new QDateEdit();
				newItemBegin->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemBegin->setText(ch->getBegin().toString("dd.MM.yyyy"));
				taskTable_->setItem(taskTable_->rowCount()-1, 2, newItemBegin);

				QTableWidgetItem *newItemDuration = new QTableWidgetItem();
				newItemDuration->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemDuration->setText(QString::number(ch->getDuration()));
				taskTable_->setItem(taskTable_->rowCount()-1, 3, newItemDuration);
			}
		}
	}
	taskTable_->blockSignals(false);

}

void MainWindow::newTaskSlot()
{
	project_->addTask(new Task("New task"));
	setWindowModified(true);
	refreshTaskTable();
}

void MainWindow::removeTaskSlot()
{
	int row = taskTable_->currentRow();
	if (row < 0 || row > taskTable_->rowCount())
		return;
	int id = taskTable_->item(row, 0)->text().toInt();
	project_->removeTask(id);
	setWindowModified(true);
	refreshTaskTable();
}

void MainWindow::indentTaskSlot()
{
	int row = taskTable_->currentRow();

	// No row selected:
	if (row < 1 || row > taskTable_->rowCount())
		return;

	int child = taskTable_->item(row, 0)->text().toInt();

	std::cerr << " Child id: " << child << std::endl;

	// Task is already a child:
	if (project_->getParentTask(child) != 0) {
		std::cerr << " Child already has a parent" << std::endl;
		return;
	}

	std::cerr << "Child does not have parent" << std::endl;


	// Iterate backward to find the new parent:
	while (project_->getTaskFromId(taskTable_->item(row-1, 0)->text().toInt())->getParent() != 0)
		row--;
	int parent = taskTable_->item(row-1, 0)->text().toInt();
	std::cerr << "Parent id: " << parent << std::endl;

	project_->addChildTask(parent, project_->getTaskFromId(child));
	setWindowModified(true);
	refreshTaskTable();
}

void MainWindow::deindentTaskSlot()
{
	int row = taskTable_->currentRow();

	// No row selected:
	if (row < 1 || row > taskTable_->rowCount())
		return;

	int child = taskTable_->item(row, 0)->text().toInt();
	std::cout << "Deindenting task " << child << std::endl;

	project_->removeChildTask(project_->getTaskFromId(child));
	setWindowModified(true);
	refreshTaskTable();
}

void MainWindow::taskValueChanged(int row, int column)
{
	std::cout << "item changed! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > taskTable_->rowCount())
		return;

	int id = taskTable_->item(row, 0)->text().toInt();

	switch(column) {
	case 1:
		std::cout << "Task name changed!" << std::endl;
		project_->getTaskFromId(id)->setName(taskTable_->item(row, column)->text().toStdString());
		break;
	case 3:
		std::cout << "Duration changed!" << std::endl;
		if (taskTable_->item(row, column)->text().toInt() >= 0)
			project_->getTaskFromId(id)->setDuration(taskTable_->item(row, column)->text().toInt());
		break;
	}
	setWindowModified(true);
	refreshTaskTable();
}


void MainWindow::changeTaskBegin()
{
	if (calendar_.isHidden() == false) {
		std::cerr << "Changing beginning for Task: " << calendarTaskId_ << std::endl;
		project_->setTaskBeginning(calendarTaskId_, calendar_.selectedDate());
		std::cerr << "-2-" << std::endl;
		calendar_.setHidden(true);
		std::cerr << "New date: " << project_->getTaskFromId(calendarTaskId_)->getBegin().toString("dd.MM.yyyy").toStdString() << std::endl;
		setWindowModified(true);
		refreshTaskTable();
	}
}


void MainWindow::taskValueClicked(int row, int column)
{
	std::cout << "item clicked! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > taskTable_->rowCount())
		return;

	if ((column == 2) && (calendar_.isHidden() == true)){
		int id = taskTable_->item(row, 0)->text().toInt();
		calendarTaskId_ = id;
		calendar_.setSelectedDate(project_->getTaskFromId(id)->getBegin());
		calendar_.setWindowTitle(QString("Select begin date"));
		calendar_.setHidden(false);
		connect (&calendar_, SIGNAL(selectionChanged()), this, SLOT(changeTaskBegin()));
	}
}




// ==============================================
//		RESOURCES
// ==============================================

void MainWindow::createResourceTab()
{
	// Create left table:
	resourceTable_ = new QTableWidget(0, 3);
	resourceTable_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	resourceTable_->setColumnHidden(0, true);
	connect(resourceTable_, SIGNAL(cellChanged(int, int)), this, SLOT(resourceValueChanged(int, int)));
	QStringList labels;
	labels.append("Id");
	labels.append("Name/Group");
	labels.append("Role");
	resourceTable_->setHorizontalHeaderLabels(labels);
	resourceTable_->verticalHeader()->setVisible(false);
	resourceTable_->setMinimumWidth(160);
	resourceTable_->setMaximumWidth(160);
	resourceTable_->setSelectionBehavior(QAbstractItemView::SelectRows);

	resourceTable_->setColumnWidth(0, 50);
	resourceTable_->setColumnWidth(1, 90);
	resourceTable_->setColumnWidth(2, 70);

	// Create left scene:
	QGraphicsScene* resourceScene = new QGraphicsScene(this);
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(0, 0, 100, 10);
	resourceScene->addItem(rect);
	QGraphicsView* resourceView = new QGraphicsView(resourceScene);
	resourceView->show();

	QToolBar* resourceToolbar = addToolBar(tr("&Resource toolbar"));
	resourceToolbar->addAction(newResourceAction_);
	resourceToolbar->addAction(deleteResourceAction_);
	resourceToolbar->addSeparator();
	resourceToolbar->setBaseSize(160, 20);
	resourceToolbar->addAction(deindentResourceAction_);
	resourceToolbar->addAction(indentResourceAction_);


	QVBoxLayout* resourceLeftLayout = new QVBoxLayout();
	resourceLeftLayout->addWidget(resourceToolbar);
	resourceLeftLayout->addWidget(resourceTable_);
	resourceLeftLayout->setSpacing(0);
	resourceLeftLayout->setMargin(0);
	resourceLeftLayout->setContentsMargins(0, 0, 0, 0);
	QWidget* resourceLeftContent = new QWidget();
	resourceLeftContent->setLayout(resourceLeftLayout);
	resourceLeftContent->setContentsMargins(0, 0, 0, 0);
	resourceLeftContent->setMinimumHeight(160);
	resourceLeftContent->setMaximumWidth(160);

	// Create a layout (HBox) to contain table + scene:
	QHBoxLayout* resourcePageLayout = new QHBoxLayout();
	//layout->addWidget(resourceTable_);
	resourcePageLayout->addWidget(resourceLeftContent);
	resourcePageLayout->addWidget(resourceView);
	resourcePageLayout->setSpacing(0);
	resourcePageLayout->setMargin(0);
	resourcePageLayout->setContentsMargins(0, 0, 0, 0);

	// Use a widget to set the layout:
	QWidget* resourcePage = new QWidget();
	resourcePage->setLayout(resourcePageLayout);
	resourcePage->setContentsMargins(0, 0, 0, 0);

	// Add the widget to the tab:
	mainTab_->addTab(resourcePage, tr("Resources"));
	setCentralWidget(mainTab_);
}


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


void MainWindow::refreshResourceTable()
{
	resourceTable_->blockSignals(true);

	// Delete table and items:
	for (int r = resourceTable_->rowCount(); r >= 0; --r)
		resourceTable_->removeRow(r);

	for (int i = 0; i < project_->getResourcesSize(); ++i){
		Resource* t = project_->getResourcesSequentially(i);

		// Children will be printed after their parent:
		if (t->getParent() != 0)
			continue;

		resourceTable_->insertRow(resourceTable_->rowCount());

		QTableWidgetItem *newItemResourceId = new QTableWidgetItem();
		newItemResourceId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
		newItemResourceId->setText(QString::number(t->getId()));
		resourceTable_->setItem(resourceTable_->rowCount()-1, 0, newItemResourceId);

		QTableWidgetItem *newItemResourceName = new QTableWidgetItem();
		newItemResourceName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemResourceName->setText(QString::fromStdString(t->getName()));
		resourceTable_->setItem(resourceTable_->rowCount()-1, 1, newItemResourceName);

		QTableWidgetItem *newItemResourceRole = new QTableWidgetItem();
		newItemResourceRole->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemResourceRole->setText(QString::fromStdString(t->getRole()));
		resourceTable_->setItem(resourceTable_->rowCount()-1, 2, newItemResourceRole);


		if (t->getChildrenSize() > 0){
			QFont font = newItemResourceName->font();
			font.setBold(true);
			newItemResourceName->setFont(font);
			newItemResourceId->setFont(font);
			newItemResourceRole->setFont(font);

			// Print children:
			for (int c = 0; c < t->getChildrenSize(); ++c){
				Resource* ch = t->getChildrenSequentially(c);
				std::cout << "Resource " << t->getId() << " has child " << ch->getId() << std::endl;

				resourceTable_->insertRow(resourceTable_->rowCount());

				QTableWidgetItem *newItemResourceId = new QTableWidgetItem();
				newItemResourceId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemResourceId->setText(QString::number(ch->getId()));
				resourceTable_->setItem(resourceTable_->rowCount()-1, 0, newItemResourceId);

				QTableWidgetItem *newItemResourceName = new QTableWidgetItem();
				newItemResourceName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

				QFont font = newItemResourceName->font();
				font.setItalic(true);
				newItemResourceName->setFont(font);

				newItemResourceName->setText(QString::fromStdString("   " + ch->getName()));
				resourceTable_->setItem(resourceTable_->rowCount()-1, 1, newItemResourceName);

				QTableWidgetItem *newItemResourceRole = new QTableWidgetItem();
				newItemResourceRole->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
				newItemResourceRole->setText(QString::fromStdString(ch->getRole()));
				resourceTable_->setItem(resourceTable_->rowCount()-1, 2, newItemResourceRole);
			}
		}
	}
	resourceTable_->blockSignals(false);

}


void MainWindow::newResourceSlot()
{
	project_->addResource(new Resource("New resource"));
	refreshResourceTable();
}


void MainWindow::removeResourceSlot()
{
	int row = resourceTable_->currentRow();
	if (row < 0 || row > resourceTable_->rowCount())
		return;
	int id = resourceTable_->item(row, 0)->text().toInt();
	std::cerr << "Row: " << row << " Id: " << id << std::endl;
	project_->removeResource(id);
	setWindowModified(true);
	refreshResourceTable();
}


void MainWindow::indentResourceSlot()
{
	int row = resourceTable_->currentRow();

	// No row selected:
	if (row < 1 || row > resourceTable_->rowCount())
		return;

	int child = resourceTable_->item(row, 0)->text().toInt();

	std::cerr << " Child id: " << child << std::endl;

	// Resource is already a child:
	if (project_->getParentResource(child) != 0) {
		std::cerr << " Child already has a parent" << std::endl;
		return;
	}

	std::cerr << "Child does not have parent" << std::endl;


	// Iterate backward to find the new parent:
	while (project_->getResourceFromId(resourceTable_->item(row-1, 0)->text().toInt())->getParent() != 0)
		row--;
	int parent = resourceTable_->item(row-1, 0)->text().toInt();
	std::cerr << "Parent id: " << parent << std::endl;

	project_->addChildResource(parent, project_->getResourceFromId(child));
	setWindowModified(true);
	refreshResourceTable();
}


void MainWindow::deindentResourceSlot()
{
	int row = resourceTable_->currentRow();

	// No row selected:
	if (row < 1 || row > resourceTable_->rowCount())
		return;

	int child = resourceTable_->item(row, 0)->text().toInt();
	std::cout << "Deindenting resource " << child << std::endl;

	project_->removeChildResource(project_->getResourceFromId(child));
	setWindowModified(true);
	refreshResourceTable();
}


void MainWindow::resourceValueChanged(int row, int column)
{
	std::cout << "item changed! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > resourceTable_->rowCount())
		return;

	int id = resourceTable_->item(row, 0)->text().toInt();
	if (column == 1) {
		std::cout << "Resource name changed!" << std::endl;
		project_->getResourceFromId(id)->setName(resourceTable_->item(row, column)->text().toStdString());
	} else if (column == 2) {
		std::cout << "Role changed!" << std::endl;
		project_->getResourceFromId(id)->setRole(resourceTable_->item(row, column)->text().toStdString());
	}
	setWindowModified(true);
	refreshResourceTable();
}






