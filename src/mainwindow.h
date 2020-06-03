#pragma once
#include "ui_mainwindow.h"
#include "gcoder_widget.h"
#include <QtWidgets>
#include <iostream>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QMainWindow* parent = nullptr);
	~MainWindow();

private: //functions
	Ui::MainWindow ui;
	GCoder_Widget* gcoder;
public:

};