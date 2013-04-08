#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object
{
public:
	Object(const std::string& name):
		name_(name){
		id_ = next_id_;
		next_id_++;
	}


	inline std::string getName() const {
		return name_;
	}

	inline void setName(const std::string& name ) {
		name_ = name;
	}

	inline int getId() const{
		return id_;
	}

private:
	/// Name of the object:
	std::string name_;

	/// Id of this kind of object:
	unsigned int id_;

	/// Id generator;
	static int next_id_;
};

#endif // OBJECT_HPP
