#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow;


class Options: public QDialog
{
	Q_OBJECT

public:
	Options(MainWindow* parent = 0);

	Qt::DayOfWeek getFirstDayOfWeek(){
		if (firstDaySundayCheckBox_->isChecked())
			return Qt::DayOfWeek(7);
		else
			return Qt::DayOfWeek(1);
	}

private slots:
	void closePanel();

private:
	QCheckBox* firstDaySundayCheckBox_;
	QPushButton* closeButton_ ;
	MainWindow* parent_;

};

#endif // OPTIONS_HPP
