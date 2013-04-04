#ifndef ALLOCATION_HPP
#define ALLOCATION_HPP

#include <map>

#include "task.hpp"
#include "resource.hpp"



class Allocation
{
public:
        Allocation();
        bool set(const std::string& taskName, Resource* resource, int percentage);
        std::vector<Resource> getResources(const std::string& taskName);

private:
    struct TaskAllocation {
                Resource* resource_;
                int percentage_; // 0 - 100
    };


   std::map<Task*, TaskAllocation*> allocations_;

};

#endif // ALLOCATION_HPP
