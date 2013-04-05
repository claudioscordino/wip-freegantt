#include "project.hpp"

Project::~Project()
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		delete(*i);

	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		delete(*i);
}

Resource* Project::getResource(int id)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

bool Project::removeResource(int id)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getId() == id){
			Resource* r = (*i);
			resources_.erase(i);
			delete r;
			return true;
		}
	return false;
}


int Project::addResource(const std::string& name, const std::string& role)
{
	Resource * r = new Resource (name, role);
	resources_.push_back(r);
	return r->getId();
}

bool Project::setResourceRole(int id, const std::string& role)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return false;
	}
	r->setRole(role);
	return true;
}

std::string Project::getResourceRole(int id)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return "";
	}
	return r->getRole();
}


bool Project::setResourceName(int id, const std::string& newname)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return false;
	}
	r->setName(newname);
	return true;
}

std::string Project::getResourceName(int id)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return "";
	}
	return r->getName();
}


// Tasks:

Task* Project::getTask(int id)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

bool Project::removeTask(int id)
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



int Project::addTask(const std::string& name)
{
	Task* t = new Task (name);
	tasks_.push_back(t);
	return t->getId();
}


bool Project::addChildTask(int id, Task* child)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addChild(child);
}

bool Project::addPredecessorTask(int id, Task* predecessor)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addPredecessor(predecessor);
}

bool Project::removeChildTask(int id, const Task& child)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removeChild(child);
}

bool Project::removePredecessorTask(int id, const Task& predecessor)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removePredecessor(predecessor);
}



bool Project::setTaskBeginning(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->setBegin(date);
}

bool Project::setTaskDuration(int id, int duration)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->setDuration(duration);
}

QDate Project::getTaskEnd(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getEnd();
}

QDate Project::getTaskBeginning(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return QDate::currentDate();
	return t->getBegin();
}

int Project::getTaskDuration(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return 0;
	return t->getDuration();
}

bool Project::setTaskName(int id, const std::string& newname)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	t->setName(newname);
	return true;
}

std::string Project::getTaskName(int id)
{
	Task* t = getTask(id);
	if (t == 0)
		return "";
	return t->getName();
}

bool Project::addStopDay(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->addStopDay(date);
}

bool Project::removeStopDay(int id, const QDate& date)
{
	Task* t = getTask(id);
	if (t == 0)
		return false;
	return t->removeStopDay(date);
}
