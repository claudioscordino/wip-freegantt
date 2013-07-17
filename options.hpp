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

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <iostream>


class MainWindow;


class Options: public QDialog
{
	Q_OBJECT

public:
	Options(MainWindow* parent = 0);

	inline void setFirstDayOfWeek(Qt::DayOfWeek day) {
		firstDayBox_->setCurrentIndex(day-1);
	}

	inline Qt::DayOfWeek getFirstDayOfWeek() const{
		return Qt::DayOfWeek(firstDayBox_->currentIndex()+1);
	}

	inline void setShowGrid(bool show) {
		showGridBox_->setChecked(show);
	}

	inline bool getShowGrid() const{
		return showGridBox_->isChecked();
	}


private slots:
	void closePanel(){
		this->setVisible(false);
		accept();
	}

private:
	QComboBox* firstDayBox_;
	QCheckBox* showGridBox_;
};

#endif // OPTIONS_HPP
