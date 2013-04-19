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

#include "taskpage.hpp"

TaskPage::TaskPage(Project* project, QMainWindow *parent) :
	Page(project, parent),
	calendarTaskId_(0)
{
	calendar_.setHidden(true);
	calendar_.setFirstDayOfWeek(Qt::DayOfWeek(1));
	createPage();
}

void TaskPage::createActions()
{
	newItemAction_ = new QAction(tr("&New Task"), this);
	newItemAction_->setIcon(QIcon(":images/add.png"));
	newItemAction_->setStatusTip(tr("Add a new task"));

	deleteItemAction_ = new QAction(tr("&Delete Task"), this);
	deleteItemAction_->setIcon(QIcon(":images/list-remove.svg"));
	deleteItemAction_->setStatusTip(tr("Delete the selected task"));

	indentItemAction_ = new QAction(tr("&Indent Task"), this);
	indentItemAction_->setIcon(QIcon(":images/go-next.png"));
	indentItemAction_->setStatusTip(tr("Indent the selected task"));

	deindentItemAction_ = new QAction(tr("&Deindent Task"), this);
	deindentItemAction_->setIcon(QIcon(":images/go-previous.png"));
	deindentItemAction_->setStatusTip(tr("Deindent the selected task"));

	// Tasks:
	connect(newItemAction_, SIGNAL(triggered()), this, SLOT(newItem()));
	connect(deleteItemAction_, SIGNAL(triggered()), this, SLOT(removeItem()));
	connect(indentItemAction_, SIGNAL(triggered()), this, SLOT(indentItem()));
	connect(deindentItemAction_, SIGNAL(triggered()), this, SLOT(deindentItem()));
}

void TaskPage::createTable()
{
	// Create left table:
	table_ = new QTableWidget(0, 4);
	table_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	table_->setColumnHidden(0, true);
	connect(table_, SIGNAL(cellChanged(int, int)), this, SLOT(valueChanged(int, int)));
	connect(table_, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(valueClicked(int, int)));
	QStringList labels;
	labels.append("Id");
	labels.append("Name");
	labels.append("Begin");
	labels.append("Duration");
	table_->setHorizontalHeaderLabels(labels);
	table_->verticalHeader()->setVisible(false);
	table_->setMinimumWidth(230);
	table_->setMaximumWidth(230);
	table_->setSelectionBehavior(QAbstractItemView::SelectRows);

	// Set width of the three columns:
	table_->setColumnWidth(0, 50);
	table_->setColumnWidth(1, 80);
	table_->setColumnWidth(2, 80);
	table_->setColumnWidth(3, 70);
	table_->show();
}

void TaskPage::createScene()
{
	// Create left scene:
	QGraphicsScene* taskScene = new QGraphicsScene(this);
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(0, 0, 100, 10);
	taskScene->addItem(rect);
	view_ = new QGraphicsView(taskScene);
	view_->show();
}

void TaskPage::createToolbar()
{
	if (parent_ != 0)
		toolbar_ = parent_->addToolBar(tr("&Task toolbar"));
	toolbar_->addAction(newItemAction_);
	toolbar_->addAction(deleteItemAction_);
	toolbar_->addSeparator();
	toolbar_->setBaseSize(230, 20);
	toolbar_->addAction(deindentItemAction_);
	toolbar_->addAction(indentItemAction_);
	toolbar_->show();
}





void TaskPage::createLayout()
{
	QVBoxLayout* taskLeftLayout = new QVBoxLayout();
	taskLeftLayout->addWidget(toolbar_);
	taskLeftLayout->addWidget(table_);
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
	taskPageLayout->addWidget(view_);
	taskPageLayout->setSpacing(0);
	taskPageLayout->setMargin(0);
	taskPageLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(taskPageLayout);
	setContentsMargins(0, 0, 0, 0);
}







void TaskPage::refreshTable()
{
	table_->blockSignals(true);

	// Delete table and items:
	for (int r = table_->rowCount(); r >= 0; --r)
		table_->removeRow(r);

	for (int i = 0; i < project_->getTasksSize(); ++i){
		Task* t = project_->getTaskSequentially(i);

		// Children will be printed after their parent:
		if (t->getParent() != 0)
			continue;

		table_->insertRow(table_->rowCount());

		QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
		newItemTaskId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
		newItemTaskId->setText(QString::number(t->getId()));
		table_->setItem(table_->rowCount()-1, 0, newItemTaskId);

		QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
		newItemTaskName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemTaskName->setText(QString::fromStdString(t->getName()));
		table_->setItem(table_->rowCount()-1, 1, newItemTaskName);

		if (t->getChildrenSize() == 0){

			// In case it has no children, print Begin and Duration:

			QTableWidgetItem *newItemBegin = new QTableWidgetItem();
			newItemBegin->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
			newItemBegin->setText(t->getBegin().toString("dd.MM.yyyy"));
			table_->setItem(table_->rowCount()-1, 2, newItemBegin);

			QTableWidgetItem *newItemDuration = new QTableWidgetItem();
			newItemDuration->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
			newItemDuration->setText(QString::number(t->getDuration()));
			table_->setItem(table_->rowCount()-1, 3, newItemDuration);

		} else {
			QFont font = newItemTaskName->font();
			font.setBold(true);
			newItemTaskName->setFont(font);
			newItemTaskId->setFont(font);


			// Print children:
			for (int c = 0; c < t->getChildrenSize(); ++c){
				Task* ch = t->getChildrenSequentially(c);
				std::cout << "Task " << t->getId() << " has child " << ch->getId() << std::endl;


				table_->insertRow(table_->rowCount());

				QTableWidgetItem *newItemTaskId = new QTableWidgetItem();
				newItemTaskId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemTaskId->setText(QString::number(ch->getId()));
				table_->setItem(table_->rowCount()-1, 0, newItemTaskId);

				QTableWidgetItem *newItemTaskName = new QTableWidgetItem();
				newItemTaskName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

				QFont font = newItemTaskName->font();
				font.setItalic(true);
				newItemTaskName->setFont(font);

				newItemTaskName->setText(QString::fromStdString("   " + ch->getName()));
				table_->setItem(table_->rowCount()-1, 1, newItemTaskName);

				QTableWidgetItem *newItemBegin = new QTableWidgetItem();
				//QDateEdit* newItemBegin = new QDateEdit();
				newItemBegin->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemBegin->setText(ch->getBegin().toString("dd.MM.yyyy"));
				table_->setItem(table_->rowCount()-1, 2, newItemBegin);

				QTableWidgetItem *newItemDuration = new QTableWidgetItem();
				newItemDuration->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemDuration->setText(QString::number(ch->getDuration()));
				table_->setItem(table_->rowCount()-1, 3, newItemDuration);
			}
		}
	}
	table_->blockSignals(false);

}

void TaskPage::changeTaskBegin()
{
	if (calendar_.isHidden() == false) {
		std::cerr << "Changing beginning for Task: " << calendarTaskId_ << std::endl;
		project_->setTaskBeginning(calendarTaskId_, calendar_.selectedDate());
		std::cerr << "-2-" << std::endl;
		calendar_.setHidden(true);
		std::cerr << "New date: " << project_->getTaskFromId(calendarTaskId_)->getBegin().toString("dd.MM.yyyy").toStdString() << std::endl;
		parent_->setWindowModified(true);
		refreshTable();
	}
}


void TaskPage::valueClicked(int row, int column)
{
	std::cout << "item clicked! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > table_->rowCount())
		return;

	if ((column == 2) && (calendar_.isHidden() == true)){
		int id = table_->item(row, 0)->text().toInt();
		calendarTaskId_ = id;
		calendar_.setSelectedDate(project_->getTaskFromId(id)->getBegin());
		calendar_.setWindowTitle(QString("Select begin date"));
		calendar_.setHidden(false);
		connect (&calendar_, SIGNAL(selectionChanged()), this, SLOT(changeTaskBegin()));
	}
}

void TaskPage::newItem()
{
	project_->addTask(new Task("New task"));
	parent_->setWindowModified(true);
	refreshTable();
}

void TaskPage::removeItem()
{
	int row = table_->currentRow();
	if (row < 0 || row > table_->rowCount())
		return;
	int id = table_->item(row, 0)->text().toInt();
	project_->removeTask(id);
	parent_->setWindowModified(true);
	refreshTable();
}

void TaskPage::indentItem()
{
	int row = table_->currentRow();

	// No row selected:
	if (row < 1 || row > table_->rowCount())
		return;

	int child = table_->item(row, 0)->text().toInt();

	std::cerr << " Child id: " << child << std::endl;

	// Task is already a child:
	if (project_->getParentTask(child) != 0) {
		std::cerr << " Child already has a parent" << std::endl;
		return;
	}

	std::cerr << "Child does not have parent" << std::endl;


	// Iterate backward to find the new parent:
	while (project_->getTaskFromId(table_->item(row-1, 0)->text().toInt())->getParent() != 0)
		row--;
	int parent = table_->item(row-1, 0)->text().toInt();
	std::cerr << "Parent id: " << parent << std::endl;

	project_->addChildTask(parent, project_->getTaskFromId(child));
	parent_->setWindowModified(true);
	refreshTable();
}

void TaskPage::deindentItem()
{
	int row = table_->currentRow();

	// No row selected:
	if (row < 1 || row > table_->rowCount())
		return;

	int child = table_->item(row, 0)->text().toInt();
	std::cout << "Deindenting task " << child << std::endl;

	project_->removeChildTask(project_->getTaskFromId(child));
	parent_->setWindowModified(true);
	refreshTable();
}

void TaskPage::valueChanged(int row, int column)
{
	std::cout << "item changed! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > table_->rowCount())
		return;

	int id = table_->item(row, 0)->text().toInt();

	switch(column) {
	case 1:
		std::cout << "Task name changed!" << std::endl;
		project_->getTaskFromId(id)->setName(table_->item(row, column)->text().toStdString());
		break;
	case 3:
		std::cout << "Duration changed!" << std::endl;
		if (table_->item(row, column)->text().toInt() >= 0)
			project_->getTaskFromId(id)->setDuration(table_->item(row, column)->text().toInt());
		break;
	}
	parent_->setWindowModified(true);
	refreshTable();
}
