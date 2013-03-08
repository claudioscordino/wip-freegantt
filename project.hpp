#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>
#include <QDate>

#include "resource.hpp"
#include "task.hpp"

class Project
{
public:  
    static Project* getInstance();

protected:
    Project(){}


private:
    /// List of resources:
    std::vector<Resource*> resources_;

    /// List of tasks:
    std::vector<Task*> tasks_;

    /// List of holidays:
    std::vector<QDate> holidays_;

    /// Project name:
    QString name_;

    /// Path of the project file name:
    QString file_name_;

    static Project* instance_;
 };

#endif // PROJECT_HPP
