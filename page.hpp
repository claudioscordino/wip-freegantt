#ifndef PAGE_HPP
#define PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QGraphicsView>

#include "project.hpp"

class Page : public QWidget
{
	Q_OBJECT
public:
	explicit Page(Project* project, QMainWindow *parent = 0);
	virtual void refreshTable()=0;
	virtual ~Page(){
		delete table_;
	}
	
public slots:
	virtual void newItem()=0;
	virtual void removeItem()=0;
	virtual void indentItem()=0;
	virtual void deindentItem()=0;

protected slots:
	virtual void valueChanged(int row, int column)=0;
	virtual void valueClicked(int row, int column)=0;


protected:
	void createPage();
	virtual void createTable()=0;
	virtual void createScene()=0;
	virtual void createToolbar()=0;
	virtual void createLayout()=0;
	virtual void createActions()=0;

	Project* project_;
	QMainWindow* parent_;

	QAction* indentItemAction_;
	QAction* deindentItemAction_;
	QAction* newItemAction_;
	QAction* deleteItemAction_;

	QTableWidget* table_;
	QGraphicsView* view_;
	QToolBar* toolbar_;
};

#endif // PAGE_HPP
