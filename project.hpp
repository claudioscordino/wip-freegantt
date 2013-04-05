#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>
#include <QDate>

#include "resources.hpp"
#include "tasks.hpp"
#include "calendar.hpp"
#include "allocation.hpp"

class Project
{
public:

	Project(){}
	~Project(){}

	// Resources:

	inline Resource* getResource(int id){
		return resources_.getResource(id);
	}

	inline bool removeResource(int id){
		return resources_.removeResource(id);
	}

	inline int addResource(const std::string& name, const std::string& role){
		return resources_.addResource(name, role);
	}

	inline int addResource(const std::string& name){
		return resources_.addResource (name);
	}

	inline bool setResourceRole(int id, const std::string& role){
		return resources_.setResourceRole(id, role);
	}

	inline std::string getResourceRole(int id){
		return resources_.getResourceRole(id);
	}

	inline bool setResourceName(int id, const std::string& newname){
		return resources_.setResourceName(id, newname);
	}

	inline std::string getResourceName(int id){
		return resources_.getResourceName(id);
	}



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

	inline Task* getTask(int id){
		return tasks_.getTask(id);
	}

	inline bool removeTask(int id){
		return tasks_.removeTask(id);
	}

	inline int addTask (const std::string& name){
		return tasks_.addTask(name);
	}

	inline bool addChildTask(int id, Task* child){
		return tasks_.addChildTask(id, child);
	}

	inline bool addPredecessorTask(int id, Task* predecessor){
		return tasks_.addPredecessorTask(id, predecessor);
	}

	inline bool removeChildTask(int id, const Task& child){
		return tasks_.removeChildTask(id, child);
	}

	inline bool removePredecessorTask(int id, const Task& predecessor){
		return tasks_.removePredecessorTask(id, predecessor);
	}

	inline QDate getTaskBeginning(int id){
		return tasks_.getTaskBeginning(id);
	}

	inline bool setTaskBeginning(int id, const QDate& date){
		return tasks_.setTaskBeginning(id, date);
	}

	inline int getTaskDuration(int id){
		return tasks_.getTaskDuration(id);
	}

	inline bool setTaskDuration(int id, int duration){
		return tasks_.setTaskDuration(id, duration);
	}

	inline bool setTaskName(int id, const std::string& newname){
		return tasks_.setTaskName(id, newname);
	}

	inline std::string getTaskName(int id){
		return tasks_.getTaskName(id);
	}

	inline bool addStopDay(int id, const QDate& date){
		return tasks_.addStopDay(id, date);
	}

	inline bool removeStopDay(int id, const QDate& date){
		return tasks_.removeStopDay(id, date);
	}

	inline QDate getTaskEnd(int id){
		return tasks_.getTaskEnd(id);
	}

	//Files:

	inline bool loadFile(const std::string& name){
		file_name_ = name;
		// FIXME
		return true;
	}

	inline int getTasksNumber() const {
		return tasks_.getTasksNumber();
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
	Resources resources_;

	/// List of tasks:
	Tasks tasks_;

	/// List of holidays:
	Calendar holidays_;

	/// Project name:
	std::string name_;

	/// Path of the project file name:
	std::string file_name_;

	Allocation allocations_;
};

#endif // PROJECT_HPP
