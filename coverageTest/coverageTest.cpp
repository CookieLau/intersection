#include <iostream>
#include "../intersection/Intersection.h"  

#define assertEqual(given, expected) do {\
		if (given != expected) {\
			std::cout << "Error in test, expected " << expected << " while given " << given << endl;\
		}\
	} while (0)

#define assertUnequal(given, expected) do {\
		if (given == expected) {\
			std::cout << "Error in test, expected equals given in wrong case" << endl;\
		}\
	} while (0)

int main() {
	ifstream in0("../test/testcase/cc_0.txt");
	Intersection* intersect = new Intersection();
	intersect->getAllPoints(in0);
	int ret = intersect->solveIntersection();
	assertEqual(ret, 23);
	intersect->addItem('C', 10, 10, 10, -1);
	Circle c0 = Circle(Point(0, 1), 1);
	Circle c1 = Circle(Point(1, 0), 1);
	double res = CalculateAngle(c0, c1);
	assertEqual(dcmp(res - atan(1)), 0); // pi / 4

	intersect->clearGraph();

	ifstream in1("../test/testcase/rl_0.txt");
	intersect->getAllPoints(in1);
	ret = intersect->solveIntersection();
	assertEqual(ret, 13);
	intersect->clearGraph();

	ifstream in2("../test/testcase/sl_0.txt");
	intersect->getAllPoints(in2);
	ret = intersect->solveIntersection();
	assertEqual(ret, 11);
	intersect->clearGraph();

	ifstream in3("../test/testcase/rsc_0.txt");
	intersect->getAllPoints(in3);
	ret = intersect->solveIntersection();
	assertEqual(ret, 11);
	intersect->clearGraph();

	ifstream in4("../test/testcase/rslc_0.txt");

	intersect->getAllPoints(in4);
	ret = intersect->solveIntersection();
	assertEqual(ret, 17);
	intersect->clearGraph();

	ifstream in5("../test/testcase/rsl_1.txt");

	intersect->getAllPoints(in5);
	ret = intersect->solveIntersection();
	assertEqual(ret, 14);
	intersect->clearGraph();

	ifstream in6("../test/testcase/rslc_1.txt");

	intersect->getAllPoints(in6);
	ret = intersect->solveIntersection();
	assertEqual(ret, 12);
	intersect->clearGraph();

	ifstream in7("../test/testcase/lc_1.txt");

	intersect->getAllPoints(in7);
	ret = intersect->solveIntersection();
	assertEqual(ret, 9);
	intersect->clearGraph();

	ifstream in8("../test/testcase/rsl_0.txt");

	intersect->getAllPoints(in8);
	ret = intersect->solveIntersection();
	assertEqual(ret, 15);
	intersect->clearGraph();

	ifstream in9("../test/testcase/rsl_2.txt");

	intersect->getAllPoints(in9);
	ret = intersect->solveIntersection();
	assertEqual(ret, 1531);
	intersect->clearGraph();

	ifstream in10("../test/testcase/cc_1.txt");

	intersect->getAllPoints(in10);
	ret = intersect->solveIntersection();

	assertUnequal(ret, 0);
	intersect->clearGraph();

	ifstream in11("../test/testcase/cc_2.txt");
	intersect->getAllPoints(in11);
	ret = intersect->solveIntersection();

	assertEqual(ret, 1);
	intersect->clearGraph();

	ifstream in12("../test/testcase/cc_3.txt");
	intersect->getAllPoints(in12);
	ret = intersect->solveIntersection();

	assertUnequal(ret, 0);
	intersect->clearGraph();

	//ifstream in13("../test/testcase/wrong_1.txt");
	//intersect->getAllPoints(in13);
	//ret = intersect->solveIntersection();

	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in14("../test/testcase/wrong_2.txt");
	//intersect->getAllPoints(in14);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in15("../test/testcase/wrong_3.txt");
	//intersect->getAllPoints(in15);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in16("../test/testcase/wrong_4.txt");
	//intersect->getAllPoints(in16);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in17("../test/testcase/wrong_5.txt");
	//intersect->getAllPoints(in17);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in18("../test/testcase/wrong_6.txt");
	//intersect->getAllPoints(in18);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();

	//ifstream in19("../test/testcase/wrong_7.txt");
	//intersect->getAllPoints(in19);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph();
	//
	//ifstream in20("../test/testcase/wrong_8.txt");
	//intersect->getAllPoints(in20);
	//ret = intersect->solveIntersection();
	//assertEqual(ret, -1);
	//intersect->clearGraph(); 

	try {
		ifstream in21("../test/errortestcase/0.txt");

		intersect->getAllPoints(in21);
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("在第2行，出现未识别符号"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in22("../test/errortestcase/1.txt");

		intersect->getAllPoints(in22);
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("在第1行，构成线段、射线或直线的两点重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in23("../test/errortestcase/2.txt");

		intersect->getAllPoints(in23);
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("在第1行，出现超范围的数据"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in24("../test/errortestcase/3.txt");

		intersect->getAllPoints(in24);
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("在第1行，出现值错误，无法读入"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in25("../test/errortestcase/5.txt");

		intersect->getAllPoints(in25);
		intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("直线与直线或线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in26("../test/errortestcase/6.txt");

		intersect->getAllPoints(in26);
		intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("直线与直线或线段重合"), msg);
	}
	intersect->clearGraph();



	try {
		ifstream in27("../test/errortestcase/7.txt");

		intersect->getAllPoints(in27);
		ret = intersect->solveIntersection();
		assertEqual(ret, 0);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("直线与直线或线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in28("../test/errortestcase/8.txt");

		intersect->getAllPoints(in28);
		ret = intersect->solveIntersection();
		assertEqual(1, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("直线与直线或线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in29("../test/errortestcase/9.txt");

		intersect->getAllPoints(in29);
		ret = intersect->solveIntersection();
		assertEqual(1, 2);
	}
	catch (string msg) {
		assertEqual(string("射线与射线重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in30("../test/errortestcase/10.txt");

		intersect->getAllPoints(in30);
		ret = intersect->solveIntersection();
		assertEqual(1, 2);
	}
	catch (string msg) {
		assertEqual(string("射线与射线重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in31("../test/errortestcase/11.txt");

		intersect->getAllPoints(in31);
		ret = intersect->solveIntersection();
		assertEqual(1, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("射线与射线重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in32("../test/errortestcase/12.txt");

		intersect->getAllPoints(in32);
		ret = intersect->solveIntersection();
		assertEqual(0, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("射线与射线重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in33("../test/errortestcase/12.txt");

		intersect->getAllPoints(in33);
		ret = intersect->solveIntersection();
		assertEqual(0, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("射线与射线重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in34("../test/errortestcase/13.txt");

		intersect->getAllPoints(in34);
		ret = intersect->solveIntersection();
		assertEqual(0, 1);
	}
	catch (string msg) {
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in35("../test/errortestcase/14.txt");

		intersect->getAllPoints(in35);
		ret = intersect->solveIntersection();
		assertEqual(0, 1);
	}
	catch (string msg) {
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in36("../test/errortestcase/15.txt");

		intersect->getAllPoints(in36);
		ret = intersect->solveIntersection();
		assertEqual(ret, 1);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in37("../test/errortestcase/16.txt");

		intersect->getAllPoints(in37);
		ret = intersect->solveIntersection();
		assertEqual(2, 1);
	}
	catch (string msg) {
		assertEqual(string("线段与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in38("../test/errortestcase/17.txt");

		intersect->getAllPoints(in38);
		ret = intersect->solveIntersection();
		assertEqual(0, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
		assertEqual(string("线段与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in39("../test/errortestcase/18.txt");

		intersect->getAllPoints(in39);
		ret = intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("线段与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in40("../test/errortestcase/19.txt");

		intersect->getAllPoints(in40);
		ret = intersect->solveIntersection();
		assertEqual(0, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
	}
	intersect->clearGraph();

	try {
		ifstream in41("../test/errortestcase/20.txt");

		intersect->getAllPoints(in41);
		ret = intersect->solveIntersection();
		assertEqual(1, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
	}
	intersect->clearGraph();

	try {
		ifstream in42("../test/errortestcase/21.txt");

		intersect->getAllPoints(in42);
		ret = intersect->solveIntersection();
		assertEqual(0, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
	}
	intersect->clearGraph();

	try {
		ifstream in43("../test/errortestcase/22.txt");

		intersect->getAllPoints(in43);
		ret = intersect->solveIntersection();
		assertEqual(1, ret);
	}
	catch (string msg) {
		assertEqual(true, false);
	}
	intersect->clearGraph();

	try {
		ifstream in44("../test/errortestcase/23.txt");

		intersect->getAllPoints(in44);
		ret = intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in45("../test/errortestcase/24.txt");
		intersect->getAllPoints(in45);
		ret = intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	ifstream in46("../test/testcase/rs_1.txt");
	intersect->getAllPoints(in46);
	ret = intersect->solveIntersection();
	assertEqual(ret, 0);
	intersect->clearGraph();

	ifstream in47("../test/testcase/rs_2.txt");
	intersect->getAllPoints(in47);
	ret = intersect->solveIntersection();
	assertEqual(ret, 0);
	intersect->clearGraph();

	try {
		ifstream in48("../test/errortestcase/25.txt");
		intersect->getAllPoints(in48);
		ret = intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("射线与线段重合"), msg);
	}
	intersect->clearGraph();

	try {
		ifstream in49("../test/errortestcase/26.txt");
		intersect->getAllPoints(in49);
		ret = intersect->solveIntersection();
		assertEqual(true, false);
	}
	catch (string msg) {
		assertEqual(string("圆和圆重合"), msg);
	}
	intersect->clearGraph();


	try {
		intersect->addItem('C', 10, -99999, 1000000, -1);
	}
	catch (string msg) {
		assertEqual(msg, "出现超范围的数据");
	}

	try {
		intersect->addItem('L', 0, 1, 0, 1);
	}
	catch (string msg) {
		assertEqual(msg, "构成线段、射线或直线的两点重合");
	}
	try {
		intersect->addItem('C', 0, 1, -10, -1);
	}
	catch (string msg) {
		assertEqual(msg, "圆的半径应大于0");
	}
	try {
		intersect->addItem('S', 0, 99999, 100001, -10);
	}
	catch (string msg) {
		assertEqual(msg, "出现超范围的数据");
	}

	cout << "Complete Testing..." << endl;
	return 0;
}