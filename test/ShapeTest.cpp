#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Intersection.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		TEST_METHOD(PointStructTest)
		{
			Point p0 = Point(1.0, 2.0);
			Point p1 = Point(2.0, 3.0);
			Point p2 = Point(2.0, 2.0);
			Point p3 = Point(1.000000000000001, 2.0);
			Assert::IsTrue(p0 < p1);
			Assert::IsTrue(p2 < p1);
			Assert::IsFalse(p0 < p3);
			Assert::IsFalse(p3 < p0);
		}

		TEST_METHOD(CircleStructTest)
		{
			Circle c0 = Circle(Point(0, 0), 1);
			Point p0 = c0.point(atan(1) * 2); // pi/2
			Point p1 = c0.point(atan(1) * 4); // pi
			Assert::AreEqual((int)p0.x, 0);
			Assert::AreEqual((int)p0.y, 1);
			Assert::AreEqual((int)p1.x, -1);
			Assert::AreEqual((int)p1.y, 0);
		}

		TEST_METHOD(DcmpTest)
		{
			Assert::AreEqual(dcmp(1.0000000000001 - 1.0), 0);
			Assert::AreEqual(dcmp(1.1000000000001 - 1.0), 1);
			Assert::AreEqual(dcmp(0.9000000000001 - 1.0), -1);
		}

		TEST_METHOD(VectorOperatorTest)
		{
			Vector v0 = Vector(100, 200);
			Vector v1 = Vector(50, 60);
			Vector res = v0 + v1;
			Assert::AreEqual(res.x, 150.0);
			Assert::AreEqual(res.y, 260.0);
			res = v0 - v1;
			Assert::AreEqual(res.x, 50.0);
			Assert::AreEqual(res.y, 140.0);
			res = v0 * 3;
			Assert::AreEqual(res.x, 300.0);
			Assert::AreEqual(res.y, 600.0);
			res = v0 / 4;
			Assert::AreEqual(res.x, 25.0);
			Assert::AreEqual(res.y, 50.0);

			Vector v2 = Vector(100.00000000000003, 199.99999999999999);
			Assert::IsTrue(v0 == v2);
		}

		TEST_METHOD(DotTest)
		{
			Vector v0 = Vector(1.5, 3);
			Vector v1 = Vector(1.5, 1.5);
			Assert::AreEqual(Dot(v0, v1), 6.75);
		}

		TEST_METHOD(LengthTest)
		{
			Vector v0 = Vector(3, 4);
			Vector v1 = Vector(6, 8);
			Assert::AreEqual(Length(v0), 5.0);
			Assert::AreEqual(Length(v1), 10.0);
		}

		TEST_METHOD(AngleTest)
		{
			Vector v0 = Vector(0, 0);
			Vector v1 = Vector(1, 0);
			Vector v2 = Vector(0, 1);
			Assert::AreEqual(Angle(v1, v0), 0.0);
			Assert::AreEqual(Angle(v1, v2), atan(1) * 2); // pi/2
			Assert::AreEqual(Angle(v2, v1), atan(1) * 2); // pi/2
		}

		TEST_METHOD(CrossTest)
		{
			Vector v0 = Vector(1, 2);
			Vector v1 = Vector(3, 4);
			Assert::AreEqual(Cross(v0, v1), -2.0);
		}

		TEST_METHOD(NormTest)
		{
			Vector v0 = Vector(0, 0);
			Vector v1 = Vector(6, 6);
			v0 = Norm(v0);
			v1 = Norm(v1);
			Assert::AreEqual(v0.x, 0.0);
			Assert::AreEqual(v0.y, 0.0);
			Assert::AreEqual(v1.x, sqrt(2) / 2.0);
			Assert::AreEqual(v1.y, sqrt(2) / 2.0);
		}

		TEST_METHOD(RotateTest)
		{
			Vector v0 = Vector(1, 0);
			Vector v1 = Rotate(v0, atan(1) * 2);
			Assert::AreEqual(dcmp(v1.x - 0.0), 0);
			Assert::AreEqual(dcmp(v1.y - 1.0), 0);
		}

		TEST_METHOD(LineIsValidTest)
		{
			Assert::IsTrue(LineIsValid('L', 2));
			Assert::IsTrue(LineIsValid('R', 2));
			Assert::IsFalse(LineIsValid('R', -1));
			Assert::IsTrue(LineIsValid('S', 0.5));
			Assert::IsFalse(LineIsValid('S', -1));
			Assert::IsFalse(LineIsValid('S', 2));
		}

		TEST_METHOD(CalculatePMTest)
		{
			Circle c0 = Circle(Point(0, 1), 1);
			Point p0 = Point(0.5, -1);
			Vector pq = Vector(0, 2);
			double res = CalculatePM(c0, p0, pq);
			Assert::AreEqual(res, 2.0);
		}
		
		TEST_METHOD(CalculateRMTest)
		{
			Circle c0 = Circle(Point(0, 1), 1);
			Point p0 = Point(0.5, -1);
			Vector pq = Vector(0, 2);
			double res = CalculateRM(c0, p0, pq);
			Assert::AreEqual(res, 0.5);
		}

		TEST_METHOD(CalculatePSLTest) {
			Circle c0 = Circle(Point(0, 1), 1);
			Point p0 = Point(0, 1);
			Vector pq = Vector(0, 2);
			double res = CalculatePS_l(c0, p0, pq);
			Assert::AreEqual(res, 1.0);
		}

		TEST_METHOD(CalculateAngleTest) {
			Circle c0 = Circle(Point(0, 1), 1);
			Circle c1 = Circle(Point(1, 0), 1);
			double res = CalculateAngle(c0, c1);
			Assert::AreEqual(dcmp(res - atan(1)), 0); // pi / 4
		}
	};
}
