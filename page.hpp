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

#ifndef PAGE_HPP
#define PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QGraphicsView>

#include "project.hpp"

class Page : public QWidget
{
	Q_OBJECT
public:
	explicit Page(Project* project, QMainWindow *parent = 0);
	virtual void refreshTable()=0;
	virtual ~Page(){
		delete table_;
	}
	inline void showGrid(bool show){
		table_->setShowGrid(show);
	}
	
public slots:
	virtual void newItem()=0;
	virtual void removeItem()=0;
	virtual void indentItem()=0;
	virtual void deindentItem()=0;

protected slots:
	virtual void valueChanged(int row, int column)=0;
	virtual void valueClicked(int row, int column)=0;


protected:
	void createPage();
	virtual void createTable()=0;
	virtual void createScene()=0;
	virtual void createToolbar()=0;
	virtual void createLayout()=0;
	virtual void createActions()=0;

	Project* project_;
	QMainWindow* parent_;

	QAction* indentItemAction_;
	QAction* deindentItemAction_;
	QAction* newItemAction_;
	QAction* deleteItemAction_;

	QTableWidget* table_;
	QGraphicsView* view_;
	QToolBar* toolbar_;
};

#endif // PAGE_HPP
