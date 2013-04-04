#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>
#include <QDate>

#include "resource.hpp"
#include "task.hpp"
#include "calendar.hpp"

class Project
{
public:

	// Resources:

	Resource* getResource(const std::string& name);

	bool removeResource(const std::string& name);

	bool addResource(const std::string& name, const std::string& role);

	inline bool addResource(const std::string& name){
		return addResource (name, "");
	}

	bool setResourceRole(const std::string& name, const std::string& role);

	std::string getResourceRole(const std::string& name);

	bool setResourceName(const std::string& oldname, const std::string& newname);



	// Holidays::

	inline bool addHoliday(const QDate& date) {
		return holidays_.addDate(date);
	}

	inline bool checkHoliday(const QDate& date) {
		return holidays_.checkDate(date);
	}

	inline bool removeHoliday(const QDate& date) {
		return holidays_.removeDate(date);
	}

	// Tasks:

	Task* getTask(const std::string& name);

	bool removeTask(const std::string& name);

	bool addTask (const std::string& name);

	bool addChildTask(const std::string& name, Task* child);

	bool addPredecessorTask(const std::string& name, Task* predecessor);

	bool removeChildTask(const std::string& name, const Task& child);

	bool removePredecessorTask(const std::string& name, const Task& predecessor);

	QDate getTaskBeginning(const std::string& name);

	bool setTaskBeginning(const std::string& name, const QDate& date);

	int getTaskDuration(const std::string& name);

	bool setTaskDuration(const std::string& name, int duration);

	bool setTaskName(const std::string& oldname, const std::string& newname);

	bool addStopDay(const std::string& oldname, const QDate& date);

	bool removeStopDay(const std::string& oldname, const QDate& date);

	QDate getTaskEnd(const std::string& name);

	inline bool loadFile(const std::string& name){
		file_name_ = name;
		// FIXME
		return true;
	}

	inline int getTaskNumber() const {
		return tasks_.size();
	}


	Project(){}


private:
	/// List of resources:
	std::vector<Resource*> resources_;

	/// List of tasks:
	std::vector<Task*> tasks_;

	/// List of holidays:
	Calendar holidays_;

	/// Project name:
	std::string name_;

	/// Path of the project file name:
	std::string file_name_;
};

#endif // PROJECT_HPP
