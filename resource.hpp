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

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

#include "hierarchitem.hpp"
#include "set.hpp"

class Resource: public HierarchItem
{
public:
	Resource(const std::string& name, const std::string& role):
	    HierarchItem(name), role_(role){}

	Resource(const std::string& name):
	    HierarchItem(name), role_("") {}

	inline std::string getRole () const{
		return role_;
	}

	inline void setRole (const std::string& role){
		role_ = role;
	}

	virtual inline Resource* getChildrenSequentially(int position) const {
		return static_cast<Resource*> (HierarchItem::getChildrenSequentially(position));
	}

private:
	Resource();

	/// Role of the resource (optional):
	std::string role_;

};

#endif // RESOURCE_HPP
