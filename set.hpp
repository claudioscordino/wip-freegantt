#ifndef SET_HPP
#define SET_HPP

#include <iostream>

template <class T>
class Set
{
public:
	Set(){}

	inline T* getFromId(int id) const {
		for (typename std::vector<T*>::const_iterator i = objects_.begin();
		     i != objects_.end(); ++i)
			if ((*i)->getId() == id)
				return *i;
		return 0;
	}

	inline T* getSequentially(int position) const {
		return objects_.at(position);
	}

	inline bool remove(int id){
		for (typename std::vector<T*>::iterator i = objects_.begin();
		     i != objects_.end(); ++i)
			if ((*i)->getId() == id){
				T* t = (*i);
				// In case of parent, reparent the children:
				for (int ch = 0; ch < t->getChildrenSize(); ++ch)
					t->getChildrenSequentially(ch)->setParent(0);
				objects_.erase(i);
				return true;
			}
		return false;
	}


	inline bool add(T* t){
		for (typename std::vector<T*>::iterator i = objects_.begin();
		     i != objects_.end(); ++i)
			if ((*i)->getId() == t->getId())
				return false;
		objects_.push_back(t);
		return true;
	}


	inline bool addChild(int id, T* child) {
		T* t = getFromId(id);
		if (t == 0)
			return false;
		return t->addChild(child);
	}

	inline T* getParent(int child_id) const {
		T* t = getFromId(child_id);
		if (t == 0)
			return 0;
		return t->getParent();
	}

	inline bool removeChild(int child_id){
		for (typename std::vector<T*>::iterator i = objects_.begin();
		     i != objects_.end(); ++i){
			for (int c = 0; c < (*i)->getChildrenSize(); ++c){
				std::cout << "Found child" << (*i)->getChildrenSequentially(c)->getId() << std::endl;
				if ((*i)->getChildrenSequentially(c)->getId() == child_id){
					(*i)->removeChild((*i)->getChildrenSequentially(c));
					return true;
				}
			}
		}
		return false;
	}

	inline bool setName(int id, const std::string& newname){
		T* t = getFromId(id);
		if (t == 0)
			return false;
		t->setName(newname);
		return true;
	}

	inline std::string getName(int id) const {
		T* t = getFromId(id);
		if (t == 0)
			return "";
		return t->getName();
	}

	inline bool removeChild(T* child){
		return removeChild(child->getId());
	}

	inline bool remove(T* t){
		return remove(t->getId());
	}

	inline int getSize() const{
		return objects_.size();
	}

private:
	std::vector<T*> objects_;

};

#endif // SET_HPP
