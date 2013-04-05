#include "resources.hpp"

Resources::~Resources()
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		delete(*i);
}

Resource* Resources::getResource(int id)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

bool Resources::removeResource(int id)
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


int Resources::addResource(const std::string& name, const std::string& role)
{
	Resource * r = new Resource (name, role);
	resources_.push_back(r);
	return r->getId();
}

bool Resources::setResourceRole(int id, const std::string& role)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return false;
	}
	r->setRole(role);
	return true;
}

std::string Resources::getResourceRole(int id)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return "";
	}
	return r->getRole();
}


bool Resources::setResourceName(int id, const std::string& newname)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return false;
	}
	r->setName(newname);
	return true;
}

std::string Resources::getResourceName(int id)
{
	Resource* r = getResource(id);
	if (r == 0) {
		return "";
	}
	return r->getName();
}
