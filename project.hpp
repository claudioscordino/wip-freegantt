#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>
#include <QDate>

#include "resource.hpp"
#include "task.hpp"
#include "calendar.hpp"
#include "allocation.hpp"

class Project
{
public:

	Project(){}
	~Project();

	// Resources:

	Resource* getResource(int id);

	bool removeResource(int id);

	int addResource(const std::string& name, const std::string& role);

	inline int addResource(const std::string& name){
		return addResource (name, "");
	}

	bool setResourceRole(int id, const std::string& role);

	std::string getResourceRole(int id);

	bool setResourceName(int id, const std::string& newname);

	std::string getResourceName(int id);



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

	inline bool loadFile(const std::string& name){
		file_name_ = name;
		// FIXME
		return true;
	}

	inline int getTasksNumber() const {
		return tasks_.size();
	}


	// Allocation:

	inline void allocate(int task_id, int resource_id, int percentage){
		allocations_.allocate(task_id, resource_id, percentage);
	}

	inline bool deallocate(int task_id, int resource_id){
		return allocations_.deallocate(task_id, resource_id);
	}

	inline std::vector<int> getTaskResources(int task_id){
		return allocations_.getTaskResources(task_id);
	}


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

	Allocation allocations_;
};

#endif // PROJECT_HPP
