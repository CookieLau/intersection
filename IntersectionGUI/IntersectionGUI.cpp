#include <QFileDialog>
#include <fstream>

#include "IntersectionGUI.h"
#include "..\src\Intersection.h"

IntersectionGUI::IntersectionGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	intersection = new Intersection();
	connect(ui.openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));
}

void IntersectionGUI::openFile(void) {
	QString filePath = QFileDialog::getOpenFileName(this, "Open File to Load", "./");
	QFileInfo fileInfo = QFileInfo(filePath);
	string file_path = fileInfo.absoluteFilePath().toStdString();
	ifstream in(file_path);
	intersection->getAllPoints(in);
	int res = intersection->solveIntersection();
	ui.pointNumResult->setText(QString::number(res, 10));
}
