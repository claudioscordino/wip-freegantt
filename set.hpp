#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>

class HierarchItem;

class Set
{
public:
	Set(){}

	HierarchItem* getFromId(int id) const;

	HierarchItem* getSequentially(int position) const;

	bool remove(int id);

	bool add(HierarchItem* t);

	bool addChild(int id, HierarchItem* child);

	HierarchItem* getParent(int child_id) const;

	bool removeChild(int child_id);

	bool setName(int id, const std::string& newname);

	std::string getName(int id) const;

	bool removeChild(HierarchItem* child);

	bool remove(HierarchItem* t);

	int getSize() const;

private:
	std::vector<HierarchItem*> objects_;

};

#endif // SET_HPP
