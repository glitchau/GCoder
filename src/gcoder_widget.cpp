#include "gcoder_widget.h"
#include "ui_gcoder_widget.h"
#include <QSettings>
#include <QFileDialog>


GCoder_Widget::GCoder_Widget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	
	scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);
	ui.treeWidget->setColumnCount(2);
	ui.treeWidget->setColumnWidth(2, 10);
	ui.treeWidget->clear();
	//ui.treeWidget->
	//m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/demosettings.ini";
	m_sSettingsFile = QApplication::applicationDirPath() + "/settings.ini";
	std::cout << m_sSettingsFile.toStdString() << std::endl;
	loadSettings();
	qfilewatcher = new QFileSystemWatcher();
	qfilewatcher->addPath(m_sSettingsFile);
	//qfilewatcher->
	QRect currentGeometry = ui.graphicsView->geometry();
	//printerY = 150;
	//double pixelPerMM = (double)currentGeometry.width() / (double)printerX;
	//std::cout << (double)currentGeometry.width() << " " << printerX << std::endl;
	//std::cout << "pix: " << pixelPerMM << std::endl;
	int newHeight = mm2px(printerY);
	std::cout << "new height: " << newHeight << std::endl;
	currentGeometry.setHeight(newHeight);
	ui.graphicsView->setGeometry(currentGeometry);


	//scene->addEllipse(0,0,1,1, QPen(Qt::black));
	updateGraphic();

	connect(ui.column_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.row_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.batteryDist_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.presses_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.battX_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.battY_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	//connect(ui.distPresses_spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGraphic()));
	connect(ui.treeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(updateGraphic()));
	connect(ui.generate_pushButton, SIGNAL(pressed()), this, SLOT(generate()));

	connect(qfilewatcher, SIGNAL(fileChanged(const QString &)), this, SLOT(loadSettings()));
}

GCoder_Widget::~GCoder_Widget()
{
	saveSettings();
}
void GCoder_Widget::on_printer_pushButton_pressed() 
{
	std::cout << "Printer Push Button Pressed" << std::endl;
}

void GCoder_Widget::on_add_pushButton_pressed()
{
	addGCommand();
}

void GCoder_Widget::on_remove_pushButton_pressed()
{
	if (ui.treeWidget->selectedItems().size() > 0) {
		delete ui.treeWidget->selectedItems().begin().i->t();
	}
}

void GCoder_Widget::updateGraphic() {
	int batteryDist = ui.batteryDist_spinBox->text().toInt();
	if (ui.battX_spinBox->text().toInt() < 0.5 * batteryDist) {
		ui.battX_spinBox->setValue(0.5 * batteryDist);
	}
	if (ui.battY_spinBox->text().toInt() < 0.5 * batteryDist) {
		ui.battY_spinBox->setValue(0.5 * batteryDist);
	}

	scene->clear();
	std::cout << "clear" << std::endl;
	scene->addEllipse(0, 0, 1, 1, QPen(Qt::black));//Add origin point?
	QVector <QPointF> points;
	int graphicsWidth = ui.graphicsView->geometry().width();
	int graphicsHeight = ui.graphicsView->geometry().height();
	int x = (int)((ui.battX_spinBox->text().toInt()) - batteryDist / 2);
	int y = (int)((ui.battY_spinBox->text().toInt()) - batteryDist / 2);

	for (int i = 0; i < ui.row_spinBox->text().toInt(); ++i)
	{
		x = (int)(ui.battX_spinBox->text().toInt() - batteryDist / 2);
		for (int j = 0; j < ui.column_spinBox->text().toInt(); ++j)
		{
			points.append(QPointF(x, y));
			x = x + batteryDist;
		}
		y = y + batteryDist;

	}
	QBrush brushy(Qt::SolidPattern);
	brushy.setColor(QColor(218, 111, 5, 180));
	for (int i = 0; i < points.size(); i++) 
	{
		scene->addEllipse(mm2px(points[i].x()), mm2px(points[i].y()),mm2px(batteryDist),mm2px(batteryDist), QPen(Qt::red), brushy);
	}


	//add lines
	QVector<QPointF> linePoints;
	for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i)
	{
		QComboBox* box = qobject_cast<QComboBox*>(ui.treeWidget->itemWidget(ui.treeWidget->topLevelItem(i), 0));//get combobox
		std::string currentG = box->currentText().toStdString();//get G#
		//std::cout << "curG: " << currentG << std::endl;
		if (!currentG.compare("G1"))
		{
			//double linex, liney;
			QPointF point;
			bool Xtrue = false, YTrue = false;
			for (int j = 0; j < ui.treeWidget->topLevelItem(i)->childCount(); ++j)
			{
				if (!ui.treeWidget->topLevelItem(i)->child(j)->text(1).toStdString().empty()) {
					std::string variable = ui.treeWidget->topLevelItem(i)->child(j)->text(0).toStdString();
					if (!variable.compare("X"))
					{

						//linex = ui.treeWidget->topLevelItem(i)->child(j)->text(1).toDouble();
						point.setX(ui.treeWidget->topLevelItem(i)->child(j)->text(1).toDouble());
						Xtrue = true;
						//std::cout << "x: " << ui.treeWidget->topLevelItem(i)->child(j)->text(1).toDouble() << std::endl;
					}
					if (!variable.compare("Y"))
					{
						point.setY(ui.treeWidget->topLevelItem(i)->child(j)->text(1).toDouble());
						YTrue = true;
						//std::cout << "y: " << ui.treeWidget->topLevelItem(i)->child(j)->text(1).toDouble() << std::endl;
					}
				}
			}
			if (Xtrue && YTrue)
			{
				linePoints.append(point);
			}
		}
	}
	QBrush brushy2(Qt::SolidPattern);
	brushy.setColor(QColor(Qt::blue));
	int prongEllipseSize = 2;
	int startEllipseSize = 4;
	scene->addEllipse(mm2px(ui.startX_spinBox->value() - startEllipseSize / 2), mm2px(ui.startY_spinBox->value() - startEllipseSize / 2), startEllipseSize, startEllipseSize, QPen(Qt::cyan), brushy2);
	for (int i = 0; i < linePoints.size()-1; i++)
	{
		QPen pen(Qt::blue);
		//scene->addEllipse(mm2px(points[i].x()), mm2px(points[i].y()), mm2px(batteryDist), mm2px(batteryDist), QPen(Qt::red), brushy);
		if (i == 0)
			pen.setColor(Qt::green);
		else if(i == linePoints.size() - 2)
			pen.setColor(Qt::magenta);
		scene->addLine(mm2px(linePoints[i].x()), mm2px(linePoints[i].y()), mm2px(linePoints[i+1].x()), mm2px(linePoints[i+1].y()), pen);
		if (i != 0) {
			scene->addEllipse(mm2px(linePoints[i].x() - distProngs - prongEllipseSize / 2), mm2px(linePoints[i].y() - prongEllipseSize / 2), prongEllipseSize, prongEllipseSize, QPen(Qt::blue), brushy2);
			scene->addEllipse(mm2px(linePoints[i].x() + distProngs - prongEllipseSize / 2), mm2px(linePoints[i].y() - prongEllipseSize / 2), prongEllipseSize, prongEllipseSize, QPen(Qt::blue), brushy2);
		}
	}


}

void GCoder_Widget::loadSettings()
{
	std::cout << "Load Settings" << std::endl;
	if (!QFile(m_sSettingsFile).exists())
	{
		saveSettings();// save default
	}
	else {
		//while (!QFile(m_sSettingsFile).waitForReadyRead(10));
		//qfilewatcher->
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		QSettings settings(m_sSettingsFile, QSettings::IniFormat);
		settings.beginGroup("Parameters");
		ui.column_spinBox->setValue(settings.value("Columns").toInt());
		ui.row_spinBox->setValue(settings.value("Rows").toInt());
		ui.batteryDist_spinBox->setValue(settings.value("Distance").toInt());
		ui.startX_spinBox->setValue(settings.value("StartX").toInt());
		ui.startY_spinBox->setValue(settings.value("StartY").toInt());
		ui.battX_spinBox->setValue(settings.value("BatteryX").toInt());
		ui.battY_spinBox->setValue(settings.value("BatteryY").toInt());
		ui.travelZ_spinBox->setValue(settings.value("TravelZ").toInt());
		ui.pressZ_spinBox->setValue(settings.value("PressZ").toInt());
		ui.presses_spinBox->setValue(settings.value("NumberOfPresses").toInt());
		printerX = settings.value("PrinterX", "100").toInt();
		printerY = settings.value("PrinterY", "100").toInt();
		distProngs = settings.value("DistanceProngs", "5").toInt();
		ui.distPresses_doubleSpinBox->setValue(settings.value("DistancePresses", "5.0").toDouble());
		settings.endGroup();
		std::cout << "PrinterX: " << printerX << " PrinterY: " << printerY << std::endl;
		
	}

}

void GCoder_Widget::saveSettings()
{
	QSettings settings(m_sSettingsFile, QSettings::IniFormat);
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
	settings.beginGroup("Parameters");
	settings.setValue("Columns", ui.column_spinBox->text());
	settings.setValue("Rows", ui.row_spinBox->text());
	settings.setValue("Distance", ui.batteryDist_spinBox->text());
	settings.setValue("StartX", ui.startX_spinBox->text());
	settings.setValue("StartY", ui.startY_spinBox->text());
	settings.setValue("BatteryX", ui.battX_spinBox->text());
	settings.setValue("BatteryY", ui.battY_spinBox->text());
	settings.setValue("TravelZ", ui.travelZ_spinBox->text());
	settings.setValue("PressZ", ui.pressZ_spinBox->text());
	settings.setValue("NumberOfPresses", ui.presses_spinBox->text());
	settings.setValue("PrinterX", printerX);
	settings.setValue("PrinterY", printerY);
	settings.setValue("DistanceProngs", distProngs);
	settings.setValue("DistancePresses", ui.distPresses_doubleSpinBox->text());
	//distPresses_doubleSpinBox
	settings.endGroup();
}

void GCoder_Widget::handleButton()
{
	saveSettings();
}

void GCoder_Widget::addGCommand()
{
	
	std::map<std::string, std::string> x;//
	x.insert(std::pair<std::string, std::string>("X", "10"));
	addGCommand("G1", x);
	updateGraphic();
}
 
void GCoder_Widget::addGCommand(std::string input, std::map<std::string, std::string> x)
{
	QTreeWidgetItem* item = new QTreeWidgetItem;

	QComboBox* cmb = new  QComboBox(ui.treeWidget);
	connect(cmb, SIGNAL(currentIndexChanged(QString)), SLOT(yourfunction(QString)));
	std::vector<std::string> glist;
	gcode.getList(glist);
	for (auto it = glist.begin(); it != glist.end(); ++it)
	{
		cmb->addItem((*it).c_str());// , 'value1');
	}
	cmb->setCurrentIndex(cmb->findText(input.c_str()));
	item = new QTreeWidgetItem(ui.treeWidget);
	int column = 0;
	ui.treeWidget->setItemWidget(item, column, cmb);
	updateGParameters(input, item, x);
}

void GCoder_Widget::yourfunction(QString v)
{
	if (ui.treeWidget->selectedItems().size() == 1) {
		QTreeWidgetItem* x = ui.treeWidget->selectedItems().begin().i->t();
		updateGParameters(v.toStdString(), x);
	}
}

void GCoder_Widget::updateGParameters(std::string input, QTreeWidgetItem* item, std::map<std::string, std::string> x)
{
	std::vector<std::string> p;
	gcode.getParameters(p, input);
	while (item->childCount() > 0)
	{
		delete item->child(0);
	}

	for (auto it = p.begin(); it != p.end(); ++it)
	{
		QTreeWidgetItem* r = new QTreeWidgetItem(item);
		r->setFlags(item->flags() | Qt::ItemIsEditable);
		r->setText(0, (*it).c_str());
		if (x.count((*it).c_str()))
		{
			r->setText(1, x.find((*it).c_str())->second.c_str());
		}
		else
		{
			r->setText(1, "");
		}
	}
}

void GCoder_Widget::on_pushButton_pressed() {

	std::cout << "Generating GCode" << std::endl;

	//std::cout << ui.treeWidget->topLevelItemCount() << std::endl;
	std::stringstream ss;
	for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i)
	{
		QComboBox* box = qobject_cast<QComboBox*>(ui.treeWidget->itemWidget(ui.treeWidget->topLevelItem(i), 0));//get combobox
		ss << box->currentText().toStdString() << " ";//get G#
		for (int j = 0; j < ui.treeWidget->topLevelItem(i)->childCount(); ++j)
		{
			if (!ui.treeWidget->topLevelItem(i)->child(j)->text(1).toStdString().empty()) {
				ss << ui.treeWidget->topLevelItem(i)->child(j)->text(0).toStdString() << ui.treeWidget->topLevelItem(i)->child(j)->text(1).toStdString() << " ";
			}
		}
		ss << std::endl;
	}

	std::cout << "This:\n" << ss.str() << std::endl;


	QString filters("G-Code(*.gcode);;Text files (*.txt);;All files (*.*)");
	QString defaultFilter("G-Code(*.gcode)");
	std::string filename = QFileDialog::getSaveFileName(this, "Save GCode File", QDir::currentPath(), filters).toStdString();
	std::cout << filename << std::endl;
	QFile tempFile(filename.c_str());
	if (tempFile.open(QIODevice::ReadWrite))
	{
		QTextStream stream(&tempFile);
		stream << ss.str().c_str();
	}
	//tempFile.
	tempFile.close();
	//QFileDialog dialog(this, "Save file", QDir::currentPath(), filters);
	//dialog.selectNameFilter(defaultFilter);
	//dialog.exec();
}

void GCoder_Widget::on_clear_pushButton_pressed()
{
	QMessageBox msgBox;
	msgBox.setText("This will delete all generated GCode");
	msgBox.setInformativeText("Are you sure you want to clear all generated GCode?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();

	if (ret == QMessageBox::Yes) 
	{
		ui.treeWidget->clear();
	}
}

double GCoder_Widget::px2mm(int px)
{
	double mmPerPX = (double)printerX / (double)ui.graphicsView->geometry().width();
	//std::cout << "px * mmPerPX:" << px * mmPerPX << std::endl;
	return (double)(px * mmPerPX);
}

int GCoder_Widget::mm2px(double mm)
{
	double pixelPerMM = (double)ui.graphicsView->geometry().width() / (double)printerX;
	//std::cout << "mm * pixelPerMM:" << mm * pixelPerMM << std::endl;
	return (int)(mm * pixelPerMM);
}

void GCoder_Widget::generate()
{
	QMessageBox msgBox;
	//msgBox.setText("This will delete all generated GCode");
	msgBox.setInformativeText("Do you want to delete all previously created GCode?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();

	if (ret == QMessageBox::Yes)
	{
		ui.treeWidget->clear();
	}
	if (ret == QMessageBox::No || ret == QMessageBox::Yes)
	{
		///#####################//
	//move up to travel height,
	//move to start position
	//move to first battery, press one
	//press
	// up to travel height
	//move to press 2.

	///#################//
	//Determine where all presses required and place within a vector
	//iterate through all presses -> travel height, move, press, travel height, etc.

		std::map<std::string, std::string> input;
		input.insert(std::pair<std::string, std::string>("Z", ui.travelZ_spinBox->text().toStdString()));
		addGCommand("G1", input);
		input.clear();
		input.insert(std::pair<std::string, std::string>("X", ui.startX_spinBox->text().toStdString()));
		input.insert(std::pair<std::string, std::string>("Y", ui.startY_spinBox->text().toStdString()));
		addGCommand("G1", input);

		int batteryDist = ui.batteryDist_spinBox->text().toInt();

		QVector <QPointF> points;
		int x = (int)((ui.battX_spinBox->text().toInt()));
		int y = (int)((ui.battY_spinBox->text().toInt()));
		for (int i = 0; i < ui.column_spinBox->text().toInt(); ++i)
		{
			y = (int)(ui.battY_spinBox->text().toInt());
			for (int j = 0; j < ui.row_spinBox->text().toInt(); ++j)
			{
				std::cout << "Centre of battery: [" << x << ", " << y << "]" << std::endl;
				double currenty = 0;
				if (ui.presses_spinBox->value() % 2 == 0) {
					currenty = y - (ui.distPresses_doubleSpinBox->value() * 0.5 * ui.presses_spinBox->value()) + 0.5 * ui.distPresses_doubleSpinBox->value();
				}
				else
				{
					currenty = y - ui.distPresses_doubleSpinBox->value() * (int)(0.5 * ui.presses_spinBox->value());

				}
				//std::cout << currenty << std::endl;
				for (int p = 0; p < ui.presses_spinBox->text().toInt(); ++p)
				{
					points.append(QPointF(x, currenty));
					currenty = currenty + ui.distPresses_doubleSpinBox->value();
				}
				y = y + batteryDist;
			}
			x = x + batteryDist;
		}

		for (int i = 0; i < points.size(); i++)//press points
		{
			std::cout << "x: " << points[i].x() << " y: " << points[i].y() << std::endl;
			input.clear();
			input.insert(std::pair<std::string, std::string>("X", QString::number(points[i].x()).toStdString()));
			input.insert(std::pair<std::string, std::string>("Y", QString::number(points[i].y()).toStdString()));
			addGCommand("G1", input);
			input.clear();
			input.insert(std::pair<std::string, std::string>("Z", ui.pressZ_spinBox->text().toStdString()));
			addGCommand("G1", input);
			input.clear();
			input.insert(std::pair<std::string, std::string>("Z", ui.travelZ_spinBox->text().toStdString()));
			addGCommand("G1", input);
		}
		input.clear();
		input.insert(std::pair<std::string, std::string>("X", ui.startX_spinBox->text().toStdString()));
		input.insert(std::pair<std::string, std::string>("Y", ui.startY_spinBox->text().toStdString()));
		addGCommand("G1", input);




	}
	if (ret == QMessageBox::Cancel)
	{
		std::cout << "Action Cancelled" << std::endl;
	}
	updateGraphic();
}