#pragma once

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;

#define isLine(type) (type=='L')
#define isCircle(type) (type=='C')
#define isDebug true

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
	double x, y;
	Point(double x=0.0, double y=0.0) : x(x), y(y) {} 
	bool operator < (const Point& B) const {
		return (dcmp(x - B.x) < 0 || (dcmp(x - B.x) == 0 && dcmp(y - B.y) < 0));
	} 
};

typedef Point Vector;

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
	return A / len;
}

void printAll(vector<Point> v) {
	auto it = v.begin();
	while (it != v.end()) {
		printf("%.10lf %.10lf\n", it->x, it->y);
		it++;
	}
}

struct Circle{
	Point center;
	double r;
	Circle(Point center, double r): center(center), r(r) {} 
	Point point(double angle) {
		return Point(center.x + cos(angle)*r, center.y + sin(angle)*r);
	}
};

// Calculate the point p to dir distance, s is line on dir
double DistanceToLine(Point p, Point s, Vector direction) {
	Vector t = s - p;
	return fabs(Cross(t, direction)) / Length(direction);
}

class Intersection {
private:
	vector<Point> points;
	vector<Vector> vectors;
	vector<Point> intersects;
	vector<Point> hearts;
	vector<double> radius;
public:
	Intersection();
	// int getLinePoints();
	// int getCirclePoints();
	int getAllPoints();
	void solveLineLineIntersection();
	void solveLineCircleIntersection();
	void solveCircleCircleIntersection();
	int solveIntersection();
};