#include "task.hpp"


bool Task::addChild(Task* child)
{
    for (std::vector<Task*>::iterator i = children_.begin();
        i != children_.end(); ++i)
        if ((*i)->getName() == child->getName()){
                return false;
         }
    children_.push_back(child);
    return true;
}

bool Task::removeChild(const Task& child)
{
    for (std::vector<Task*>::iterator i = children_.begin();
	i != children_.end(); ++i)
	if ((*i)->getName() == child.getName()){
		children_.erase(i);
		return true;
	 }
    return false;
}

bool Task::addPredecessor(Task* predecessor)
{
    for (std::vector<Task*>::iterator i = predecessors_.begin();
        i != predecessors_.end(); ++i)
	if ((*i)->getName() == predecessor->getName()){
                return false;
         }
    predecessors_.push_back(predecessor);
    return true;
}


bool Task::removePredecessor(const Task& predecessor)
{
    for (std::vector<Task*>::iterator i = predecessors_.begin();
	i != predecessors_.end(); ++i)
	if ((*i)->getName() == predecessor.getName()){
		predecessors_.erase(i);
		return true;
	 }
    return false;
}


QDate Task::getEnd()
{
	QDate end = begin_;
	int remaining_days = duration_;
	while (remaining_days > 0){
		end.addDays(1);
		if ((end.dayOfWeek()) < 6 && (stop_days_.checkDate(end) == false))
			remaining_days--;
	}
	return end;
}
