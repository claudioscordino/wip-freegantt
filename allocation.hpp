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
