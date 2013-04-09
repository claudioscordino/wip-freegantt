#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <QDate>

#include "calendar.hpp"
#include "hierarchitem.hpp"
#include "set.hpp"

class Task: public HierarchItem
{
public:
	Task(const std::string& name):
	    HierarchItem(name),
	    begin_(QDate::currentDate()),
	    duration_(0){}

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

	inline bool addPredecessor(Task* predecessor){
		return predecessors_.add(predecessor);
	}

	inline bool removePredecessor(Task* predecessor){
		return predecessors_.remove(predecessor);
	}

	QDate getEnd();

	inline int getPredecessorsSize() const{
		return predecessors_.getSize();
	}

	inline Task* getPredecessorsSequentially(int position){
		return static_cast<Task*>(predecessors_.getSequentially(position));
	}

	virtual inline Task* getChildrenSequentially(int position) const {
		return static_cast<Task*> (HierarchItem::getChildrenSequentially(position));
	}

private:
	Task();

	/// Predecessors of the task:
	Set<Task> predecessors_;

	/// Begin of the task:
	QDate begin_;

	/// Duration:
	int duration_;

	/// Stop days:
	Calendar stop_days_;
};

#endif // TASK_HPP
