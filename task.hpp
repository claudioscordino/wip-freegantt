#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
//#include <QColor>
#include <QDate>

//#include "resource.hpp"
#include "calendar.hpp"
#include "tasks.hpp"

class Task
{
public:
	Task(const std::string& name):
	    name_(name),
	    begin_(QDate::currentDate()),
	    duration_(0){
		id_ = next_id_;
		next_id_++;
	}

	inline std::string getName() const {
		return name_;
	}

	inline void setName(const std::string& name ) {
		name_ = name;
	}

	inline QDate getBegin() const {
		return begin_;
	}

	inline bool setBegin(const QDate& d){
		if (d.isValid() == false)
			return false;
		begin_ = d;
		return true;
	}

	inline int getDuration(){
		return duration_;
	}


	inline bool setDuration(int duration){
		if (duration < 0)
			return false;
		duration_ = duration;
		return true;
	}

	inline bool addStopDay(const QDate& date){
		return stop_days_.addDate(date);
	}

	inline bool removeStopDay(const QDate& date){
		return stop_days_.removeDate(date);
	}

	inline bool addChild(Task* child){
		return children_.addTask(child);
	}

	inline Task* removeChild(const Task& child){
		return children_.removeTask(child);
	}

	inline bool addPredecessor(Task* predecessor){
		return predecessors_.addTask(predecessor);
	}

	inline Task* removePredecessor(const Task& predecessor){
		return predecessors_.removeTask(predecessor);
	}

	QDate getEnd();

	inline int getId() const{
		return id_;
	}

	inline int getChildrenNumber() const{
		return children_.getTasksNumber();
	}

	inline int getPredecessorsNumber() const{
		return predecessors_.getTasksNumber();
	}

	inline Task* getChildrenSequentially(int position){
		return children_.getTaskSequentially(position);
	}

	inline Task* getPredecessorsSequentially(int position){
		return predecessors_.getTaskSequentially(position);
	}


private:
	Task();

	/// Name of the task:
	std::string name_;

	/// Children of the task:
	Tasks children_;

	/// Predecossors of the task:
	Tasks predecessors_;

	/// Begin of the task:
	QDate begin_;

	/// Duration:
	int duration_;

	/// Stop days:
	Calendar stop_days_;

	/// Task id:
	unsigned int id_;

	/// Id generator;
	static int next_id_;
};

#endif // TASK_HPP
