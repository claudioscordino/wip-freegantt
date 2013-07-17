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

#include "allocation.hpp"

Allocation::~Allocation()
{
	for (std::vector<TaskAllocation*>::iterator i = allocations_.begin();
	     i != allocations_.end(); ++i)
			delete(*i);
}

void Allocation::allocate(int task_id, int resource_id, int percentage)
{
	for (std::vector<TaskAllocation*>::iterator i = allocations_.begin();
	     i != allocations_.end(); ++i)
		if (((*i)->task_id_ == task_id) && ((*i)->resource_id_ == resource_id)){
			(*i)->percentage_ = percentage;
			return;
		}
	TaskAllocation* t = new TaskAllocation;
	t->task_id_ = task_id;
	t->resource_id_ = resource_id;
	t->percentage_ = percentage;
	allocations_.push_back(t);
}

bool Allocation::deallocate(int task_id, int resource_id)
{
	for (std::vector<TaskAllocation*>::iterator i = allocations_.begin();
	     i != allocations_.end(); ++i)
		if (((*i)->task_id_ == task_id) && ((*i)->resource_id_ == resource_id)){
			delete(*i);
			allocations_.erase(i);
			return true;
		}
	return false;
}

std::vector<int> Allocation::getTaskResources(int task_id)
{
	std::vector<int> ret;
	for (std::vector<TaskAllocation*>::iterator i = allocations_.begin();
	     i != allocations_.end(); ++i)
		if ( ((*i)->task_id_) == task_id)
			ret.push_back((*i)->resource_id_);
	return ret;
}
