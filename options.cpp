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
