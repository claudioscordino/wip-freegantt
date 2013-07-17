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

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>

#include "item.hpp"


class Item
{
public:
	Item(const std::string& name):
		name_(name){
		id_ = next_id_;
		next_id_++;
	}

	inline std::string getName() const {
		return name_;
	}

	inline void setName(const std::string& name ) {
		name_ = name;
	}

	inline int getId() const{
		return id_;
	}

private:
	/// Name of the object:
	std::string name_;

	/// Id of this kind of object:
	unsigned int id_;

	/// Id generator;
	static int next_id_;

};

#endif // OBJECT_HPP
