#include "tasks.hpp"
#include "task.hpp"


Task* Tasks::getTaskFromId(int id)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

Task* Tasks::getTaskSequentially(int position)
{
	return tasks_.at(position);
}


Task* Tasks::removeTask(int id)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getId() == id){
			Task* t = (*i);
			tasks_.erase(i);
			return t;
		}
	return 0;
}

Task* Tasks::removeTask(const Task &t)
{
	return removeTask(t.getId());
}


int Tasks::addTask(Task* t)
{
	tasks_.push_back(t);
	return t->getId();
}


bool Tasks::addChildTask(int id, Task* child)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->addChild(child);
}

bool Tasks::addPredecessorTask(int id, Task* predecessor)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->addPredecessor(predecessor);
}

Task* Tasks::removeChildTask(int id, const Task& child)
{
	Task* t = getTaskFromId(id);
	return t->removeChild(child);
}

Task* Tasks::removePredecessorTask(int id, const Task& predecessor)
{
	Task* t = getTaskFromId(id);
	return t->removePredecessor(predecessor);
}



bool Tasks::setTaskBeginning(int id, const QDate& date)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->setBegin(date);
}

bool Tasks::setTaskDuration(int id, int duration)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->setDuration(duration);
}

QDate Tasks::getTaskEnd(int id)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getEnd();
}

QDate Tasks::getTaskBeginning(int id)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getBegin();
}

int Tasks::getTaskDuration(int id)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return 0;
	return t->getDuration();
}

bool Tasks::setTaskName(int id, const std::string& newname)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	t->setName(newname);
	return true;
}

std::string Tasks::getTaskName(int id)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return "";
	return t->getName();
}

bool Tasks::addStopDay(int id, const QDate& date)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->addStopDay(date);
}

bool Tasks::removeStopDay(int id, const QDate& date)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->removeStopDay(date);
}
