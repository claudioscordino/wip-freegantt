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

Resource* Project::getResource(const std::string& name)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getName() == name)
			return *i;
	return 0;
}

bool Project::removeResource(const std::string& name)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getName() == name){
			Resource* r = (*i);
			resources_.erase(i);
			delete r;
			return true;
		}
	return false;
}


bool Project::addResource(const std::string& name, const std::string& role)
{
	if (getResource(name) != 0) {
		return false;
	}
	resources_.push_back(new Resource (name, role));
	return true;
}

bool Project::setResourceRole(const std::string& name, const std::string& role)
{
	Resource* r = getResource(name);
	if (r == 0) {
		return false;
	}
	r->setRole(role);
	return true;
}

std::string Project::getResourceRole(const std::string& name)
{
	Resource* r = getResource(name);
	if (r == 0) {
		return "";
	}
	return r->getRole();
}


bool Project::setResourceName(const std::string& oldname, const std::string& newname)
{
	Resource* r = getResource(oldname);
	if (r == 0) {
		return false;
	}
	r->setName(newname);
	return true;
}



Task* Project::getTask(const std::string& name)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getName() == name)
			return *i;
	return 0;
}

bool Project::removeTask(const std::string& name)
{
	for (std::vector<Task*>::iterator i = tasks_.begin();
	     i != tasks_.end(); ++i)
		if ((*i)->getName() == name){
			Task* r = (*i);
			tasks_.erase(i);
			delete r;
			return true;
		}
	return false;
}



bool Project::addTask(const std::string& name)
{
	if (getTask(name) != 0) {
		return false;
	}
	tasks_.push_back(new Task (name));
	return true;
}


bool Project::addChildTask(const std::string& name, Task* child)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->addChild(child);
}

bool Project::addPredecessorTask(const std::string& name, Task* predecessor)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->addPredecessor(predecessor);
}

bool Project::removeChildTask(const std::string& name, const Task& child)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->removeChild(child);
}

bool Project::removePredecessorTask(const std::string& name, const Task& predecessor)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->removePredecessor(predecessor);
}



bool Project::setTaskBeginning(const std::string& name, const QDate& date)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->setBegin(date);
}

bool Project::setTaskDuration(const std::string& name, int duration)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->setDuration(duration);
}

QDate Project::getTaskEnd(const std::string& name)
{
	Task* t = getTask(name);
	if (t == 0)
		return QDate::currentDate();
	return t->getEnd();
}

QDate Project::getTaskBeginning(const std::string& name)
{
	Task* t = getTask(name);
	if (t == 0)
		return QDate::currentDate();
	return t->getBegin();
}

int Project::getTaskDuration(const std::string& name)
{
	Task* t = getTask(name);
	if (t == 0)
		return 0;
	return t->getDuration();
}

bool Project::setTaskName(const std::string& oldname, const std::string& newname)
{
	Task* t = getTask(oldname);
	if (t == 0)
		return false;
	t->setName(newname);
	return true;
}

bool Project::addStopDay(const std::string& name, const QDate& date)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->addStopDay(date);
}

bool Project::removeStopDay(const std::string& name, const QDate& date)
{
	Task* t = getTask(name);
	if (t == 0)
		return false;
	return t->removeStopDay(date);
}
