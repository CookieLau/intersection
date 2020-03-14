#pragma once

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <math.h>
using namespace std;

#define isLine(type) (type=='L' || type=='R' || type=='S')
#define isCircle(type) (type=='C')
#define isDebug true
#define isPrintAllIntersections false
#define hasResultAfter true

const double eps = 1e-12;
int dcmp(double x) {
	if (fabs(x) <= eps) {
		return 0;
	}
	else {
		return x < 0 ? -1 : 1;
	}
}

struct Point {
	// store one end for line, ray, segment
	double x, y;

	// 'L' for line, with no end
	// 'R' for ray, with one end
	// 'S' for segment, with double end
	char type; 

	// Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	Point(double x=0.0, double y=0.0, char type='N') : x(x), y(y), type(type) {} 
	
	// mention: operator < must obey opposite
	// A not < B -> B >= A
	bool operator < (const Point& B) const {
		return (dcmp(x - B.x) < 0 || (dcmp(x - B.x) == 0 && dcmp(y - B.y) < 0));
	} 
};

typedef Point Vector;
typedef Point Heart;

Vector operator + (Vector A, Vector B) {
	return Vector(A.x + B.x, A.y + B.y);
}

Vector operator - (Point A, Point B) {
	return Vector(A.x - B.x, A.y - B.y);
}

Vector operator * (Point A, double b) {
	return Vector(A.x*b, A.y*b);
}

Vector operator / (Point A, double b) {
	if (dcmp(b) == 0) {
		cout << "Invalid division detected" << endl;
	}
	return Vector(A.x / b, A.y / b);
}

bool operator == (const Point& A, const Point& B) {
	if (dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y)==0) {
		return true;
	}
	return false;
}

double Dot(Vector A, Vector B) {
	return A.x*B.x + A.y*B.y;
}

double Length(Vector A) {
	if (dcmp(A.x) == 0 && dcmp(A.y)==0) {
		return 0;
	}
	return sqrt(Dot(A, A));
}

double Angle(Vector A, Vector B) {
	if (Length(A) == 0 || Length(B) == 0) {
		return 0;
	}
	
	return acos(Dot(A, B)) / Length(A) / Length(B);
}

double Cross(Vector A, Vector B) {
	return A.x*B.y - A.y*B.x;
}

Vector Norm(Vector A) {
	double len = Length(A);
	if (dcmp(len) == 0) {
		return A;
	}
	return A / len;
}

Vector Rotate(Vector A, double rad) {
	return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}

bool LineIsValid(char type, double t) {
	switch (type)
	{
	case 'L':
		return true;
	case 'R':
		return dcmp(t) >= 0;
	case 'S':
		return dcmp(t - 1.0) <= 0 && dcmp(t) >= 0;
	default:
		return false;
	}
}

struct Circle{
	Heart center;
	double radius;
	Circle(Heart center, double radius): center(center), radius(radius) {}

	// calculate point on circle
	Point point(double angle) {
		return Point(center.x + cos(angle)*radius, center.y + sin(angle)*radius);
	}
};


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
double CalculatePM(Circle c, Point p, Vector pq) {
	Heart r = c.center;
	Vector t = r - p;
	return Dot(t, pq) / Length(pq);
}

double CalculateRM(Circle c, Point p, Vector pq) {
	Heart r = c.center;
	Vector t = r - p;
	double pr = Length(t);
	double pm = CalculatePM(c, p, pq);
	return sqrt(pr*pr-pm*pm);
}

// only for circle center not on line situation, symmetric
double CalculatePS_l(Circle c, Point p, Vector pq) {
	Heart r = c.center;
	double radius = c.radius;

	double PR = Length((p - r));
	double RM = CalculateRM(c, p, pq);

	if (dcmp(PR) == 0) {
		return radius;
	}

	double ratio = RM / PR;
	if (ratio > 1 - eps) {
		ratio = 1 - eps;
	}
	else if (ratio < eps - 1) {
		ratio = eps - 1;
	}
	double alpha = asin(ratio);
	
	ratio = RM / radius;
	if (ratio > 1 - eps) {
		ratio = 1 - eps;
	}
	else if (ratio < eps - 1) {
		ratio = eps - 1;
	}

	double gamma = asin(ratio);
	double beta  = gamma - alpha;
	
	if (dcmp(alpha - beta) == 0) {
		return radius;
	}
	return radius*sin(beta) / sin(alpha);
}

// circle and circle intersections related definition
// p is heart of one cirle
// q is heart of another circle
// radius_1 is radius of p heart circle
// radius_2 is radius of q heart circle
// s_l is one intersect
// s_r is another intersect

double CalculateAngle(Circle c_1, Circle c_2) {
	Point p = c_1.center;
	Point q = c_2.center;
	Vector pq = q - p;
	double p2q = Length(pq);

	double radius_1 = c_1.radius;
	double radius_2 = c_2.radius;
	
	double ratio = (radius_1*radius_1 + p2q * p2q - radius_2 * radius_2) / (2 * radius_1*p2q);
	if (ratio > 1 - eps) {
		ratio = 1 - eps;
	}
	else if (ratio < eps - 1) {
		ratio = eps - 1;
	}
	return acos(ratio);
}

class Intersection {
private:
	vector<Point> points;
	vector<Vector> vectors;
	vector<Point> intersects;
	vector<Circle> circles;
	// vector<double> Radius;
public:
	Intersection();
	// int getLinePoints();
	// int getCirclePoints();
	int getAllPoints();
	void solveLineLineIntersection();
	void solveLineCircleIntersection();
	void solveCircleCircleIntersection();
	int solveIntersection();
	void printAllPoints(vector<Point> v);
	void printAllIntersections();
};