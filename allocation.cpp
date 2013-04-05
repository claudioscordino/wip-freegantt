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
