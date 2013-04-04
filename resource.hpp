#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

class Resource
{
public:
	Resource(const std::string& name, const std::string& role):
		name_(name), role_(role){}

	Resource(const std::string& name):
		name_(name), role_("") {}

	inline std::string getName () const{
		return name_;
	}

	inline void setName (const std::string& name){
		name_ = name;
	}

	inline std::string getRole () const{
		return role_;
	}

	inline void setRole (const std::string& role){
		role_ = role;
	}



private:
	Resource();

	/// Name of the resource:
	std::string name_;

	/// Role of the resource (optional):
	std::string role_;
};

#endif // RESOURCE_HPP
