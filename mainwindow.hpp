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
#include "options.hpp"
#include "taskpage.hpp"
#include "resourcepage.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
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

	void showOptions();

private:
	void createActions();
	void createMainMenu();
	void createMainToolbar();
	void enableDisableMenu();

	void createTaskTab();
	void createResourceTab();
	void writeInStatusBar(const char* s, int msec);


	QScopedPointer<Project> project_;

	QTableWidget* resourceTable_;
	Options options_;

	QScopedPointer<TaskPage> taskPage_;
	QScopedPointer<ResourcePage> resourcePage_;

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

	QAction* indentTaskAction_;
	QAction* deindentTaskAction_;
	QAction* newTaskAction_;
	QAction* deleteTaskAction_;

	// Edit menu:
	QMenu* editMenu_;
	QAction* newResourceAction_;
	QAction* deleteResourceAction_;


	// View menu:
	QMenu* viewMenu_;
	QAction* viewResourceAction_;
	QAction* viewTaskAction_;

	// About menu:
	QMenu* aboutMenu_;
	QAction* aboutAction_;
	QAction* aboutQtAction_;

	// Main toolbar
	QAction* indentResourceAction_;
	QAction* deindentResourceAction_;

	QToolBar* mainToolbar_;
	QTabWidget* mainTab_;
};

#endif // MAINWINDOW_HPP
