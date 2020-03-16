#include "Intersection.h"


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

	if (hasResultAfter) {
		int result;
		cin >> result;
		if (result == ret) {
			cout << "Pass" << endl;
		}
		else {
			cout << "Wrong Answer" << endl;
			intersect->printAllIntersections();
		}
	}
	cout << ret << endl;


	fclose(stdin);
	fclose(stdout);

	return 0;
}