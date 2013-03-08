#include "project.hpp"

Project* Project::instance_ = 0;

Project* Project::getInstance()
{
    if (instance_ == 0)
	    instance_ = new Project;
    return instance_;
}
