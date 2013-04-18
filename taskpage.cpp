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
#include <QtGui>

#include <iostream>

#define VERSION "0.3"

#include "taskpage.hpp"

TaskPage::TaskPage(Project* project, QMainWindow *parent) :
	QWidget(parent),
	project_(project),
	calendarTaskId_(0),
	taskTable_(0),
	taskView_(0),
	taskToolbar_(0)
{
	calendar_.setHidden(true);
	createActions();
	createTable();
	createScene();
	createToolbar(parent);
	createLayout();
}

void TaskPage::createActions()
{
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

	// Tasks:
	connect(newTaskAction_, SIGNAL(triggered()), this, SLOT(newTaskSlot()));
	connect(deleteTaskAction_, SIGNAL(triggered()), this, SLOT(removeTaskSlot()));
	connect(indentTaskAction_, SIGNAL(triggered()), this, SLOT(indentTaskSlot()));
	connect(deindentTaskAction_, SIGNAL(triggered()), this, SLOT(deindentTaskSlot()));
}

void TaskPage::createTable()
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
	taskTable_->show();
}

void TaskPage::createScene()
{
	// Create left scene:
	QGraphicsScene* taskScene = new QGraphicsScene(this);
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(0, 0, 100, 10);
	taskScene->addItem(rect);
	taskView_ = new QGraphicsView(taskScene);
	taskView_->show();
}

void TaskPage::createToolbar(QMainWindow *parent)
{
	if (parent != 0)
		taskToolbar_ = parent->addToolBar(tr("&Task toolbar"));
	taskToolbar_->addAction(newTaskAction_);
	taskToolbar_->addAction(deleteTaskAction_);
	taskToolbar_->addSeparator();
	taskToolbar_->setBaseSize(230, 20);
	taskToolbar_->addAction(deindentTaskAction_);
	taskToolbar_->addAction(indentTaskAction_);
	taskToolbar_->show();
}





void TaskPage::createLayout()
{
	QVBoxLayout* taskLeftLayout = new QVBoxLayout();
	taskLeftLayout->addWidget(taskToolbar_);
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
	taskPageLayout->addWidget(taskLeftContent);
	taskPageLayout->addWidget(taskView_);
	taskPageLayout->setSpacing(0);
	taskPageLayout->setMargin(0);
	taskPageLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(taskPageLayout);
	setContentsMargins(0, 0, 0, 0);
}







void TaskPage::refreshList()
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

void TaskPage::changeTaskBegin()
{
	if (calendar_.isHidden() == false) {
		std::cerr << "Changing beginning for Task: " << calendarTaskId_ << std::endl;
		project_->setTaskBeginning(calendarTaskId_, calendar_.selectedDate());
		std::cerr << "-2-" << std::endl;
		calendar_.setHidden(true);
		std::cerr << "New date: " << project_->getTaskFromId(calendarTaskId_)->getBegin().toString("dd.MM.yyyy").toStdString() << std::endl;
		setWindowModified(true);
		refreshList();
	}
}


void TaskPage::taskValueClicked(int row, int column)
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

void TaskPage::newTaskSlot()
{
	project_->addTask(new Task("New task"));
	setWindowModified(true);
	refreshList();
}

void TaskPage::removeTaskSlot()
{
	int row = taskTable_->currentRow();
	if (row < 0 || row > taskTable_->rowCount())
		return;
	int id = taskTable_->item(row, 0)->text().toInt();
	project_->removeTask(id);
	setWindowModified(true);
	refreshList();
}

void TaskPage::indentTaskSlot()
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
	refreshList();
}

void TaskPage::deindentTaskSlot()
{
	int row = taskTable_->currentRow();

	// No row selected:
	if (row < 1 || row > taskTable_->rowCount())
		return;

	int child = taskTable_->item(row, 0)->text().toInt();
	std::cout << "Deindenting task " << child << std::endl;

	project_->removeChildTask(project_->getTaskFromId(child));
	setWindowModified(true);
	refreshList();
}

void TaskPage::taskValueChanged(int row, int column)
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
	refreshList();
}
