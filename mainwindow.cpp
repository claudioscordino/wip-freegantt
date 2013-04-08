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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    project_(0),
    taskTable_(0),
    resourceTable_(0),
    ui(new Ui::MainWindow),
    tab(this)
{
	ui->setupUi(this);
	createMainMenu();
	createMainToolbar();
	enableDisableMenu();

	setWindowIcon(QIcon(":/images/gantt-hi.png"));
	setWindowTitle("FreeGantt 0.2");

	connect(&tab, SIGNAL(currentChanged(int)), this, SLOT(switchTab(int)));
	connect(newTaskAction, SIGNAL(triggered()), this, SLOT(newTaskSlot()));
	connect(deleteTaskAction, SIGNAL(triggered()), this, SLOT(removeTaskSlot()));
}

//========== TAB ===========================


void MainWindow::refreshTaskTable()
{
	// Delete table and items:
	for (int r = taskTable_->rowCount(); r >= 0; --r)
		taskTable_->removeRow(r);

	for (int i = 0; i < project_->getTasksNumber(); ++i){
		Task* t = project_->getTaskSequentially(i);

		taskTable_->insertRow(taskTable_->rowCount());

		QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
		newItemTaskId->setTextAlignment(Qt::AlignCenter);
		newItemTaskId->setText(QString::fromStdString(t->getId()));
		taskTable_->setItem(taskTable_->rowCount()-1, 0, newItemTaskId);

		QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
		newItemTaskId->setTextAlignment(Qt::AlignLeft);
		newItemTaskName->setText(QString::fromStdString(t->getName()));
		taskTable_->setItem(taskTable_->rowCount()-1, 1, newItemTaskName);

		QTableWidgetItem *newItemBegin = new QTableWidgetItem();
		newItemBegin->setTextAlignment(Qt::AlignCenter);
		newItemBegin->setText(t->getBegin().toString("dd.MM.yyyy"));
		taskTable_->setItem(taskTable_->rowCount()-1, 2, newItemBegin);

		QTableWidgetItem *newItemDuration = new QTableWidgetItem();
		newItemDuration->setTextAlignment(Qt::AlignCenter);
		newItemDuration->setText(QString::number(t->getDuration()));
		taskTable_->setItem(taskTable_->rowCount()-1, 3, newItemDuration);

		//if (t->getChildrenNumber() > 0)
		//	newItemTaskName->setFont(QFont(QFont::Bold));

		// Children:
		for (int c = 0; c < t->getChildrenNumber(); ++c){
			Task* ch = t->getChildrenSequentially(c);

			taskTable_->insertRow(taskTable_->rowCount());

			QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
			newItemTaskId->setTextAlignment(Qt::AlignCenter);
			newItemTaskId->setText(QString::fromStdString(ch->getId()));
			taskTable_->setItem(taskTable_->rowCount()-1, 0, newItemTaskId);

			QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
			newItemTaskId->setTextAlignment(Qt::AlignLeft);
			newItemTaskName->setText(QString::fromStdString(ch->getName()));
			taskTable_->setItem(taskTable_->rowCount()-1, 1, newItemTaskName);

			QTableWidgetItem *newItemBegin = new QTableWidgetItem();
			newItemBegin->setTextAlignment(Qt::AlignCenter);
			newItemBegin->setText(ch->getBegin().toString("dd.MM.yyyy"));
			taskTable_->setItem(taskTable_->rowCount()-1, 2, newItemBegin);

			QTableWidgetItem *newItemDuration = new QTableWidgetItem();
			newItemDuration->setTextAlignment(Qt::AlignCenter);
			newItemDuration->setText(QString::number(ch->getDuration()));
			taskTable_->setItem(taskTable_->rowCount()-1, 3, newItemDuration);
		}
	}
}

void MainWindow::newTaskSlot()
{
	project_->addTask(new Task("New task"));
	refreshTaskTable();
}

void MainWindow::removeTaskSlot()
{
	int row = taskTable_->currentRow();
	int id = taskTable_->item(row, 0)->text().toInt();
	project_->removeTask(id);
	refreshTaskTable();
}



void MainWindow::switchToResourceTab()
{
        tab.setCurrentIndex(0);
        newTaskAction->setEnabled(false);
        deleteTaskAction->setEnabled(false);
        newResourceAction->setEnabled(true);
        deleteResourceAction->setEnabled(true);
        viewResourceAction->setEnabled(false);
        viewTaskAction->setEnabled(true);
}

void MainWindow::switchToTaskTab()
{
        tab.setCurrentIndex(1);
        newTaskAction->setEnabled(true);
        deleteTaskAction->setEnabled(true);
        newResourceAction->setEnabled(false);
        deleteResourceAction->setEnabled(false);
        viewResourceAction->setEnabled(true);
        viewTaskAction->setEnabled(false);
}

// 0 = Resources; 1 = Tasks
void MainWindow::switchTab(int tab_nb)
{
    if (tab_nb == 0)
        switchToResourceTab();
    else
        switchToTaskTab();
}


void MainWindow::createTaskTab()
{
    // Create left table:
    int numberOfColumns = 4;
    taskTable_ = new QTableWidget(0, 4);
    QStringList labels;
    labels.append("Id");
    labels.append("Name");
    labels.append("Begin");
    labels.append("Duration");
    taskTable_->setHorizontalHeaderLabels(labels);
    taskTable_->verticalHeader()->setVisible(false);
    taskTable_->setMinimumWidth(numberOfColumns * 70);
    taskTable_->setMaximumWidth(numberOfColumns * 70);
    taskTable_->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set width of the three columns:
    taskTable_->setColumnWidth(0, 60);
    taskTable_->setColumnWidth(1, 70);
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


    taskToolbar->addAction(newTaskAction);
    taskToolbar->addAction(deleteTaskAction);
    taskToolbar->addSeparator();

    taskToolbar->setBaseSize(numberOfColumns * 70, 20);

    deindentTaskAction= new QAction(tr("&Deindent"), this);
    deindentTaskAction->setIcon(QIcon(":images/go-previous.png"));
    taskToolbar->addAction(deindentTaskAction);

    indentTaskAction= new QAction(tr("&Indent"), this);
    indentTaskAction->setIcon(QIcon(":images/go-next.png"));
    taskToolbar->addAction(indentTaskAction);

    QVBoxLayout* taskLeftLayout = new QVBoxLayout();
    taskLeftLayout->addWidget(taskToolbar);
    taskLeftLayout->addWidget(taskTable_);
    taskLeftLayout->setSpacing(0);
    taskLeftLayout->setMargin(0);
    taskLeftLayout->setContentsMargins(0, 0, 0, 0);
    QWidget* taskLeftContent = new QWidget();
    taskLeftContent->setLayout(taskLeftLayout);
    taskLeftContent->setContentsMargins(0, 0, 0, 0);
    taskLeftContent->setMinimumHeight(numberOfColumns * 70);
    taskLeftContent->setMaximumWidth(numberOfColumns * 70);

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
    tab.addTab(taskPage, tr("Tasks"));
    setCentralWidget(&tab);
}


void MainWindow::createResourceTab()
{
    // Create left table:
    int numberOfColumns = 3;
    resourceTable_ = new QTableWidget(0, 3);
    QStringList labels;
    labels.append("Id");
    labels.append("Name");
    labels.append("Role");
    resourceTable_->setHorizontalHeaderLabels(labels);
    resourceTable_->verticalHeader()->setVisible(false);
    resourceTable_->setMinimumWidth(numberOfColumns * 70);
    resourceTable_->setMaximumWidth(numberOfColumns * 70);
    resourceTable_->setColumnWidth(0, 70);
    resourceTable_->setColumnWidth(1, 70);
    resourceTable_->setColumnWidth(2, 70);

    // Create left scene:
    QGraphicsScene* resourceScene = new QGraphicsScene(this);
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0, 0, 100, 10);
    resourceScene->addItem(rect);
    QGraphicsView* resourceView = new QGraphicsView(resourceScene);
    resourceView->show();

    QToolBar* resourceToolbar = addToolBar(tr("&Resource toolbar"));
    resourceToolbar->addAction(newResourceAction);
    resourceToolbar->addAction(deleteResourceAction);
    resourceToolbar->setBaseSize(numberOfColumns * 70, 20);


    QVBoxLayout* resourceLeftLayout = new QVBoxLayout();
    resourceLeftLayout->addWidget(resourceToolbar);
    resourceLeftLayout->addWidget(resourceTable_);
    resourceLeftLayout->setSpacing(0);
    resourceLeftLayout->setMargin(0);
    resourceLeftLayout->setContentsMargins(0, 0, 0, 0);
    QWidget* resourceLeftContent = new QWidget();
    resourceLeftContent->setLayout(resourceLeftLayout);
    resourceLeftContent->setContentsMargins(0, 0, 0, 0);
    resourceLeftContent->setMinimumHeight(numberOfColumns * 70);
    resourceLeftContent->setMaximumWidth(numberOfColumns * 70);

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
    tab.addTab(resourcePage, tr("Resources"));
    setCentralWidget(&tab);
}

//========== MENU ===========================


void MainWindow::createMainMenu()
{
    // File menu:

    newProjectAction = new QAction(tr("&New Project"), this);
    newProjectAction->setIcon(QIcon(":images/document-new.svg"));
    newProjectAction->setStatusTip(tr("Create a new project"));
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(newProjectSlot()));

    openProjectAction = new QAction(tr("&Open Project"), this);
    openProjectAction->setIcon(QIcon(":images/document-open.svg"));
    connect(openProjectAction, SIGNAL(triggered()), this, SLOT(openClicked()));

    saveProjectAction = new QAction(tr("&Save Project"), this);
    saveProjectAction->setIcon(QIcon(":images/document-save.svg"));

    saveAsProjectAction = new QAction(tr("&Save Project as"), this);
    saveAsProjectAction->setIcon(QIcon(":images/document-save-as.svg"));

    recentProjectsAction = new QAction(tr("&Open recent projects"), this);
    recentProjectsAction->setIcon(QIcon(":images/document-open-recent.png"));

    exportAction = new QAction(tr("&Export to"), this);
    exportAction->setIcon(QIcon(":images/document-save.svg"));

    optionsAction= new QAction(tr("&Options"), this);
    optionsAction->setIcon(QIcon(":images/preferences-desktop.svg"));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon(":images/exit.svg"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitClicked()));

    fileMenu = menuBar()->addMenu((tr("&File")));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    fileMenu->addAction(recentProjectsAction);
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(saveAsProjectAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(optionsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Edit menu:

    editMenu = menuBar()->addMenu((tr("&Edit")));

    newTaskAction = new QAction(tr("&New Task"), this);
    newTaskAction->setIcon(QIcon(":images/add.png"));
    editMenu->addAction(newTaskAction);

    deleteTaskAction = new QAction(tr("&Delete Task"), this);
    deleteTaskAction->setIcon(QIcon(":images/list-remove.svg"));
    editMenu->addAction(deleteTaskAction);

    editMenu->addSeparator();

    newResourceAction = new QAction(tr("&New Resource"), this);
    newResourceAction->setIcon(QIcon(":images/im-user.png"));
    editMenu->addAction(newResourceAction);

    deleteResourceAction = new QAction(tr("&Delete resource "), this);
    deleteResourceAction->setIcon(QIcon(":images/im-kick-user.png"));
    editMenu->addAction(deleteResourceAction);

    // View menu:

    viewMenu = menuBar()->addMenu((tr("&View")));
    viewResourceAction = new QAction(tr("&View Resources"), this);
    viewResourceAction->setIcon(QIcon(":images/im-user-offline.png"));
    viewMenu->addAction(viewResourceAction);
    connect(viewResourceAction, SIGNAL(triggered()), this, SLOT(switchToResourceTab()));

    viewTaskAction = new QAction(tr("&View Tasks"), this);
    viewTaskAction->setIcon(QIcon(":images/showGrid.png"));
    viewMenu->addAction(viewTaskAction);
    connect(viewTaskAction, SIGNAL(triggered()), this, SLOT(switchToTaskTab()));

    menuBar()->addSeparator();

    aboutMenu = menuBar()->addMenu((tr("&About")));
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":images/statusWindow.png"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutClicked()));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::enableDisableMenu()
{
    if (project_ != 0) {
	editMenu->setEnabled(true);
        viewMenu->setEnabled(true);
        saveProjectAction->setEnabled(true);
        saveAsProjectAction->setEnabled(true);
        exportAction->setEnabled(true);
    } else {
        editMenu->setEnabled(false);
        viewMenu->setEnabled(false);
        saveProjectAction->setEnabled(false);
        saveAsProjectAction->setEnabled(false);
        exportAction->setEnabled(false);
    }
}

void MainWindow::openClicked()
{
    if (saveProject()) {
	QString fileName = QFileDialog::getOpenFileName(this,
							tr("Open saved projects"), ".",
							tr("FreeGantt files (*.gtt)"));
	if (!fileName.isEmpty())
	    loadFile(fileName.toStdString());
    }

}


void MainWindow::createMainToolbar()
{
    mainToolbar = addToolBar(tr("&Main commands"));
    mainToolbar->addAction(newProjectAction);
    mainToolbar->addAction(openProjectAction);
    mainToolbar->addAction(saveProjectAction);

}



void MainWindow::newProjectSlot()
{
    project_ = new Project();
    enableDisableMenu();
    createResourceTab();
    createTaskTab();
    switchToTaskTab();
}


bool MainWindow::saveProject()
{
    if (project_ != 0) {
	int ret = QMessageBox::warning(this, tr("Exit"),
		    tr("The project has been modifed.\n"
		       "Do you want to save your changes ?"),
		    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (ret == QMessageBox::Yes)
	    return saveClicked();
	else if (ret == QMessageBox::Cancel)
	    return false;
    }
    return true;
}

bool MainWindow::exitClicked()
{
    if (saveProject())
	exit(1);
    return false;
}


void MainWindow::aboutClicked()
{
    QMessageBox::about(this, tr("About FreeGantt"),
                       "<h2>FreeGantt 0.2</h2>"
                       "<p>Copyright &copy; 2013 Claudio Scordino</p>"
		       "<p> FreeGantt is a small application to draw "
		       "Gantt diagrams.</p>");
}


MainWindow::~MainWindow()
{
    delete ui;
}
