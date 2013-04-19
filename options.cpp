#include "options.hpp"
#include "mainwindow.hpp"

void Options::closePanel()
{
	parent_->updateOptions();
	this->setVisible(false);
}

Options::Options(MainWindow* parent):
    QDialog(parent),
    parent_(parent){
	setWindowTitle(tr("Options"));
	setFixedHeight(150);
	setFixedWidth(400);

	QVBoxLayout* leftLayout = new QVBoxLayout;

	firstDayOfWeek_ = new QComboBox;
	firstDayOfWeek_->addItem(tr("Monday"), Qt::Monday);
	firstDayOfWeek_->addItem(tr("Tuesday"), Qt::Tuesday);
	firstDayOfWeek_->addItem(tr("Wednesday"), Qt::Wednesday);
	firstDayOfWeek_->addItem(tr("Thursday"), Qt::Thursday);
	firstDayOfWeek_->addItem(tr("Friday"), Qt::Friday);
	firstDayOfWeek_->addItem(tr("Saturday"), Qt::Saturday);
	firstDayOfWeek_->addItem(tr("Sunday"), Qt::Sunday);

	firstDayOfWeek_->setCurrentIndex(0);

	firstDayLabel_ = new QLabel(tr("Wee&k starts on:"));
	firstDayLabel_->setBuddy(firstDayOfWeek_);

	leftLayout->addWidget(firstDayOfWeek_);
	leftLayout->addWidget(firstDayLabel_);


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
