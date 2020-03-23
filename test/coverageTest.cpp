#include "pch.h"
#include <iostream> 
#include "../src/Shape.h"
#include "../src/Intersection.h"  
#include <cassert>

int main() {
		ifstream in0("../test/testcase/cc_0.txt");
		Intersection* intersect = new Intersection();
		intersect->getAllPoints(in0);
		int ret = intersect->solveIntersection();
		cout << ret << endl;
		assert(ret == 23);
		intersect->clearGraph();

		ifstream in1("..//test/testcase/rl_0.txt");
		intersect->getAllPoints(in1);
		ret = intersect->solveIntersection();
		assert(ret == 13);
		intersect->clearGraph();

		ifstream in2("..//test/testcase/sl_0.txt");
		intersect->getAllPoints(in2);
		ret = intersect->solveIntersection();
		assert(ret == 11);
		intersect->clearGraph();

		ifstream in3("..//test/testcase/rsc_0.txt");
		intersect->getAllPoints(in3);
		ret = intersect->solveIntersection();
		assert(ret == 11);
		intersect->clearGraph();

		ifstream in4("..//test/testcase/rslc_0.txt");
		
		intersect->getAllPoints(in4);
		ret = intersect->solveIntersection();
		assert(ret == 17);
		intersect->clearGraph();

		ifstream in5("..//test/testcase/rsl_1.txt");
		
		intersect->getAllPoints(in5);
		ret = intersect->solveIntersection();
		assert(ret == 14);
		intersect->clearGraph();

		ifstream in6("..//test/testcase/rslc_1.txt");
		
		intersect->getAllPoints(in6);
		ret = intersect->solveIntersection();
		assert(ret == 12);
		intersect->clearGraph();

		ifstream in7("..//test/testcase/lc_1.txt");
		
		intersect->getAllPoints(in7);
		ret = intersect->solveIntersection();
		assert(ret == 9);
		intersect->clearGraph();

		ifstream in8("..//test/testcase/rsl_0.txt");
		
		intersect->getAllPoints(in8);
		ret = intersect->solveIntersection();
		assert(ret == 15);
		intersect->clearGraph();

		ifstream in9("..//test/testcase/rsl_2.txt");
		
		intersect->getAllPoints(in9);
		ret = intersect->solveIntersection();
		assert(ret == 1531);
		intersect->clearGraph();

		ifstream in10("../test/testcase/cc_1.txt");
		
		intersect->getAllPoints(in10);
		ret = intersect->solveIntersection();
		cout << ret << endl;
		assert(ret == 1);
		intersect->clearGraph();

		ifstream in11("../test/testcase/cc_2.txt");
		intersect->getAllPoints(in11);
		ret = intersect->solveIntersection();
		cout << ret << endl;
		assert(ret == 1);
		intersect->clearGraph();

		ifstream in12("../test/testcase/cc_3.txt");
		intersect->getAllPoints(in12);
		ret = intersect->solveIntersection();
		cout << ret << endl;
		assert(ret == 2);
		intersect->clearGraph();

		cout << "Complete Testing..." << endl;
		return 0;
}