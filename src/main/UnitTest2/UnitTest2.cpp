#include "pch.h"
#include "CppUnitTest.h"
#include "../main/myIntersection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersection* intersect = new Intersection();
			FILE *stream1;
			freopen_s(&stream1, "parallel1.txt", "r", stdin);
			intersect->getAllPoints();
			Assert::AreEqual(0, intersect->solveIntersection());
		}

		TEST_METHOD(TestMethod2)
		{
			Intersection* intersect = new Intersection();
			FILE *stream1;
			freopen_s(&stream1, "parallel2.txt", "r", stdin);
			intersect->getAllPoints();
			Assert::AreEqual(9, intersect->solveIntersection());
		}

		TEST_METHOD(TestMethod3) 
		{
			Intersection* intersect = new Intersection();
			FILE *stream1;
			freopen_s(&stream1, "verticle1.txt", "r", stdin);
			intersect->getAllPoints();
			Assert::AreEqual(2, intersect->solveIntersection());
		}

		TEST_METHOD(TestMethod4) 
		{
			Intersection* intersect = new Intersection();
			FILE *stream1;
			freopen_s(&stream1, "hard1.txt", "r", stdin);
			intersect->getAllPoints();
			Assert::AreEqual(2, intersect->solveIntersection());
		}


	};
}
