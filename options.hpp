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
