#ifndef TASKPAGE_HPP
#define TASKPAGE_HPP

#include <QWidget>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QMainWindow>
#include <QGraphicsView>

#include "project.hpp"
#include "page.hpp"

class TaskPage : public Page
{
	Q_OBJECT
public:
	explicit TaskPage(Project* project, QMainWindow *parent = 0);
#if 1
	virtual void refreshTable();
#endif

#if 1
public slots:
	virtual void newItem();
	virtual void removeItem();
	virtual void indentItem();
	virtual void deindentItem();
#endif

#if 1
protected slots:
	virtual void valueChanged(int row, int column);
	virtual void valueClicked(int row, int column);
#endif


private slots:
	void changeTaskBegin();

private:

#if 1
	virtual void createTable();
	virtual void createScene();
	virtual void createToolbar();
	virtual void createLayout();
	virtual void createActions();
#endif
	QCalendarWidget calendar_;
	int calendarTaskId_;


};

#endif // TASKPAGE_HPP
