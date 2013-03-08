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
    ui(new Ui::MainWindow),
    tab(this),
    project_(0)
{
    ui->setupUi(this);
    createMainMenu();
    createMainToolbar();
    projectNotExisting();

    setWindowIcon(QIcon(":/images/gantt-hi.png"));
    setWindowTitle("FreeGantt 0.1");

    connect(&tab, SIGNAL(currentChanged(int)), this, SLOT(switchTab(int)));
    //connect(&tab, SIGNAL(currentChanged(1)), this, SLOT(switchToTaskView()));

}

//========== TAB ===========================

void MainWindow::switchToResourceView()
{
    tab.setCurrentIndex(0);
    newTaskAction->setEnabled(false);
    deleteTaskAction->setEnabled(false);
    newResourceAction->setEnabled(true);
    deleteResourceAction->setEnabled(true);
    viewResourceAction->setEnabled(false);
    viewTaskAction->setEnabled(true);
}

void MainWindow::switchToTaskView()
{
    tab.setCurrentIndex(1);
    newTaskAction->setEnabled(true);
    deleteTaskAction->setEnabled(true);
    newResourceAction->setEnabled(false);
    deleteResourceAction->setEnabled(false);
    viewResourceAction->setEnabled(true);
    viewTaskAction->setEnabled(false);
}

void MainWindow::switchTab(int position)
{
    if (position == 0)
	switchToResourceView();
    else
	switchToTaskView();
}


void MainWindow::createTaskTab()
{
    // Create right table:
    int numberOfColumns = 3;
    QTableWidget* taskTable = new QTableWidget(1, 3);
    QStringList labels;
    labels.append("Task");
    labels.append("Begin");
    labels.append("End");
    taskTable->setHorizontalHeaderLabels(labels);
    taskTable->verticalHeader()->setVisible(false);
    taskTable->setMinimumWidth(numberOfColumns * 70);
    taskTable->setMaximumWidth(numberOfColumns * 70);
    taskTable->setColumnWidth(0, 68);
    taskTable->setColumnWidth(1, 68);
    taskTable->setColumnWidth(2, 68);

    // Create left scene:
    QGraphicsScene* taskScene = new QGraphicsScene(this);
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0, 0, 100, 10);
    taskScene->addItem(rect);
    QGraphicsView* taskView = new QGraphicsView(taskScene);
    taskView->show();

    QToolBar* taskToolbar = addToolBar(tr("&Task toolbar"));

    deindentTaskAction= new QAction(tr("&Indent"), this);
    deindentTaskAction->setIcon(QIcon(":images/go-previous.png"));
    taskToolbar->addAction(deindentTaskAction);

    indentTaskAction= new QAction(tr("&Indent"), this);
    indentTaskAction->setIcon(QIcon(":images/go-next.png"));
    taskToolbar->addAction(indentTaskAction);

    taskToolbar->addSeparator();
    taskToolbar->addAction(newTaskAction);
    taskToolbar->addAction(deleteTaskAction);

    taskToolbar->setBaseSize(numberOfColumns * 70, 20);

    QVBoxLayout* taskLeftLayout = new QVBoxLayout();
    taskLeftLayout->addWidget(taskToolbar);
    taskLeftLayout->addWidget(taskTable);
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

    // Create right table:
    int numberOfColumns = 2;
    QTableWidget* resourceTable = new QTableWidget(1, 2);
    QStringList labels;
    labels.append("Name");
    labels.append("Job");
    resourceTable->setHorizontalHeaderLabels(labels);
    resourceTable->verticalHeader()->setVisible(false);
    resourceTable->setMinimumWidth(numberOfColumns * 70);
    resourceTable->setMaximumWidth(numberOfColumns * 70);
    resourceTable->setColumnWidth(0, 68);
    resourceTable->setColumnWidth(1, 68);

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
    resourceLeftLayout->addWidget(resourceTable);
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
    //layout->addWidget(resourceTable);
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
    connect(viewResourceAction, SIGNAL(triggered()), this, SLOT(switchToResourceView()));

    viewTaskAction = new QAction(tr("&View Tasks"), this);
    viewTaskAction->setIcon(QIcon(":images/showGrid.png"));
    viewMenu->addAction(viewTaskAction);
    connect(viewTaskAction, SIGNAL(triggered()), this, SLOT(switchToTaskView()));

    menuBar()->addSeparator();

    aboutMenu = menuBar()->addMenu((tr("&About")));
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":images/statusWindow.png"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutClicked()));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::projectExisting()
{
    project_ = Project::getInstance();
    editMenu->setEnabled(true);
    viewMenu->setEnabled(true);
    saveProjectAction->setEnabled(true);
    saveAsProjectAction->setEnabled(true);
    exportAction->setEnabled(true);
}

void MainWindow::projectNotExisting()
{
    delete project_;
    editMenu->setEnabled(false);
    viewMenu->setEnabled(false);
    saveProjectAction->setEnabled(false);
    saveAsProjectAction->setEnabled(false);
    exportAction->setEnabled(false);
}

void MainWindow::openClicked()
{
    if (saveProject()) {
	QString fileName = QFileDialog::getOpenFileName(this,
							tr("Open saved projects"), ".",
							tr("FreeGantt files (*.gtt)"));
	if (!fileName.isEmpty())
	    loadFile(fileName);
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
    projectExisting();
    createResourceTab();
    createTaskTab();
    switchToResourceView();
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
		       "<h2>FreeGantt 0.1</h2>"
		       "<p>Copyright &copy; 2011 Claudio Scordino</p>"
		       "<p> FreeGantt is a small application to draw "
		       "Gantt diagrams.</p>");
}


MainWindow::~MainWindow()
{
    delete ui;
}
