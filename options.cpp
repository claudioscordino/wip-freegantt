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

	QHBoxLayout* weekDayLayout = new QHBoxLayout;
	firstDayOfWeek_ = new QComboBox;
	firstDayOfWeek_->addItem(tr("Monday"), Qt::Monday);
	firstDayOfWeek_->addItem(tr("Tuesday"), Qt::Tuesday);
	firstDayOfWeek_->addItem(tr("Wednesday"), Qt::Wednesday);
	firstDayOfWeek_->addItem(tr("Thursday"), Qt::Thursday);
	firstDayOfWeek_->addItem(tr("Friday"), Qt::Friday);
	firstDayOfWeek_->addItem(tr("Saturday"), Qt::Saturday);
	firstDayOfWeek_->addItem(tr("Sunday"), Qt::Sunday);
	firstDayOfWeek_->setCurrentIndex(0);

	QLabel* firstDayLabel = new QLabel(tr("Wee&k starts on:"));
	firstDayLabel->setBuddy(firstDayOfWeek_);

	weekDayLayout->addWidget(firstDayLabel);
	weekDayLayout->addWidget(firstDayOfWeek_);
	leftLayout->addLayout(weekDayLayout);

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
