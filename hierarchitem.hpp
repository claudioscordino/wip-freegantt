/*
 * Copyright (C) 2013 Claudio Scordino
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
		Item(name), parent_(0){}

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
		child->setParent(this);
		return children_.add(child);
	}

	inline bool removeChild(HierarchItem* child){
		child->setParent(0);
		return children_.remove(child);
	}

private:

	/// Children of the object:
	Set children_;

	/// Parent in case it is a child
	HierarchItem* parent_;
};

#endif // HIERARCHITEM_HPP
