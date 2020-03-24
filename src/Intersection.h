#pragma once
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <math.h>
#include <fstream>

#define isLine(type) (type=='L' || type=='R' || type=='S')
#define isCircle(type) (type=='C')
#define isDebug false
#define isPrintAllIntersections false
#define hasResultAfter false

//#define DLL_OPTION
#define DLL_OPTION _declspec(dllexport)

using namespace std;

extern const double eps;

int dcmp(double x);

struct DLL_OPTION Point {
	// store one end for line, ray, segment
	double x, y;

	// store the index stored in vectors or points
	int index;

	// 'L' for line, with no end
	// 'R' for ray, with one end
	// 'S' for segment, with double end
	char type;
	bool isExist;

	// Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	Point(double x = 0.0, double y = 0.0, char type = 'N', int index = -1, bool isExist = true);

	// mention: operator < must obey opposite
	// A not < B -> B >= A
	bool operator < (const Point& B) const;
	string getName(void);
};

typedef Point Vector;
typedef Point Heart;

struct DLL_OPTION Circle {
	Heart center;
	double radius;
	bool isExist;

	Circle(Heart center, double radius, bool isExist = true);

	// calculate point on circle
	Point point(double angle);
	string getName(void);
};

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
	void printAllIntersections();
	void printAllPoints(vector<Point> v);
	void addItem(char type, double a, double b, double c, double d);

	void removeVector(int index);
	void removeCircle(int index);

	vector<Point> getPoints(void);
	vector<Vector> getVectors(void);
	vector<Point> getIntersects(void);
	vector<Circle> getCircles(void);

	void setVectorNotExist(int index);
	void setCircleNotExist(int index);

	void clearGraph();
};

Vector operator + (Vector A, Vector B);

Vector operator - (Point A, Point B);

Vector operator * (Point A, double b);

Vector operator / (Point A, double b);

bool operator == (const Point& A, const Point& B);

double Dot(Vector A, Vector B);

double Length(Vector A);

double Angle(Vector A, Vector B);

double Cross(Vector A, Vector B);

Vector Norm(Vector A);

Vector Rotate(Vector A, double rad);

bool LineIsValid(char type, double t);


// circle and line intersections related definition
// p is one end on line
// r is the heart of circle
// m is on line and pm and rm are perpendicular with each other
// q is the other end of line
// s_l and s_r are the intersections of line and circle, standing for s_left, s_right, where s_left is closer to p than s_right
// alpha is the angle of PM and PR
// beta is the angle of RP and RS
// gamma is the angle of SR and SM


// Caution: RM here is an vector, it has direction, (-¡Þ, +¡Þ)
double CalculatePM(Circle c, Point p, Vector pq);

double CalculateRM(Circle c, Point p, Vector pq);

// only for circle center not on line situation, symmetric
double CalculatePS_l(Circle c, Point p, Vector pq);

// circle and circle intersections related definition
// p is heart of one cirle
// q is heart of another circle
// radius_1 is radius of p heart circle
// radius_2 is radius of q heart circle
// s_l is one intersect
// s_r is another intersect

double CalculateAngle(Circle c_1, Circle c_2);

#endif // !INTERSECTION_H
