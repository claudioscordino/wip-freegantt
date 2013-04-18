#ifndef TASKPAGE_HPP
#define TASKPAGE_HPP

#include <QWidget>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QMainWindow>
#include <QGraphicsView>

#include "project.hpp"

class TaskPage : public QWidget
{
	Q_OBJECT
public:
	explicit TaskPage(Project* project, QMainWindow *parent = 0);
	void refreshList();
	~TaskPage(){
		delete taskTable_;
	}


public slots:
	void newTaskSlot();
	void removeTaskSlot();
	void indentTaskSlot();
	void deindentTaskSlot();

private slots:
	void changeTaskBegin();
	void taskValueChanged(int row, int column);
	void taskValueClicked(int row, int column);


private:
	void createTable();
	void createScene(QMainWindow *parent);
	void createToolbar(QMainWindow *parent);
	void createLayout();
	void createActions();

	Project* project_;
	QCalendarWidget calendar_;
	int calendarTaskId_;


	QAction* indentTaskAction_;
	QAction* deindentTaskAction_;
	QAction* newTaskAction_;
	QAction* deleteTaskAction_;

	QTableWidget* taskTable_;
	QGraphicsView* taskView_;
	QToolBar* taskToolbar_;



};

#endif // TASKPAGE_HPP
