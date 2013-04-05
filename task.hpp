#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
//#include <QColor>
#include <QDate>

//#include "resource.hpp"
#include "calendar.hpp"

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

	bool removeStopDay(const QDate& date){
		return stop_days_.removeDate(date);
	}

	bool addChild(Task* child);

	bool removeChild(const Task& child);

	bool addPredecessor(Task* predecessor);

	bool removePredecessor(const Task& predecessor);

	QDate getEnd();

	inline int getId(){
		return id_;
	}

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
