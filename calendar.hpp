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

#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include<QDate>
#include<vector>

class Calendar
{
public:
	Calendar(){}
	~Calendar();

	inline bool addDate(const QDate& date){
		return addDate(date, "");
	}

	bool addDate(const QDate& date, const std::string& name);

	bool removeDate(const QDate& date);

	bool checkDate(const QDate& date);

private:
	struct Date {
		std::string name_;
		QDate date_;
	};

	std::vector<Date*> dates_;
};

#endif // CALENDAR_HPP
