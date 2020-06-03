#include "gcoder_widget.h"
#include "ui_gcoder_widget.h"
#include <QSettings>
#include <QFileDialog>


GCoder_Widget::GCoder_Widget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	//m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/demosettings.ini";
	m_sSettingsFile = QApplication::applicationDirPath() + "/demosettings.ini";
	std::cout << m_sSettingsFile.toStdString() << std::endl;
	loadSettings();



	//m_pLabel = new QLabel("", this);
	//m_pLabel->setGeometry(0, 80, 200, 40);
	//m_pEdit = new QLineEdit("", this);
	//m_pEdit->setGeometry(0, 140, 200, 40);
	/*
	if (ui.pushButton)
	{
		connect(ui.pushButton, SIGNAL(released()), this, SLOT(handleButton()));
	}
	*/
	//connect(ui.Columns_spinBox, SIGNAL(changeEvent), this, SLOT(handleButton()));

	QVector <QPointF> points;
	for (int i = 0; i < 80; i++)
		points.append(QPointF(i * 5, i * 5));

	QGraphicsScene* scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);

	//size of bed 120x120
	//120 = 400
	// 400/120 = number of pixels per mm
	// 18 * 400 / 120

	for (int i = 0; i < points.size(); i++)
		scene->addEllipse(points[i].x(), points[i].y(), (int)((18 * 400) / 120), (int)((18 * 400) / 120), QPen(Qt::green));

	int batteryDiameter = 18;

	std::cout << "Battery: " << ((18 * 400) / 120) << std::endl;

	scene->addEllipse(0, 0, 1, 1);


}

GCoder_Widget::~GCoder_Widget()
{
	//std::cout << "Killer Process" << std::endl;
}

void GCoder_Widget::on_Columns_spinBox_valueChanged()
{
	std::cout << "Columns spin" << std::endl;
}

void GCoder_Widget::on_printer_pushButton_pressed() 
{
	std::cout << "Printer Push Button Pressed" << std::endl;
}

void GCoder_Widget::updateGraphic() {
	//get updated values, clear image and redraw
}

void GCoder_Widget::loadSettings()
{
	std::cout << "Load Settings" << std::endl;
	QSettings settings(m_sSettingsFile, QSettings::IniFormat);
	std::cout << "size: " << settings.allKeys().size() << std::endl;
	std::cout << "settings: " << (settings.allKeys().begin() + 1)->toStdString() << std::endl;
	std::cout << "Load Settings2" << std::endl;
	QString sText = settings.value("Settings", "").toString();
	//QSettings settings2 = settings.value("Settings", "");
	QString sText2 = settings.value("Settings/DetailedLog", "").toString();
	std::cout << "Load Settings3: " << sText.toStdString() << std::endl;
	std::cout << "Load Settings4: " << sText2.toStdString() << std::endl;
	/**f (m_pLabel)
	{
		m_pLabel->setText(sText);
	}
	*/
}

void GCoder_Widget::saveSettings()
{
	QSettings settings(m_sSettingsFile, QSettings::IniFormat);
	//QString sText = (m_pEdit) ? m_pEdit->text() : "";
	//settings.setValue("text", sText);
	//if (m_pLabel)
	//{
	//	m_pLabel->setText(sText);
	//}
}

void GCoder_Widget::handleButton()
{
	saveSettings();
}
