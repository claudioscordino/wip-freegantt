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
    ~MainWindow();

private:

    Project* project_;

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

    QToolBar* mainToolbar;

    QTabWidget tab;

    void createMainMenu();
    void createMainToolbar();
    void projectExisting();
    void projectNotExisting();
    bool loadFile(QString filename){return true;}

    void createResourceTab();
    void createTaskTab();

private slots:
    bool saveProject();
    bool exitClicked();
    void newProjectSlot();
    bool saveClicked(){return true;}
    void openClicked();
    void aboutClicked();
    void switchToTaskView();
    void switchToResourceView();
    void switchTab(int pos);

protected:
    void closeEvent(QCloseEvent* event){exitClicked();}


};

#endif // MAINWINDOW_HPP
