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

private:

	Project* project_;
	QTableWidget* taskTable_;
	QTableWidget* resourceTable_;

	Ui::MainWindow *ui;

	// File menu:
	QMenu* fileMenu;
	QAction* newProjectAction;
	QAction* openProjectAction;
	QAction* recentProjectsAction;
	QAction* saveProjectAction;
	QAction* saveAsProjectAction;
	QAction* exportAction;
	QAction* exitAction;
	QAction* optionsAction;

	// Edit menu:
	QMenu* editMenu;
	QAction* newResourceAction;
	QAction* deleteResourceAction;
	QAction* newTaskAction;
	QAction* deleteTaskAction;

	// View menu:
	QMenu* viewMenu;
	QAction* viewResourceAction;
	QAction* viewTaskAction;

	// About menu:
	QMenu* aboutMenu;
	QAction* aboutAction;

	// Main toolbar
	QAction* indentTaskAction;
	QAction* deindentTaskAction;
	QAction* indentResourceAction;
	QAction* deindentResourceAction;

	QToolBar* mainToolbar;

	QTabWidget tab;

	void createMainMenu();
	void createMainToolbar();
	void enableDisableMenu();
	bool loadFile(const std::string& filename){
		return project_->loadFile(filename);
	}

	void createResourceTab();
	void createTaskTab();

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
	void changeTaskValues(int row, int column);
	void newResourceSlot();
	void removeResourceSlot();
	void indentResourceSlot();
	void deindentResourceSlot();
	void changeResourceValues(int row, int column);
};

#endif // MAINWINDOW_HPP
