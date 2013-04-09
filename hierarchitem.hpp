#ifndef HIERARCHITEM_HPP
#define HIERARCHITEM_HPP

#include <string>
#include <vector>

#include "item.hpp"
#include "set.hpp"

class HierarchItem: public Item
{
public:
	HierarchItem(const std::string& name):
		Item(name){}

	inline void setParent(HierarchItem* p){
		parent_ = p;
	}

	inline HierarchItem* getParent() const {
		return parent_;
	}

	inline int getChildrenSize() const {
		return children_.getSize();
	}

	virtual inline HierarchItem* getChildrenSequentially(int position) const {
		return children_.getSequentially(position);
	}

	inline bool addChild(HierarchItem* child) {
		return children_.add(child);
	}

	inline bool removeChild(HierarchItem* child){
		return children_.remove(child);
	}

private:

	/// Children of the object:
	Set<HierarchItem> children_;

	/// Parent in case it is a child
	HierarchItem* parent_;
};

#endif // HIERARCHITEM_HPP
