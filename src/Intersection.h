#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Shape.h"
#define DLL_OPTION
// #define DLL_OPTION _declspec(dllexport)

class DLL_OPTION Intersection {
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
	
	void removeVector(int index);
	void removeCircle(int index);
};

#endif // !INTERSECTION_H