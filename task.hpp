#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <QDate>
#include <QColor>

#include "resource.hpp"


class Task
{
public:
    Task(const std::string& name):
	name_(name), priority(0){}
private:
    Task();

    /// Name of the task:
    std::string name_;

    /// Children of the task:
    std::vector<Task*> children_;

    /// Predecossors of the task:
    std::vector<Task*> predecessors_;

    /// Begin of the task:
    QDate begin_;

    /// End of the task:
    QDate end_;

    /// Priority of the task: (0-100):
    int priority_;

    /// Color in the gantt chart:
    QColor color_;

    struct Allocation {
	Resource* resource_;
	int percentage_; // 0 - 100
    };

    /// Allocation of resources:
    std::vector<Allocation> resources_;
};

#endif // TASK_HPP
