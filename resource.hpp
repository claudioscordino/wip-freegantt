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
