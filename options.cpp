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
