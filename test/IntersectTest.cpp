#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Shape.h"
#include "../src/Intersection.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		TEST_METHOD(CC0Test)
		{
			if (freopen("../testcase/cc_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 23);
		}

		TEST_METHOD(RL0Test)
		{
			if (freopen("../testcase/rl_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 13);
		}

		TEST_METHOD(SL0Test)
		{
			if (freopen("../testcase/sl_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 11);
		}

		TEST_METHOD(RSC0Test)
		{
			if (freopen("../testcase/rsc_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 11);
		}

		TEST_METHOD(RSLC0Test)
		{
			if (freopen("../testcase/rslc_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 17);
		}

		TEST_METHOD(RSL1Test)
		{
			if (freopen("../testcase/rsl_1.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 14);
		}

		TEST_METHOD(RSLC1Test)
		{
			if (freopen("../testcase/rslc_1.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 12);
		}

		TEST_METHOD(LC1Test)
		{
			if (freopen("../testcase/lc_1.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 9);
		}

		TEST_METHOD(RSL0Test)
		{
			if (freopen("../testcase/rsl_0.txt", "r", stdin) == NULL) {
				Assert::AreEqual(1, 2);
			}
			Intersection* intersect = new Intersection();
			intersect->getAllPoints();
			int ret = intersect->solveIntersection();
			Assert::AreEqual(ret, 15);
		}
	};
}
