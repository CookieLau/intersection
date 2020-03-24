#include "ShowPic.h"
#include <QWidget>
#include <QPainter>
#include "../intersection/Intersection.h"

ShowPic::ShowPic(QWidget *parent) :QWidget(parent)
{
	setAutoFillBackground(true);
	setPalette(QPalette(Qt::white));
	intersection = new Intersection();
	zoom = 20;
}

void ShowPic::setIntersection(Intersection *intersection) {
	this->intersection = intersection;
}

void ShowPic::setScale(double multi) {
	zoom *= multi;
}

void ShowPic::setOffset(double x, double y) {
	x_offset = x;
	y_offset = y;
}

void ShowPic::paintEvent(QPaintEvent *event) {

	QPainter painter(this);
	//painter.setPen(Qt::blue);
	QPen pp;
	pp.setWidth(2);
	pp.setColor(Qt::blue);
	pp.setStyle(Qt::DotLine);
	painter.setPen(pp);

	QPen ppoint;
	ppoint.setWidth(4);
	ppoint.setColor(Qt::gray);

	QLineF axis_X(-1e3, y_offset, 2e3, y_offset);
	QLineF axis_Y(x_offset, -1e3, x_offset, 2e3);

	painter.drawLine(axis_X);
	painter.drawLine(axis_Y);

	painter.setFont(QFont("Arial", 10));

	double x_axisOff = x_offset + 5;
	int cnt = 0;
	while (x_axisOff < max_x) {
		painter.setPen(pp);
		painter.drawText(QRectF(x_axisOff, y_offset, 50, 50), QString::fromStdString(to_string(cnt)));
		painter.setPen(ppoint);
		QPointF ppp(x_axisOff - 5, y_offset);
		painter.drawPoint(ppp);
		cnt++;
		x_axisOff += zoom;
	}

	cnt = -1;
	x_axisOff = x_offset + 5 - zoom;
	while (x_axisOff > 0) {
		painter.setPen(pp);
		painter.drawText(QRectF(x_axisOff, y_offset, 50, 50), QString::fromStdString(to_string(cnt)));
		painter.setPen(ppoint);
		QPointF ppp(x_axisOff - 5, y_offset);
		painter.drawPoint(ppp);
		cnt--;
		x_axisOff -= zoom;
	}

	x_axisOff = x_offset + 5;
	double y_axisOff = y_offset + zoom;
	cnt = -1;
	while (y_axisOff < max_y) {
		painter.setPen(pp);
		painter.drawText(QRectF(x_axisOff, y_axisOff, 50, 50), QString::fromStdString(to_string(cnt)));
		painter.setPen(ppoint);
		QPointF ppp(x_axisOff - 5, y_axisOff);
		painter.drawPoint(ppp);
		cnt--;
		y_axisOff += zoom;
	}

	y_axisOff = y_offset - zoom;
	cnt = 1;
	while (y_axisOff > 0) {
		painter.setPen(pp);
		painter.drawText(QRectF(x_axisOff, y_axisOff, 50, 50), QString::fromStdString(to_string(cnt)));
		painter.setPen(ppoint);
		QPointF ppp(x_axisOff - 5, y_axisOff);
		painter.drawPoint(ppp);
		cnt++;
		y_axisOff -= zoom;
	}




	pp.setColor(Qt::black);
	pp.setStyle(Qt::SolidLine);
	painter.setPen(pp);
	// 因为是左上角为基准点，所以要加上偏移量
	double multipleSize = 1e7;
	double x1, y1; // x1, y1 point
	double v1, v2;
	double radius;
	QLineF line;
	QRectF circle;

	// 画基本图形
	int type;

	// 遍历基本图形
	std::vector<Point> linePoints = intersection->getPoints();
	std::vector<Vector> vectors = intersection->getVectors();
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
			line.setLine(x_offset + (x1 + multipleSize * v1)*zoom, y_offset - (y1 + multipleSize * v2)*zoom, x_offset + (x1 - multipleSize * v1)*zoom, y_offset - (y1 - multipleSize * v2)*zoom);
			painter.drawLine(line);
			break;
		case 'R':
			// get x1, x2, v1, x2
			line.setLine(x_offset + (x1 + multipleSize * v1)*zoom, y_offset - (y1 + multipleSize * v2)*zoom, x_offset + x1 * zoom, y_offset - y1 * zoom);
			painter.drawLine(line);
			break;
		case 'S':
			// get x1, x2, v1, x2
			line.setLine(x_offset + (x1 + v1)*zoom, y_offset - (y1 + v2)*zoom, x_offset + x1 * zoom, y_offset - y1 * zoom);
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
		//        printf("%lf %lf %lf\n", x1, y1, radius);
		circle.setRect(x_offset + (x1 - radius)*zoom, y_offset - (y1 + radius)*zoom, 2 * radius*zoom, 2 * radius*zoom);
		painter.drawEllipse(circle);

		//        circle.setRect(0, 0, 10, 10);painter.drawEllipse(circle);
		//        circle.setRect(10, 10, 10, 10);painter.drawEllipse(circle);
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
		QPointF  point(x_offset + x1 * zoom, y_offset - y1 * zoom);
		painter.drawPoint(point);
	}
}

