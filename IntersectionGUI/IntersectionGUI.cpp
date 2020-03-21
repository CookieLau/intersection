#include <QFileDialog>
#include <QtCharts>
#include <fstream>
#include <map>

#include "IntersectionGUI.h"
#include "..\src\Intersection.h"

IntersectionGUI::IntersectionGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	intersection = new Intersection();
	connect(ui.openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.getResult, SIGNAL(clicked()), this, SLOT(getResult()));
	connect(ui.deleteShape, SIGNAL(clicked()), this, SLOT(deleteItem()));
	QSplineSeries* series = new QSplineSeries();
	series->append(0, 1);
	series->append(0.707, 0.707);
	series->append(1, 0);
	series->append(0.707, -0.707);
	series->append(0, -1);
	series->append(-0.707, -0.707);
	series->append(-1, 0);
	series->append(-0.707, 0.707);
	series->append(0, 1);

	QLineSeries* series1 = new QLineSeries();
	series1->append(0, 1);
	series1->append(1, 0);

	QScatterSeries* series2 = new QScatterSeries();
	series2->append(0, 1);
	series2->append(1, 0);

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->addSeries(series1);
	chart->addSeries(series2);
	chart->legend()->hide();
	chart->createDefaultAxes();
	chart->axisX()->setRange(-5, 5);
	chart->axisY()->setRange(-5, 5);
	//chart->setAxisX(axisX);
	//chart->setAxisY(axisY);
	ui.widget->setChart(chart);
}

void IntersectionGUI::loadShape(QStringList& strList) {
	vectorNameToIndex.erase(vectorNameToIndex.begin(), vectorNameToIndex.end());
	circleNameToIndex.erase(circleNameToIndex.begin(), circleNameToIndex.end());
	int indexCnt = 0;
	// int test = intersection->getVectors().size();
	for (auto item : intersection->getVectors()) {
		if (!item.isExist) {
			continue;
		}
		strList << QString::fromStdString(item.getName());
		vectorNameToIndex[item.getName()] = indexCnt++;
	}
	indexCnt = 0;
	for (auto item : intersection->getCircles()) {
		if (!item.isExist) {
			continue;
		}
		strList << QString::fromStdString(item.getName());
		circleNameToIndex[item.getName()] = indexCnt++;
	}
}

void IntersectionGUI::openFile(void) {
	QString filePath = QFileDialog::getOpenFileName(this, "Open File to Load", "./");
	QFileInfo fileInfo = QFileInfo(filePath);
	string file_path = fileInfo.absoluteFilePath().toStdString();
	ifstream in(file_path);
	intersection->getAllPoints(in);
	QStringList strList;
	loadShape(strList);
	ui.allShapes->addItems(strList);
	// add all names to the <shapeName, int> map
	// int res = intersection->solveIntersection();
	// ui.pointNumResult->setText(QString::number(res, 10));
}

void IntersectionGUI::getResult(void) {
	int res = intersection->solveIntersection();
	ui.pointNumResult->setText(QString::number(res, 10));
}

void IntersectionGUI::deleteItem(void) {
	//QPoint pnt = QCursor::pos();
	//pnt = mapFromGlobal(pnt);
	//QListWidgetItem* item = ui.allShapes->itemAt(pnt);
	//string text = (item->text()).toStdString();
	int currenRow = ui.allShapes->currentRow();
	string text = (ui.allShapes->item(currenRow)->text()).toStdString();
	if (vectorNameToIndex.count(text) != 0) {
		int index = vectorNameToIndex[text];
		intersection->setVectorNotExist(index);
	}
	else {
		int index = circleNameToIndex[text];
		intersection->setCircleNotExist(index);
	}
	ui.allShapes->takeItem(currenRow);
}

