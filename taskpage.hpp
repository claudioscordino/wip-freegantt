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

#ifndef TASKPAGE_HPP
#define TASKPAGE_HPP

#include <QWidget>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QMainWindow>
#include <QGraphicsView>

#include "project.hpp"
#include "page.hpp"

class TaskPage : public Page
{
	Q_OBJECT
public:
	explicit TaskPage(Project* project, QMainWindow *parent = 0);
	virtual void refreshTable();
	void setFirstDayOfWeek(Qt::DayOfWeek day){
		calendar_.setFirstDayOfWeek(day);
	}

public slots:
	virtual void newItem();
	virtual void removeItem();
	virtual void indentItem();
	virtual void deindentItem();

protected slots:
	virtual void valueChanged(int row, int column);
	virtual void valueClicked(int row, int column);

private slots:
	void changeTaskBegin();

private:
	virtual void createTable();
	virtual void createScene();
	virtual void createToolbar();
	virtual void createLayout();
	virtual void createActions();

	QCalendarWidget calendar_;
	int calendarTaskId_;
};

#endif // TASKPAGE_HPP
