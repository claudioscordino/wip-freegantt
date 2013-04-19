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
		std::cerr << "Current index: " << firstDayOfWeek_->currentIndex() << std::endl;
		return Qt::DayOfWeek(1+firstDayOfWeek_->currentIndex());
	}

private slots:
	void closePanel();

private:
	QComboBox* firstDayOfWeek_;
	QLabel* firstDayLabel_;
	QPushButton* closeButton_ ;
	MainWindow* parent_;

};

#endif // OPTIONS_HPP
