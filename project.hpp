/*
 * Copyright (C) 2013 Claudio Scordino
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>
#include <QDate>

#include "calendar.hpp"
#include "allocation.hpp"

class Project
{
public:

	Project():
	    file_name_("")
		{}
	~Project(){}

	// Resources:

	inline Resource* getResourceFromId(int id){
		return static_cast<Resource*> (resources_.getFromId(id));
	}

	inline bool removeResource(int id){
		Resource* r = static_cast<Resource*>(resources_.getFromId(id));
		// In case of child, remove from parent's children:
		if (r->getParent() != 0)
			r->getParent()->removeChild(r);
		// Then, remove the resource:

		return resources_.remove(id);
	}

	inline int addResource(Resource* r){
		return resources_.add(r);
	}

	inline void setResourceRole(int id, const std::string& role){
		Resource* r = static_cast<Resource*> (resources_.getFromId(id));
		r->setRole(role);
	}

	inline std::string getResourceRole(int id){
		Resource* r = static_cast<Resource*> (resources_.getFromId(id));
		return r->getRole();
	}

	inline bool setResourceName(int id, const std::string& newname){
		return resources_.setName(id, newname);
	}

	inline std::string getResourceName(int id){
		return resources_.getName(id);
	}

	inline int getResourcesSize() const {
		return resources_.getSize();
	}

	inline Resource* getResourcesSequentially(int position){
		return static_cast<Resource*>(resources_.getSequentially(position));
	}

	inline bool addChildResource(int id, Resource* child){
		return resources_.addChild(id, child);
	}

	inline bool removeChildResource(Resource* child){
		return resources_.removeChild(child);
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

	inline Task* getTaskFromId(int id){
		return static_cast<Task*>(tasks_.getFromId(id));
	}

	inline Task* getTaskSequentially(int position){
		return static_cast<Task*>(tasks_.getSequentially(position));
	}

	inline bool removeTask(int id){
		Task* t = static_cast<Task*>(tasks_.getFromId(id));
		// In case of child, remove from parent's children:
		if (t->getParent() != 0)
			t->getParent()->removeChild(t);
		// Then, remove the task:
		return tasks_.remove(id);
	}

	inline int addTask (Task* t){
		return tasks_.add(t);
	}

	inline bool addChildTask(int id, Task* child){
		return tasks_.addChild(id, child);
	}

	inline bool addPredecessorTask(int id, Task* predecessor){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->addPredecessor(predecessor);
	}

	inline bool removeChildTask(Task* child){
		return tasks_.removeChild(child);
	}

	inline bool removePredecessorTask(int id, Task* predecessor){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->removePredecessor(predecessor);
	}

	inline QDate getTaskBeginning(int id){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->getBegin();
	}

	inline bool setTaskBeginning(int id, const QDate& date){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->setBegin(date);
	}

	inline int getTaskDuration(int id){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->getDuration();
	}

	inline bool setTaskDuration(int id, int duration){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->setDuration(duration);
	}

	inline bool setTaskName(int id, const std::string& newname){
		return tasks_.setName(id, newname);
	}

	inline std::string getTaskName(int id){
		return tasks_.getName(id);
	}

	inline bool addStopDay(int id, const QDate& date){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->addStopDay(date);
	}

	inline bool removeStopDay(int id, const QDate& date){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->removeStopDay(date);
	}

	inline QDate getTaskEnd(int id){
		Task* t = static_cast<Task*> (tasks_.getFromId(id));
		return t->getEnd();
	}

	inline int getTasksSize() const {
		return tasks_.getSize();
	}


	//Files:

	inline bool load(const std::string& file){
		file_name_ = file;
		// TODO: load file
		return true;
	}

	inline bool save(){
		// TODO: save to file
		return true;
	}

	inline std::string getFileName() {
		return file_name_;
	}

	inline void setFileName(const std::string& file) {
		file_name_ = file;
	}


	// Allocation:

	inline void allocate(int task_id, int resource_id, int percentage) {
		allocations_.allocate(task_id, resource_id, percentage);
	}

	inline bool deallocate(int task_id, int resource_id) {
		return allocations_.deallocate(task_id, resource_id);
	}

	inline std::vector<int> getTaskResources(int task_id) {
		return allocations_.getTaskResources(task_id);
	}

	inline Task* getParentTask(int child_task_id) const {
		return static_cast<Task*>(tasks_.getParent(child_task_id));
	}

	inline Resource* getParentResource(int child_resource_id) const {
		return static_cast<Resource*>(resources_.getParent(child_resource_id));
	}


private:
	/// List of resources:
	Set resources_;

	/// List of tasks:
	Set tasks_;

	/// List of holidays:
	Calendar holidays_;

	/// Path of the project file name:
	std::string file_name_;

	Allocation allocations_;
};

#endif // PROJECT_HPP
