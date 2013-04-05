#ifndef TASKS_HPP
#define TASKS_HPP

#include <string>
#include <vector>
#include <QDate>

#include "task.hpp"

class Tasks
{
public:
	Tasks(){}
	~Tasks();

	Task* getTask(int id);

	bool removeTask(int id);

	int addTask (const std::string& name);

	bool addChildTask(int id, Task* child);

	bool addPredecessorTask(int id, Task* predecessor);

	bool removeChildTask(int id, const Task& child);

	bool removePredecessorTask(int id, const Task& predecessor);

	QDate getTaskBeginning(int id);

	bool setTaskBeginning(int id, const QDate& date);

	int getTaskDuration(int id);

	bool setTaskDuration(int id, int duration);

	bool setTaskName(int id, const std::string& newname);

	std::string getTaskName(int id);

	bool addStopDay(int id, const QDate& date);

	bool removeStopDay(int id, const QDate& date);

	QDate getTaskEnd(int id);

	inline int getTasksNumber() const{
		return tasks_.size();
	}

private:

	/// List of tasks:
	std::vector<Task*> tasks_;

};

#endif // TASKS_HPP
