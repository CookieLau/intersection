#include "pch.h"
#include "CppUnitTest.h"
#include "../intersection/Intersection.h"
#include <cmath>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		TEST_METHOD(CC0Test)
		{
			ifstream in("../test/testcase/cc_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 23);
		}

		TEST_METHOD(RL0Test)
		{
			ifstream in("../test/testcase/rl_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 13);
		}

		TEST_METHOD(SL0Test)
		{
			ifstream in("../test/testcase/sl_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 11);
		}

		TEST_METHOD(RSC0Test)
		{
			ifstream in("../test/testcase/rsc_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 11);
		}

		TEST_METHOD(RSLC0Test)
		{
			ifstream in("../test/testcase/rslc_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 17);
		}

		TEST_METHOD(RSL1Test)
		{
			ifstream in("../test/testcase/rsl_1.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 14);
		}

		TEST_METHOD(RSLC1Test)
		{
			ifstream in("../test/testcase/rslc_1.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 12);
		}

		TEST_METHOD(LC1Test)
		{
			ifstream in("../test/testcase/lc_1.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 9);
		}

		TEST_METHOD(RSL0Test)
		{
			ifstream in("../test/testcase/rsl_0.txt");
			Intersection* intersect = new Intersection();
			intersect->getAllPoints(in);
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 15);
		}
	};
}
