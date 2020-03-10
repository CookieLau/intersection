#include "myIntersection.h"

Intersection::Intersection() {}

int Intersection::getAllPoints() {
	int n, i;
	double x1, x2, y1, y2;
	char type;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> type;
		if (isLine(type)) {
			cin >> x1 >> y1 >> x2 >> y2;
			points.push_back(Point(x1, y1));
			vectors.push_back(Point(x2 - x1, y2 - y1));
		}
		else if (isCircle(type)) {
			// do something
		}
		else {
			fprintf(stderr, "Type error detected in line %d: type:%c\n", n, type);
			return -1;
		}
	}
	return 0;
}

void Intersection::solveLineLineIntersection() {
	int i, j, n, ssize;
	Vector u, v, w;
	n = (int) vectors.size();
	ssize = (int) intersects.size();
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			u = points[i] - points[j];
			v = vectors[i];
			w = vectors[j];
			double denominator = Cross(v, w);
			if (dcmp(denominator) == 0) { // parallel case
				continue;
			}
			double t = 1.0 * Cross(w, u) / denominator;
			intersects.push_back(points[i] + v * t);
		}
	}
}

void Intersection::solveLineCircleIntersection() {

}

void Intersection::solveCircleCircleIntersection() {

}

int Intersection::solveIntersection() {
	if (points.size() > 0) {
		solveLineLineIntersection();
	}
	if (hearts.size() > 0) {
		solveLineCircleIntersection();
	}
	if (points.size() > 0 && hearts.size() > 0) {
		solveLineCircleIntersection();
	}

	// ------------------ Delete Duplicates ------------------------

	int size = (int) intersects.size();

	// cout << "before unique: " << size << endl;
	// printAll(intersects);

	sort(intersects.begin(), intersects.end());
	auto new_end = unique(intersects.begin(), intersects.end());

	assert(size == intersects.size()); // Fake Delete Duplicates

	intersects.erase(new_end, intersects.end()); // Real Delete Duplicates

	// cout << "after unique: " << intersects.size() << endl;
	// printAll(intersects);

	return (int) intersects.size();
}


int main(int argc, const char** argv) {
	//FILE* stream1;
	for (int i = 1; i+1 < argc; i+=2) {
		const char* path = argv[i + 1];
		if (argv[i][0]=='-' && argv[i][1]=='i') {
			//if (freopen_s(&stream1, path, "r", stdin) == NULL) {
			if (freopen(path, "r", stdin) == NULL) {
					cout << "File: " << path << " opened filed, exit." << endl;
				return 0;
			}
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'o') {
			//if (freopen_s(&stream1, path, "w", stdout) == NULL) {
			if (freopen(path, "w", stdout) == NULL) {
					cout << "File: " << path << " opened filed, exit." << endl;
				return 0;
			}
		}
	}

	Intersection* intersect = new Intersection();
	if (intersect->getAllPoints() != 0) {
		return 0; // unexpected quit
	}

	int ret = intersect->solveIntersection();
	cout << ret << endl;

	
	fclose(stdin);
	fclose(stdout);

	return 0;
}