#include "calendar.hpp"


bool Calendar::addDate(const QDate& date, const std::string& name)
{
	for (std::vector<Date*>::iterator i = dates_.begin();
	    i != dates_.end(); ++i)
		if ((*i)->date_ == date)
		    return false;
	Date* d = new Date;
	d->date_ = date;
	d->name_ = name;
	dates_.push_back(d);
	return true;
}


bool Calendar::removeDate(const QDate& date)
{
	for (std::vector<Date*>::iterator i = dates_.begin();
	    i != dates_.end(); ++i)
		if ((*i)->date_ == date){
			Date* d = (*i);
			dates_.erase(i);
			delete d;
			return true;
		}
	return false;
}


bool Calendar::checkDate(const QDate& date)
{
	for (std::vector<Date*>::iterator i = dates_.begin();
	    i != dates_.end(); ++i)
		if ((*i)->date_ == date){
			return true;
		}
	return false;
}

