#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

#include "object.hpp"

class Resource: public Object
{
public:
	Resource(const std::string& name, const std::string& role):
	    Object(name), role_(role){}

	Resource(const std::string& name):
	    Object(name), role_("") {}

	inline std::string getRole () const{
		return role_;
	}

	inline void setRole (const std::string& role){
		role_ = role;
	}

private:
	Resource();

	/// Role of the resource (optional):
	std::string role_;

};

#endif // RESOURCE_HPP
