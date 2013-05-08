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

	inline Qt::DayOfWeek getFirstDayOfWeek() const{
		return Qt::DayOfWeek(1+firstDayOfWeek_->currentIndex());
	}

	inline bool getShowGrid() const{
		return showGrid_->isChecked();
	}

private slots:
	void closePanel(){
		this->setVisible(false);
	}

private:
	QComboBox* firstDayOfWeek_;
	QCheckBox* showGrid_;

};

#endif // OPTIONS_HPP
