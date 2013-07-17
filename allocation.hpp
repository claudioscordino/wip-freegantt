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

#ifndef ALLOCATION_HPP
#define ALLOCATION_HPP

#include <map>

#include "task.hpp"
#include "resource.hpp"



class Allocation
{
public:
	Allocation(){}
	~Allocation();
	void allocate(int task_id, int resource_id, int percentage);
	bool deallocate(int task_id, int resource_id);
	std::vector<int> getTaskResources(int task_id);

private:
	struct TaskAllocation {
		int task_id_;
		int resource_id_;
		int percentage_; // 0 - 100
	};

	std::vector<TaskAllocation*> allocations_;
};

#endif // ALLOCATION_HPP
