/*
 * Copyright (C) 2013 Claudio Scordino
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "calendar.hpp"


Calendar::~Calendar()
{
	for (std::vector<Date*>::iterator i = dates_.begin();
	    i != dates_.end(); ++i)
			delete(*i);
}

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

