#pragma once
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

class Mainwindow : public QWidget {
	Q_OBJECT

public:
	explicit Mainwindow(QWidget* parent = nullptr);
	~Mainwindow();

private: //functions
	Ui::GCoder ui;

	void loadSettings();

	void saveSettings();

	void updateGraphic();

private slots:

	void handleButton();
	void on_Columns_spinBox_valueChanged();

private: //variables
	QString m_sSettingsFile;

	QLabel* m_pLabel;
	QLineEdit* m_pEdit;

};