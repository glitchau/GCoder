#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	gcoder = new GCoder_Widget(this);
	setCentralWidget(gcoder);
	//ui.centralwidget = gcoder;

}

MainWindow::~MainWindow()
{
	//std::cout << "Killer Process" << std::endl;
}
