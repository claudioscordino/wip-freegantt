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
