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
	virtual void refreshTable();
	void setFirstDayOfWeek(Qt::DayOfWeek day){
		calendar_.setFirstDayOfWeek(day);
	}
	Qt::DayOfWeek getFirstDayOfWeek(){
		return calendar_.firstDayOfWeek();
	}

public slots:
	virtual void newItem();
	virtual void removeItem();
	virtual void indentItem();
	virtual void deindentItem();

protected slots:
	virtual void valueChanged(int row, int column);
	virtual void valueClicked(int row, int column);

private slots:
	void changeTaskBegin();

private:
	virtual void createTable();
	virtual void createScene();
	virtual void createToolbar();
	virtual void createLayout();
	virtual void createActions();

	QCalendarWidget calendar_;
	int calendarTaskId_;
};

#endif // TASKPAGE_HPP
