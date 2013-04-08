#include "tasks.hpp"
#include "task.hpp"

#include <iostream>


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
			// In case of parent, reparent the children:
			for (int ch = 0; ch < t->getChildrenNumber(); ++ch)
				t->getChildrenSequentially(ch)->setParent(0);
			tasks_.erase(i);
			return t;
		}
	return 0;
}

Task* Tasks::removeTask(Task* t)
{
	return removeTask(t->getId());
}


bool Tasks::addTask(Task* t)
{
	if (getTaskFromId(t->getId()) == 0){
		tasks_.push_back(t);
		return true;
	} else {
		return false;
	}
}


bool Tasks::addChildTask(int id, Task* child)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->addChild(child);
}

Task* Tasks::getParentTask(int child_id)
{
	Task* t = getTaskFromId(child_id);
	if (t == 0)
		return 0;
	return t->getParent();
}

bool Tasks::addPredecessorTask(int id, Task* predecessor)
{
	Task* t = getTaskFromId(id);
	if (t == 0)
		return false;
	return t->addPredecessor(predecessor);
}

bool Tasks::removeChildTask(Task* child)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i){
		std::cout << "Checking task " << (*i)->getId() << std::endl;
		if ((*i)->getParent() != 0)
			continue;
		for (int c = 0; c < (*i)->getChildrenNumber(); ++c){
			std::cout << "Found child" << (*i)->getChildrenSequentially(c)->getId() << std::endl;
			Task* ch = (*i)->getChildrenSequentially(c);
			if ((ch->getId()) == (child->getId())){
				(*i)->removeChild(ch);
				return true;
			}
		}
	}
	return false;
}

Task* Tasks::removePredecessorTask(int id, Task* predecessor)
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
