#include "tasks.hpp"

Tasks::~Tasks()
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		delete(*i);
}

Task* Tasks::getTask(int id)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

bool Tasks::removeTask(int id)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getId() == id){
			Task* r = (*i);
			tasks_.erase(i);
			delete r;
			return true;
		}
	return false;
}



int Tasks::addTask(const std::string& name)
{
	Task* t = new Task (name);
	tasks_.push_back(t);
	return t->getId();
}


bool Tasks::addChildTask(int id, Task* child)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addChild(child);
}

bool Tasks::addPredecessorTask(int id, Task* predecessor)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addPredecessor(predecessor);
}

bool Tasks::removeChildTask(int id, const Task& child)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removeChild(child);
}

bool Tasks::removePredecessorTask(int id, const Task& predecessor)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removePredecessor(predecessor);
}



bool Tasks::setTaskBeginning(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->setBegin(date);
}

bool Tasks::setTaskDuration(int id, int duration)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->setDuration(duration);
}

QDate Tasks::getTaskEnd(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getEnd();
}

QDate Tasks::getTaskBeginning(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getBegin();
}

int Tasks::getTaskDuration(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return 0;
	return t->getDuration();
}

bool Tasks::setTaskName(int id, const std::string& newname)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	t->setName(newname);
	return true;
}

std::string Tasks::getTaskName(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return "";
	return t->getName();
}

bool Tasks::addStopDay(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addStopDay(date);
}

bool Tasks::removeStopDay(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removeStopDay(date);
}
