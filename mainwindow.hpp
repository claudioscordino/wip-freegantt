#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTableWidget>
#include <QTabWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include <vector>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QCalendarWidget>

#include "project.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	void refreshTaskTable();
	void refreshResourceTable();
	~MainWindow();


protected:
	inline void closeEvent(QCloseEvent* ){
		exitProgram();
	}

private slots:
	int okToDiscardCurrentProject();
	void exitProgram();
	void newProject();
	bool saveProject();
	bool saveProjectAs();
	void openProject();
	void aboutProgram();
	void switchToTab(int tab);
	void switchTab();
	void switchToTaskTab();
	void switchToResourceTab();
	void newTaskSlot();
	void removeTaskSlot();
	void indentTaskSlot();
	void deindentTaskSlot();
	void taskValueChanged(int row, int column);
	void taskValueClicked(int row, int column);
	void newResourceSlot();
	void removeResourceSlot();
	void indentResourceSlot();
	void deindentResourceSlot();
	void resourceValueChanged(int row, int column);
	void changeTaskBegin();

private:
	void createActions();
	void createMainMenu();
	void createMainToolbar();
	void enableDisableMenu();

	void createTaskTab();
	void createResourceTab();
	void writeInStatusBar(const char* s, int msec);


	QScopedPointer<Project> project_;
	QTableWidget* taskTable_;
	QTableWidget* resourceTable_;

	Ui::MainWindow *ui;

	// File menu:
	QMenu* fileMenu_;
	QAction* newProjectAction_;
	QAction* printProjectAction_;
	QAction* openProjectAction_;
	QAction* recentProjectsAction_;
	QAction* saveProjectAction_;
	QAction* saveAsProjectAction_;
	QAction* exportProjectAction_;
	QAction* exitAction_;
	QAction* optionsPanelAction_;
	QAction* switchTabAction_;

	// Edit menu:
	QMenu* editMenu_;
	QAction* newResourceAction_;
	QAction* deleteResourceAction_;
	QAction* newTaskAction_;
	QAction* deleteTaskAction_;

	// View menu:
	QMenu* viewMenu_;
	QAction* viewResourceAction_;
	QAction* viewTaskAction_;

	// About menu:
	QMenu* aboutMenu_;
	QAction* aboutAction_;
	QAction* aboutQtAction_;

	// Main toolbar
	QAction* indentTaskAction_;
	QAction* deindentTaskAction_;
	QAction* indentResourceAction_;
	QAction* deindentResourceAction_;

	QToolBar* mainToolbar_;

	QTabWidget* mainTab_;

	QCalendarWidget calendar_;
	int calendarTaskId_;

};

#endif // MAINWINDOW_HPP
