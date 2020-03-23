#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <fstream>
#include "Shape.h"

//#define DLL_OPTION
#define DLL_OPTION _declspec(dllexport)

class DLL_OPTION Intersection {
private:
	vector<Point> points;
	vector<Vector> vectors;
	vector<Point> intersects;
	vector<Circle> circles;
	
public:
	Intersection();
	int getAllPoints(ifstream& in);
	void solveLineLineIntersection();
	void solveLineCircleIntersection();
	void solveCircleCircleIntersection();
	int solveIntersection();
	void printAllPoints(vector<Point> v);
	void printAllIntersections();
	
	void removeVector(int index);
	void removeCircle(int index);

	vector<Point> getPoints(void);
	vector<Vector> getVectors(void);
	vector<Point> getIntersects(void);
	vector<Circle> getCircles(void);

	void setVectorNotExist(int index);
	void setCircleNotExist(int index);
};

#endif // !INTERSECTION_H