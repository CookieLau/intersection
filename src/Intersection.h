#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Shape.h"

class _declspec(dllexport) Intersection {
private:
	vector<Point> points;
	vector<Vector> vectors;
	vector<Point> intersects;
	vector<Circle> circles;
public:
	Intersection();
	int getAllPoints();
	void solveLineLineIntersection();
	void solveLineCircleIntersection();
	void solveCircleCircleIntersection();
	int solveIntersection();
	void printAllPoints(vector<Point> v);
	void printAllIntersections();
};

#endif // !INTERSECTION_H