#include <iostream>


#include "set.hpp"
#include "hierarchitem.hpp"

HierarchItem* Set::getFromId(int id) const
{
	for (typename std::vector<HierarchItem*>::const_iterator i = objects_.begin();
	     i != objects_.end(); ++i)
		if ((*i)->getId() == id)
			return *i;
	std::cerr << "Id not found!" << std::endl;
	return 0;
}

HierarchItem* Set::getSequentially(int position) const
{
	return objects_.at(position);
}

bool Set::remove(int id)
{
	for (typename std::vector<HierarchItem*>::iterator i = objects_.begin();
	     i != objects_.end(); ++i)
		if ((*i)->getId() == id){
			HierarchItem* t = (*i);
			// In case of parent, reparent the children:
			for (int ch = 0; ch < t->getChildrenSize(); ++ch)
				t->getChildrenSequentially(ch)->setParent(0);
			objects_.erase(i);
			return true;
		}
	return false;
}


bool Set::add(HierarchItem* t)
{
	for (typename std::vector<HierarchItem*>::iterator i = objects_.begin();
	     i != objects_.end(); ++i)
		if ((*i)->getId() == t->getId())
			return false;
	objects_.push_back(t);
	return true;
}


bool Set::addChild(int id, HierarchItem* child)
{
	HierarchItem* t = getFromId(id);
	if (t == 0)
		return false;
	return t->addChild(child);
}

HierarchItem* Set::getParent(int child_id) const
{
	HierarchItem* t = getFromId(child_id);
	if (t == 0) {
		std::cerr << "Parent not found!" << std::endl;
		return 0;
	}
	return t->getParent();
}

bool Set::removeChild(int child_id)
{
	for (typename std::vector<HierarchItem*>::iterator i = objects_.begin();
	     i != objects_.end(); ++i){
		for (int c = 0; c < (*i)->getChildrenSize(); ++c){
			std::cout << "Found child" << (*i)->getChildrenSequentially(c)->getId() << std::endl;
			if ((*i)->getChildrenSequentially(c)->getId() == child_id){
				(*i)->removeChild((*i)->getChildrenSequentially(c));
				return true;
			}
		}
	}
	return false;
}

bool Set::setName(int id, const std::string& newname)
{
	HierarchItem* t = getFromId(id);
	if (t == 0)
		return false;
	t->setName(newname);
	return true;
}

std::string Set::getName(int id) const
{
	HierarchItem* t = getFromId(id);
	if (t == 0)
		return "";
	return t->getName();
}

bool Set::removeChild(HierarchItem* child)
{
	return removeChild(child->getId());
}

bool Set::remove(HierarchItem* t)
{
	return remove(t->getId());
}

int Set::getSize() const
{
	return objects_.size();
}
