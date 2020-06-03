#pragma once
#include "ui_gcoder_widget.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

class GCoder_Widget : public QWidget {
	Q_OBJECT

public:
	explicit GCoder_Widget(QWidget* parent = nullptr);
	~GCoder_Widget();

private: //functions
	Ui::GCoder ui;

	void loadSettings();

	void saveSettings();

	void updateGraphic();

private slots:

	void handleButton();
	void on_Columns_spinBox_valueChanged();
	void on_printer_pushButton_pressed();

private: //variables
	QString m_sSettingsFile;

	QLabel* m_pLabel;
	QLineEdit* m_pEdit;

};