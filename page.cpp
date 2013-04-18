#include <QStringList>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QAction>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QtGui>

#include <iostream>

#include "page.hpp"

Page::Page(Project* project, QMainWindow *parent) :
	QWidget(parent),
	project_(project),
	parent_(parent),
	table_(0),
	view_(0),
	toolbar_(0)
{}


void Page::createPage()
{
	this->createActions();
	this->createTable();
	this->createScene();
	this->createToolbar();
	this->createLayout();
}





