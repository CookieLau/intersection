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
	connect(ui.draw, SIGNAL(clicked()), this, SLOT(paintItems(ui.canvas)));
	/*
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
	*/
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
    if (vectorNameToIndex.find(text) != vectorNameToIndex.end()) {
		int index = vectorNameToIndex[text];
		intersection->setVectorNotExist(index);
	}
	else {
		int index = circleNameToIndex[text];
		intersection->setCircleNotExist(index);
	}
	ui.allShapes->takeItem(currenRow);
}

void IntersectionGUI::paintItems(QPaintEvent *) {

    QPainter painter(this);
    //painter.setPen(Qt::blue);
    painter.setPen(Qt::black);

    // 因为是左上角为基准点，所以要加上偏移量
    double x_offset, y_offset;
    double multipleSize = 1e9;
    double x1, y1; // x1, y1 point
    double v1, v2;
    double radius;
    QLineF line;
    QRectF circle;

    // 画基本图形
    int type;

    // 遍历基本图形
	vector<Point> linePoints = intersection->getPoints();
	vector<Vector> vectors = intersection->getVectors();
	for (int i = 0; i < linePoints.size(); ++i) {
		if (!linePoints[i].isExist) {
			continue;
		}
		type = linePoints[i].type;
		x1 = linePoints[i].x;
		y1 = linePoints[i].y;
		v1 = vectors[i].x;
		v2 = vectors[i].y;
		switch (type) {
		case 'L':
			// get x1, x2, v1, x2
			line.setLine(x_offset + x1 + multipleSize * v1, y_offset - y1 - multipleSize * v2, x_offset + x1 - multipleSize * v1, y_offset - y1 + multipleSize * v1);
			painter.drawLine(line);
			break;
		case 'R':
			// get x1, x2, v1, x2
			line.setLine(x_offset + x1 + multipleSize * v1, y_offset - y1 - multipleSize * v2, x_offset + x1, y_offset - y1);
			painter.drawLine(line);
			break;
		case 'S':
			// get x1, x2, v1, x2
			line.setLine(x_offset + x1 + v1, y_offset - y1 - v2, x_offset + x1, y_offset - y1);
			painter.drawLine(line);
			break;
		default:
			break;
		}
	}
	for (Circle item : intersection->getCircles()) {
		if (!item.isExist) {
			continue;
		}
		x1 = item.center.x;
		y1 = item.center.y;
		radius = item.radius;
		circle.setRect(x_offset + x1 - radius, y_offset - y1 - radius, radius, radius);
		painter.drawRect(circle);
	}

    // 画交点
    QPen dotPen;
    dotPen.setWidth(4);
    dotPen.setColor(Qt::red);
    painter.setPen(dotPen);

    // 遍历交点
	for (Point p : intersection->getIntersects()) {
		x1 = p.x;
		y1 = p.y;
		QPointF  point(x_offset + x1, y_offset - y1);
		painter.drawPoint(point);
	}
}

