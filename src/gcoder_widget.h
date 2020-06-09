#ifndef GCODER_WIDGET_H
#define GCODER_WIDGET_H
#include "ui_gcoder_widget.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QComboBox>
#include <QMessageBox>
#include "gcode.h"

class GCoder_Widget : public QWidget {
	Q_OBJECT

public:
	explicit GCoder_Widget(QWidget* parent = nullptr);
	~GCoder_Widget();

private: //functions
	Ui::GCoder ui;

	void loadSettings();

	void saveSettings();

	//void updateGraphic();

	void addGCommand();

	void addGCommand(std::string input, std::map<std::string, std::string> x = std::map<std::string,std::string>());

	void updateGParameters(std::string input, QTreeWidgetItem* item, std::map<std::string, std::string> x = std::map<std::string, std::string>());
	
	double px2mm(int px);
	int mm2px(double mm);


private slots:

	void handleButton();
	void on_printer_pushButton_pressed();
	void on_add_pushButton_pressed();
	void on_remove_pushButton_pressed();
	void on_pushButton_pressed();
	void on_clear_pushButton_pressed();
	void yourfunction(QString v);
	void updateGraphic();
	void generate();

private: //variables
	QString m_sSettingsFile;

	QLabel* m_pLabel;
	QLineEdit* m_pEdit;
	GCode gcode;

	QGraphicsScene* scene;

	int printerX = 100, printerY = 100;
	int distProngs = 5;
};
#endif