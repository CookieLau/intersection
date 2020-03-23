#pragma once
#ifndef SHOWPIC_H
#define SHOWPIC_H

#include <QWidget>
#include <QPainter>
#include "../src/Intersection.h"

class ShowPic: public QWidget
{
public:
    explicit ShowPic(QWidget *parent = 0);
    void setIntersection(Intersection *intersection);
    void setOffset(double, double);
    void setScale(double multi);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Intersection *intersection;
    double x_offset, y_offset;
    double zoom;

};

#endif // SHOWPIC_H
