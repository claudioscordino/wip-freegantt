#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <vector>

#include "resource.hpp"

class Resources
{
public:
	Resources(){}
	~Resources();

	Resource* getResource(int id);

	bool removeResource(int id);

	int addResource(const std::string& name, const std::string& role);

	inline int addResource(const std::string& name){
		return addResource (name, "");
	}

	bool setResourceRole(int id, const std::string& role);

	std::string getResourceRole(int id);

	bool setResourceName(int id, const std::string& newname);

	std::string getResourceName(int id);
private:
	/// List of resources:
	std::vector<Resource*> resources_;
};

#endif // RESOURCES_HPP
