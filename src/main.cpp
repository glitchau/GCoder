//#include "rapidcsv.h"
#include <QApplication>
#include "mainwindow.h"


//int WinMain(int argc, char** argv)
int main(int argc, char** argv) //and change add_executable (remove WIN32)
{
	QApplication app(argc, argv);


	MainWindow w;
	

	

	w.show();

	return app.exec();
	return 0;
}

//rapidcsv::Document doc("Trajectory_1573700282.270_blasting.csv", rapidcsv::LabelParams(-1, -1));
/*
std::cout << "column count1: " << doc.GetColumnCount() << std::endl;
//rapidcsv::Document doc("outputfile.csv", rapidcsv::LabelParams(-1, -1));
try {
	//std::vector<std::string> checkEmpty = doc.GetRow<std::string>(size_t(0));
	//if (checkEmpty.empty()) {
	//	std::cout << "empty" << std::endl;
	//}
	//else {
		//std::cout << "not empty: " << checkEmpty.size() << std::endl;
		//std::cout << "what is it:" << checkEmpty[0] << "HERE" <<  std::endl;
	//}

	//doc.GetColumn<double>(4);
}
catch (rapidcsv::no_converter & e) {
	//std::cout << e.what() << std::endl;
	std::cout << "error" << std::endl;
}*/
/*
doc.RemoveRow(0);
int numberOfJoints = 6;*/
/*
rapidcsv::Document doc1;
doc1.setLabels(rapidcsv::LabelParams(-1, -1));
doc1.SetColumn(0, doc.GetColumn<double>(4));


for (int i = 0; i < numberOfJoints; ++i) {
	int count = 6 + (i * 8);
	doc1.SetColumn(i*2 + 1, doc.GetColumn<double>(count));
	doc1.SetColumn(i*2 + 2, doc.GetColumn<double>(count + 6));
}
doc1.Save("outputfile.csv"); //reduced csv file (not used) <-- useJSON
*/