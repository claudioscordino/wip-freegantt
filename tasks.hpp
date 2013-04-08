#ifndef TASKS_HPP
#define TASKS_HPP

#include <string>
#include <vector>
#include <QDate>

class Task;

class Tasks
{
public:
	Tasks(){}
	~Tasks(){}

	Task* getTaskFromId(int id);

	Task* getTaskSequentially(int position);

	Task* removeTask(Task* t);

	Task* removeTask(int id);

	bool addTask(Task* t);

	bool addChildTask(int id, Task* child);

	bool addPredecessorTask(int id, Task* predecessor);

	bool removeChildTask(Task* child);

	Task* removePredecessorTask(int id, Task* predecessor);

	Task* getParentTask(int child_id);

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
