#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Intersection.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		TEST_METHOD(INPUT_0)
		{
			try {
				ifstream in("../test/errortestcase/0.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("在第2行，出现未识别符号"), msg);
			}
		}
		TEST_METHOD(INPUT_1)
		{
			try {
				ifstream in("../test/errortestcase/1.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("在第1行，构成线段、射线或直线的两点重合"), msg);
			}
		}
		TEST_METHOD(INPUT_2)
		{
			try {
				ifstream in("../test/errortestcase/2.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("在第1行，出现超范围的数据"), msg);
			}
		}
		TEST_METHOD(INPUT_3)
		{
			try {
				ifstream in("../test/errortestcase/3.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("在第1行，出现值错误，无法读入"), msg);
			}
		}
		TEST_METHOD(LL_0)
		{
			try {
				ifstream in("../test/errortestcase/5.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				intersect->solveIntersection();
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("直线与直线或线段重合"), msg);
			}
		}
		TEST_METHOD(LR_0)
		{
			try {
				ifstream in("../test/errortestcase/6.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				intersect->solveIntersection();
				Assert::IsTrue(false);
			}
			catch (string msg) {
				Assert::AreEqual(string("直线与直线或线段重合"), msg);
			}
		}
		TEST_METHOD(RR_0)
		{
			try {
				ifstream in("../test/errortestcase/7.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(ret, 0);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("直线与直线或线段重合"), msg);
			}
		}
		TEST_METHOD(RR_1)
		{
			try {
				ifstream in("../test/errortestcase/8.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(1, ret);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("直线与直线或线段重合"), msg);
			}
		}
		TEST_METHOD(RR_2)
		{
			try {
				ifstream in("../test/errortestcase/9.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(1, 2);
			}
			catch (string msg) {
				Assert::AreEqual(string("射线与射线重合"), msg);
			}
		}
		TEST_METHOD(RR_3)
		{
			try {
				ifstream in("../test/errortestcase/10.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(1, 2);
			}
			catch (string msg) {
				Assert::AreEqual(string("射线与射线重合"), msg);
			}
		}
		TEST_METHOD(RS_0)
		{
			try {
				ifstream in("../test/errortestcase/11.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(1, ret);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("射线与射线重合"), msg);
			}
		}
		TEST_METHOD(RS_1)
		{
			try {
				ifstream in("../test/errortestcase/12.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(0, ret);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("射线与射线重合"), msg);
			}
		}
		TEST_METHOD(RS_2)
		{
			try {
				ifstream in("../test/errortestcase/12.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(0, ret);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("射线与射线重合"), msg);
			}
		}
		TEST_METHOD(RS_3)
		{
			try {
				ifstream in("../test/errortestcase/13.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(0, 1);
			}
			catch (string msg) {
				Assert::AreEqual(string("射线与线段重合"), msg);
			}
		}
		TEST_METHOD(RS_4)
		{
			try {
				ifstream in("../test/errortestcase/14.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(0, 1);
			}
			catch (string msg) {
				Assert::AreEqual(string("射线与线段重合"), msg);
			}
		}
		TEST_METHOD(SS_0)
		{
			try {
				ifstream in("../test/errortestcase/15.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(ret, 1);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("射线与线段重合"), msg);
			}
		}
		TEST_METHOD(SS_1)
		{
			try {
				ifstream in("../test/errortestcase/16.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(2, 1);
			}
			catch (string msg) {
				Assert::AreEqual(string("线段与线段重合"), msg);
			}
		}
		TEST_METHOD(SS_2)
		{
			try {
				ifstream in("../test/errortestcase/17.txt");
				Intersection* intersect = new Intersection();
				intersect->getAllPoints(in);
				int ret = intersect->solveIntersection();
				Assert::AreEqual(0, ret);
			}
			catch (string msg) {
				Assert::IsTrue(false);
				Assert::AreEqual(string("线段与线段重合"), msg);
			}
		}
	};
}