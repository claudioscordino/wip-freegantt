#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>


class MainWindow;


class Options: public QDialog
{
	Q_OBJECT

public:
	Options(MainWindow* parent = 0);

	Qt::DayOfWeek getFirstDayOfWeek(){
		return Qt::DayOfWeek(1+firstDayOfWeek_->currentIndex());
	}

private slots:
	void closePanel();

private:
	QComboBox* firstDayOfWeek_;
	MainWindow* parent_;

};

#endif // OPTIONS_HPP
