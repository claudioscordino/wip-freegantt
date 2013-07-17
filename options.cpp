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

#include "options.hpp"
#include "mainwindow.hpp"


Options::Options(MainWindow* parent):
    QDialog(parent){
	setWindowTitle(tr("Options"));
	setFixedHeight(150);
	setFixedWidth(400);

	QVBoxLayout* leftLayout = new QVBoxLayout;

	QHBoxLayout* weekDayLayout = new QHBoxLayout;
	firstDayBox_ = new QComboBox;
	firstDayBox_->addItem(tr("Monday"), Qt::Monday);
	firstDayBox_->addItem(tr("Tuesday"), Qt::Tuesday);
	firstDayBox_->addItem(tr("Wednesday"), Qt::Wednesday);
	firstDayBox_->addItem(tr("Thursday"), Qt::Thursday);
	firstDayBox_->addItem(tr("Friday"), Qt::Friday);
	firstDayBox_->addItem(tr("Saturday"), Qt::Saturday);
	firstDayBox_->addItem(tr("Sunday"), Qt::Sunday);
	firstDayBox_->setCurrentIndex(0);

	QLabel* firstDayLabel = new QLabel(tr("Week starts on:"));
	firstDayLabel->setBuddy(firstDayBox_);

	weekDayLayout->addWidget(firstDayLabel);
	weekDayLayout->addWidget(firstDayBox_);
	leftLayout->addLayout(weekDayLayout);

	showGridBox_ = new QCheckBox(tr("Show &Grid"));
	showGridBox_->setChecked(true);
	leftLayout->addWidget(showGridBox_);

	QPushButton* closeButton = new QPushButton(tr("Ok"), this);
	connect(closeButton, SIGNAL(clicked()), this, SLOT(closePanel()));
	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightLayout->addStretch();
	rightLayout->addWidget(closeButton);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
}
