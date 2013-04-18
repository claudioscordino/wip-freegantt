#ifndef RESOURCEPAGE_HPP
#define RESOURCEPAGE_HPP

#include <QWidget>
#include <QTableWidget>
#include <QMainWindow>
#include <QGraphicsView>

#include "project.hpp"
#include "page.hpp"

class ResourcePage : public Page
{
	Q_OBJECT
public:
	explicit ResourcePage(Project* project, QMainWindow *parent = 0);
	virtual void refreshTable();

public slots:
	virtual void newItem();
	virtual void removeItem();
	virtual void indentItem();
	virtual void deindentItem();

protected slots:
	virtual void valueChanged(int row, int column);
	virtual void valueClicked(int , int ){}

private:
	virtual void createTable();
	virtual void createScene();
	virtual void createToolbar();
	virtual void createLayout();
	virtual void createActions();
};

#endif // RESOURCEPAGE_HPP
