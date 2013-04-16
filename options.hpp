#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class Options: public QDialog
{
	Q_OBJECT

public:
	Options(QWidget* parent = 0):
	    QDialog(parent) {
		setWindowTitle(tr("Options"));
		setFixedHeight(150);
		setFixedWidth(400);

		QVBoxLayout* leftLayout = new QVBoxLayout;
		firstDaySundayCheckBox_ = new QCheckBox(tr("First day of week is Sunday"), this);
		leftLayout->addWidget(firstDaySundayCheckBox_);

		closeButton_ = new QPushButton(tr("Ok"), this);
		connect(closeButton_, SIGNAL(clicked()), this, SLOT(closePanel()));
		QVBoxLayout* rightLayout = new QVBoxLayout;
		rightLayout->addStretch();
		rightLayout->addWidget(closeButton_);

		QHBoxLayout* mainLayout = new QHBoxLayout;
		mainLayout->addLayout(leftLayout);
		mainLayout->addLayout(rightLayout);
		setLayout(mainLayout);
	}

private slots:
	void closePanel(){
		this->setVisible(false);
	}

private:
	QCheckBox* firstDaySundayCheckBox_;
	QPushButton* closeButton_ ;

};

#endif // OPTIONS_HPP
