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

#include "resourcepage.hpp"

ResourcePage::ResourcePage(Project* project, QMainWindow *parent) :
	Page(project, parent)
{
	createPage();
}


void ResourcePage::createActions()
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

	// Resources:
	connect(newItemAction_, SIGNAL(triggered()), this, SLOT(newItem()));
	connect(deleteItemAction_, SIGNAL(triggered()), this, SLOT(removeItem()));
	connect(indentItemAction_, SIGNAL(triggered()), this, SLOT(indentItem()));
	connect(deindentItemAction_, SIGNAL(triggered()), this, SLOT(deindentItem()));

}

void ResourcePage::createTable()
{
	// Create left table:
	table_ = new QTableWidget(0, 3);
	table_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	table_->setColumnHidden(0, true);
	connect(table_, SIGNAL(cellChanged(int, int)), this, SLOT(resourceValueChanged(int, int)));
	QStringList labels;
	labels.append("Id");
	labels.append("Name/Group");
	labels.append("Role");
	table_->setHorizontalHeaderLabels(labels);
	table_->verticalHeader()->setVisible(false);
	table_->setMinimumWidth(160);
	table_->setMaximumWidth(160);
	table_->setSelectionBehavior(QAbstractItemView::SelectRows);

	table_->setColumnWidth(0, 50);
	table_->setColumnWidth(1, 90);
	table_->setColumnWidth(2, 70);
	table_->show();
}

void ResourcePage::createScene()
{
	// Create left scene:
	QGraphicsScene* resourceScene = new QGraphicsScene(this);
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(0, 0, 100, 10);
	resourceScene->addItem(rect);
	QGraphicsView* view_ = new QGraphicsView(resourceScene);
	view_->show();
}

void ResourcePage::createToolbar()
{
	if (parent_ != 0)
		toolbar_ = parent_->addToolBar(tr("&Resource toolbar"));
	toolbar_->addAction(newItemAction_);
	toolbar_->addAction(deleteItemAction_);
	toolbar_->addSeparator();
	toolbar_->setBaseSize(160, 20);
	toolbar_->addAction(deindentItemAction_);
	toolbar_->addAction(indentItemAction_);
	toolbar_->show();
}





void ResourcePage::createLayout()
{
	QVBoxLayout* resourceLeftLayout = new QVBoxLayout();
	resourceLeftLayout->addWidget(toolbar_);
	resourceLeftLayout->addWidget(table_);
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
	resourcePageLayout->addWidget(resourceLeftContent);
	resourcePageLayout->addWidget(view_);
	resourcePageLayout->setSpacing(0);
	resourcePageLayout->setMargin(0);
	resourcePageLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(resourcePageLayout);
	setContentsMargins(0, 0, 0, 0);
}







void ResourcePage::refreshTable()
{
	table_->blockSignals(true);

	// Delete table and items:
	for (int r = table_->rowCount(); r >= 0; --r)
		table_->removeRow(r);

	for (int i = 0; i < project_->getResourcesSize(); ++i){
		Resource* t = project_->getResourcesSequentially(i);

		// Children will be printed after their parent:
		if (t->getParent() != 0)
			continue;

		table_->insertRow(table_->rowCount());

		QTableWidgetItem *newItemResourceId = new QTableWidgetItem();
		newItemResourceId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
		newItemResourceId->setText(QString::number(t->getId()));
		table_->setItem(table_->rowCount()-1, 0, newItemResourceId);

		QTableWidgetItem *newItemResourceName = new QTableWidgetItem();
		newItemResourceName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemResourceName->setText(QString::fromStdString(t->getName()));
		table_->setItem(table_->rowCount()-1, 1, newItemResourceName);

		QTableWidgetItem *newItemResourceRole = new QTableWidgetItem();
		newItemResourceRole->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		newItemResourceRole->setText(QString::fromStdString(t->getRole()));
		table_->setItem(table_->rowCount()-1, 2, newItemResourceRole);


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

				table_->insertRow(table_->rowCount());

				QTableWidgetItem *newItemResourceId = new QTableWidgetItem();
				newItemResourceId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
				newItemResourceId->setText(QString::number(ch->getId()));
				table_->setItem(table_->rowCount()-1, 0, newItemResourceId);

				QTableWidgetItem *newItemResourceName = new QTableWidgetItem();
				newItemResourceName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

				QFont font = newItemResourceName->font();
				font.setItalic(true);
				newItemResourceName->setFont(font);

				newItemResourceName->setText(QString::fromStdString("   " + ch->getName()));
				table_->setItem(table_->rowCount()-1, 1, newItemResourceName);

				QTableWidgetItem *newItemResourceRole = new QTableWidgetItem();
				newItemResourceRole->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
				newItemResourceRole->setText(QString::fromStdString(ch->getRole()));
				table_->setItem(table_->rowCount()-1, 2, newItemResourceRole);
			}
		}
	}
	table_->blockSignals(false);


}




void ResourcePage::newItem()
{
	project_->addResource(new Resource("New resource"));
	parent_->setWindowModified(true);
	refreshTable();
}

void ResourcePage::removeItem()
{
	int row = table_->currentRow();
	if (row < 0 || row > table_->rowCount())
		return;
	int id = table_->item(row, 0)->text().toInt();
	std::cerr << "Row: " << row << " Id: " << id << std::endl;
	project_->removeResource(id);


	parent_->setWindowModified(true);
	refreshTable();
}

void ResourcePage::indentItem()
{
	int row = table_->currentRow();

	// No row selected:
	if (row < 1 || row > table_->rowCount())
		return;

	int child = table_->item(row, 0)->text().toInt();

	std::cerr << " Child id: " << child << std::endl;

	// Resource is already a child:
	if (project_->getParentResource(child) != 0) {
		std::cerr << " Child already has a parent" << std::endl;
		return;
	}

	std::cerr << "Child does not have parent" << std::endl;


	// Iterate backward to find the new parent:
	while (project_->getResourceFromId(table_->item(row-1, 0)->text().toInt())->getParent() != 0)
		row--;
	int parent = table_->item(row-1, 0)->text().toInt();
	std::cerr << "Parent id: " << parent << std::endl;

	project_->addChildResource(parent, project_->getResourceFromId(child));

	parent_->setWindowModified(true);
	refreshTable();
}

void ResourcePage::deindentItem()
{
	int row = table_->currentRow();

	// No row selected:
	if (row < 1 || row > table_->rowCount())
		return;

	int child = table_->item(row, 0)->text().toInt();
	std::cout << "Deindenting resource " << child << std::endl;

	project_->removeChildResource(project_->getResourceFromId(child));
	parent_->setWindowModified(true);
	refreshTable();
}

void ResourcePage::valueChanged(int row, int column)
{
	std::cout << "item changed! row: " << row << " column: " << column << std::endl;

	// No row selected:
	if (row < 0 || row > table_->rowCount())
		return;

	int id = table_->item(row, 0)->text().toInt();
	if (column == 1) {
		std::cout << "Resource name changed!" << std::endl;
		project_->getResourceFromId(id)->setName(table_->item(row, column)->text().toStdString());
	} else if (column == 2) {
		std::cout << "Role changed!" << std::endl;
		project_->getResourceFromId(id)->setRole(table_->item(row, column)->text().toStdString());
	}


	parent_->setWindowModified(true);
	refreshTable();
}
