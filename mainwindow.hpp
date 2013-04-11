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
		exitClicked();
	}

private slots:
	bool saveProject();
	bool exitClicked();
	void newProjectSlot();
	bool saveClicked(){return true;}
	void openClicked();
	void aboutClicked();
	void switchTab(int tab);
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
	bool loadFile(const std::string& filename){
		return project_->loadFile(filename);
	}

	void createResourceTab();
	void createTaskTab();

	Project* project_;
	QTableWidget* taskTable_;
	QTableWidget* resourceTable_;

	Ui::MainWindow *ui;

	// File menu:
	QMenu* fileMenu_;
	QAction* newProjectAction_;
	QAction* openProjectAction_;
	QAction* recentProjectsAction_;
	QAction* saveProjectAction_;
	QAction* saveAsProjectAction_;
	QAction* exportProjectAction_;
	QAction* exitAction_;
	QAction* optionsPanelAction_;

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

	// Main toolbar
	QAction* indentTaskAction_;
	QAction* deindentTaskAction_;
	QAction* indentResourceAction_;
	QAction* deindentResourceAction_;

	QToolBar* mainToolbar_;

	QTabWidget mainTab_;


	QCalendarWidget calendar_;
	int calendarTaskId_;
};

#endif // MAINWINDOW_HPP
