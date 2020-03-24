#ifndef SHOWPIC_H
#define SHOWPIC_H

#include <QWidget>
#include <QPainter>
#include "../intersection/Intersection.h"

class ShowPic : public QWidget
{
public:
	explicit ShowPic(QWidget *parent = 0);
	void setIntersection(Intersection *intersection);
	void setOffset(double, double);
	void setScale(double multi);
	double zoom;
	double x_offset, y_offset;
	double max_x, max_y;


protected:
	void paintEvent(QPaintEvent *event);

private:
	Intersection *intersection;


};

#endif // SHOWPIC_H
