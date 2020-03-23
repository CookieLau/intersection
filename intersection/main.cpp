#include <fstream>
#include "Intersection.h"


int main(int argc, const char** argv) {
	//FILE* stream1;
	ifstream in;
	ofstream out;
	for (int i = 1; i+1 < argc; i+=2) {
		const char* path = argv[i + 1];
		if (argv[i][0]=='-' && argv[i][1]=='i') {
			// if (freopen_s(&stream1, path, "r", stdin) == NULL) {
			// if (freopen(path, "r", stdin) == NULL) {
			in.open(path);
			if (!in.is_open()) {
					cout << "File: " << path << " opened filed, exit." << endl;
				return 0;
			}
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'o') {
			// if (freopen_s(&stream1, path, "w", stdout) == NULL) {
			// if (freopen(path, "w", stdout) == NULL) {
			out.open(path);
			if (!out.is_open()) {
					cout << "File: " << path << " opened filed, exit." << endl;
				return 0;
			}
		}
	}

	Intersection* intersect = new Intersection();
	if (intersect->getAllPoints(in) != 0) {
		return 0; // unexpected quit
	}

	int ret = intersect->solveIntersection();

	if (hasResultAfter) {
		int result;
		in >> result;
		if (result == ret) {
			cout << "Pass" << endl;
		}
		else {
			cout << "Wrong Answer" << endl;
			intersect->printAllIntersections();
		}
	}
	out << ret << endl;

	in.close();
	out.close();
	// fclose(stdin);
	// fclose(stdout);

	return 0;
}