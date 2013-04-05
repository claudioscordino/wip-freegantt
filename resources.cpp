#include "resources.hpp"

Resource* Resources::getResourceFromId(int id)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	return 0;
}

Resource* Resources::getResourceSequentially(int position)
{
	return resources_.at(position);
}


Resource* Resources::removeResource(int id)
{
	for (std::vector<Resource*>::iterator i = resources_.begin();
	     i != resources_.end(); ++i)
		if ((*i)->getId() == id){
			Resource* r = (*i);
			resources_.erase(i);
			return r;
		}
	return 0;
}


int Resources::addResource(Resource* r)
{
	resources_.push_back(r);
	return r->getId();
}

bool Resources::setResourceRole(int id, const std::string& role)
{
	Resource* r = getResourceFromId(id);
	if (r == 0) {
		return false;
	}
	r->setRole(role);
	return true;
}

std::string Resources::getResourceRole(int id)
{
	Resource* r = getResourceFromId(id);
	if (r == 0) {
		return "";
	}
	return r->getRole();
}


bool Resources::setResourceName(int id, const std::string& newname)
{
	Resource* r = getResourceFromId(id);
	if (r == 0) {
		return false;
	}
	r->setName(newname);
	return true;
}

std::string Resources::getResourceName(int id)
{
	Resource* r = getResourceFromId(id);
	if (r == 0) {
		return "";
	}
	return r->getName();
}
