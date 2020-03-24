#include <fstream>
#include "Intersection.h"

bool isInLimitation(double num) {
	if (dcmp(num - 100000) < 0 && dcmp(num + 100000) > 0) {
		return true;
	}
	else {
		return false;
	}
}

Intersection::Intersection() {}

int Intersection::getAllPoints(ifstream& in) {
	int n, i;
	double x1, x2, y1, y2, radius;
	char type;
	in >> n;
	for (i = 0; i < n; i++) {
		in >> type;
		if (isLine(type)) {
			if (!(in >> x1 >> y1 >> x2 >> y2)) {
				throw "�ڵ�" + to_string(i + 1) + "�У�����ֵ�����޷�����";
				// fprintf(stderr, "Value error detected in line %d, there are non-numeric characters.\n", i + 1);
			}
			if (dcmp(x1 - x2) == 0 && dcmp(y1 - y2) == 0) {
				throw "�ڵ�" + to_string(i + 1) + "�У������߶Ρ����߻�ֱ�ߵ������غ�";
				// fprintf(stderr, "Two points for constructing %c are the same in line %d.\n", type, i + 1);
			}
			if (!(isInLimitation(x1) && isInLimitation(y1) && isInLimitation(x2) && isInLimitation(y2))) {
				throw "�ڵ�" + to_string(i + 1) + "�У����ֳ���Χ������";
				// fprintf(stderr, "There are numbers out of range (-100000, 100000) at line %d.\n", i + 1);
			}
			int index = points.size();
			points.push_back(Point(x1, y1, type, index));
			vectors.push_back(Point(x2 - x1, y2 - y1, type, index)); // whole Length
		}
		else if (isCircle(type)) {
			if (!(in >> x1 >> y1 >> radius)) {
				throw "�ڵ�" + to_string(i + 1) + "�У�����ֵ�����޷�����";
				// fprintf(stderr, "Value error detected in line %d, there are non-numeric characters.\n", i + 1);
			}
			if (!(isInLimitation(x1) && isInLimitation(y1) && isInLimitation(radius))) {
				throw "�ڵ�" + to_string(i + 1) + "�У����ֳ���Χ������";
				// fprintf(stderr, "There are numbers out of range (-100000, 100000) at line %d.\n", i + 1);
			}
			if (dcmp(radius) <= 0) {
				throw "�ڵ�" + to_string(i + 1) + "�У�Բ�İ뾶Ӧ����0";
			}
			circles.push_back(Circle(Heart(x1, y1, type), radius));
			// Radius.push_back(radius);
		}
		else {
			throw "�ڵ�" + to_string(i + 1) + "�У�����δʶ�����";
			// fprintf(stderr, "Type error detected in line %d: type:%c\n", i + 1, type);
			return -1;
		}
	}
	return 0;
}

void Intersection::addItem(char type, double x1, double y1, double x2, double y2) {
	if (type == 'C') {
		if (!(isInLimitation(x1) && isInLimitation(y1) && isInLimitation(x2))) {
			throw "���ֳ���Χ������";
			// fprintf(stderr, "There are numbers out of range (-100000, 100000) at line %d.\n", i + 1);
		}
		if (dcmp(x2) <= 0) {
			throw "Բ�İ뾶Ӧ����0";
		}
		circles.push_back(Circle(Heart(x1, y1, type), x2));
	}
	else {
		if (dcmp(x1 - x2) == 0 && dcmp(y1 - y2) == 0) {
			throw "�����߶Ρ����߻�ֱ�ߵ������غ�";
			// fprintf(stderr, "Two points for constructing %c are the same in line %d.\n", type, i + 1);
		}
		if (!(isInLimitation(x1) && isInLimitation(y1) && isInLimitation(x2) && isInLimitation(y2))) {
			throw "���ֳ���Χ������";
			// fprintf(stderr, "There are numbers out of range (-100000, 100000) at line %d.\n", i + 1);
		}
		int index = points.size();
		points.push_back(Point(x1, y1, type, index));
		vectors.push_back(Point(x2 - x1, y2 - y1, type, index)); // whole Length
	}
}



void Intersection::solveLineLineIntersection() {
	int i, j, n;
	Vector u, v, w;
	n = (int)vectors.size();
	for (i = 0; i < n; i++) {
		if (!points[i].isExist) {
			continue;
		}
		for (j = i + 1; j < n; j++) {
			if (!points[j].isExist) {
				continue;
			}
			u = points[i] - points[j];
			v = vectors[i];
			w = vectors[j];
			double denominator = Cross(v, w);
			if (dcmp(denominator) == 0) { // parallel case
				if (dcmp(Cross(u, v)) == 0) {
					// �����غ�
					// ������һ����ֱ��
					if (points[i].type == 'L' || points[j].type == 'L') {
						throw string("ֱ����ֱ�߻��߶��غ�");
					}
					else if (points[i].type == 'R' && points[j].type == 'R') {
						// �Է����������е�ˣ����ͬ����error
						double judge = Dot(vectors[i], vectors[j]);
						if (dcmp(judge) > 0) {
							throw string("�����������غ�");
						}
						// ��ͬ�������������ɵ�����������һ�������������
						Point ppv = points[j] - points[i]; // ��iָ��j
						judge = Dot(ppv, vectors[i]);
						// ppv ��i�ķ��������ڻ�
						if (dcmp(judge) > 0) {
							throw string("�����������غ�");
						}
						else if (dcmp(judge) == 0) {
							// ��һ�����㣬���������
							intersects.push_back(points[i]);
						}
						else {
							continue;
						}
					}
					else if (points[i].type == 'R' && points[j].type == 'S') {
						Point rsv0 = points[j] - points[i];
						Point rsv1 = vectors[j] + points[j] - points[i];
						double judge0 = Dot(vectors[i], rsv0);
						double judge1 = Dot(vectors[i], rsv1);
						if (dcmp(judge0) < 0 && dcmp(judge1) < 0) {
							continue;
						}
						else if ((dcmp(judge0) < 0 && dcmp(judge1) == 0) || (dcmp(judge0) == 0 && dcmp(judge1) < 0)) {
							// ��ʱ��Ψһ����Ϊ�������
							intersects.push_back(points[i]);
						}
						else {
							throw string("�������߶��غ�");
						}
					}
					else if (points[i].type == 'S' && points[j].type == 'R') {
						Point rsv0 = points[i] - points[j];
						Point rsv1 = vectors[i] + points[i] - points[j];
						double judge0 = Dot(vectors[j], rsv0);
						double judge1 = Dot(vectors[j], rsv1);
						if (dcmp(judge0) < 0 && dcmp(judge1) < 0) {
							continue;
						}
						else if ((dcmp(judge0) < 0 && dcmp(judge1) == 0) || (dcmp(judge0) == 0 && dcmp(judge1) < 0)) {
							// ��ʱ��Ψһ����Ϊ�������
							intersects.push_back(points[j]);
						}
						else {
							throw string("�������߶��غ�");
						}
					}
					else if (points[i].type == 'S' && points[j].type == 'S') {
						Point iSmall = (dcmp(vectors[i].x) > 0) ? points[i] : (points[i] + vectors[i]);
						Point iLarge = (dcmp(vectors[i].x) > 0) ? (points[i] + vectors[i]) : points[i];
						Point jSmall = (dcmp(vectors[j].x) > 0) ? points[j] : (points[j] + vectors[j]);
						Point jLarge = (dcmp(vectors[j].x) > 0) ? (points[j] + vectors[j]) : points[j];
						if (dcmp(vectors[i].x) == 0) {
							// ��y��ƽ�У���������
							if (iSmall.y > jLarge.y || jSmall.y > iLarge.y) {
								continue;
							}
							else if (iSmall.y == jLarge.y || jSmall.y == iLarge.y) {
								// һ����С������һ���Ĵ���һ���غϵĵ�
								if (iSmall.y == jLarge.y) {
									intersects.push_back(iSmall);
								}
								else {
									intersects.push_back(jSmall);
								}
							}
							else {
								throw string("�߶����߶��غ�");
							}
						}
						else {
							// �ú�����
							if (iSmall.x > jLarge.x || jSmall.x > iLarge.x) {
								continue;
							}
							else if (iSmall.x == jLarge.x || jSmall.x == iLarge.x) {
								// һ����С������һ���Ĵ���һ���غϵĵ�
								if (iSmall.x == jLarge.x) {
									intersects.push_back(iSmall);
								}
								else {
									intersects.push_back(jSmall);
								}
							}
							else {
								throw string("�߶����߶��غ�");
							}
						}
					}
				}
				// LL error /continue
				// LR error /continue
				// RR ��� ͬ��error ��ͬ�� һ���������һ������������ǰ�߷���������� >0 error =0 +1���� <0 continue /continue
				// RS R�����S���˵���������� ��R����������� ȫΪ���� continue һ0һ�� +1���� ���� error /continue
				// SS ��x���� ���x����ͬ��ƽ����y������y���꣬����ÿһ���߶� ��x��С�����x�ϴ����� һ��С����>��һ�������� continue
				// ����ȣ�һ��С���������һ�������꣩����+1���㣬���� error     /continue
				continue;
			}
			double t_i = 1.0 * Cross(w, u) / denominator;
			double t_j = 1.0 * Cross(v, u) / denominator;

			char type_i = points[i].type;
			char type_j = points[j].type;

			if (LineIsValid(type_i, t_i) && LineIsValid(type_j, t_j)) { // only when double valid is valid
				intersects.push_back(points[i] + v * t_i);
				// intersects.push_back(points[j] + w * t_j); // the same, only for validate t_j
			}
		}
	}
}

void Intersection::solveLineCircleIntersection() {
	int i, j;
	for (i = 0; i < (int)vectors.size(); i++) {
		if (!points[i].isExist) {
			continue;
		}
		for (j = 0; j < (int)circles.size(); j++) {
			if (!circles[j].isExist) {
				continue;
			}
			Point p = points[i];
			Vector pq = vectors[i];
			Circle c = circles[j];
			double radius = c.radius;
			char type = p.type;
			Vector norm_pq = Norm(pq);
			Heart r = c.center;
			Vector pr = r - p;
			Vector norm_pr = Norm(pr);
			Point q = p + pq;

			double RM = CalculateRM(c, p, pq);
			double PR = Length(pr);
			int status = dcmp(RM - radius);
			if (status == 0) { // tangency
				double PM = CalculatePM(c, p, pq);
				double t = PM / Length(pq);
				if (LineIsValid(type, t)) {
					Point m = p + norm_pq * PM;
					intersects.push_back(m);
				}

				// For validation
				double PS = CalculatePS_l(c, p, pq);
				// assert(dcmp(fabs(PS) - fabs(PM)) == 0);
			}
			else if (status > 0) { // disjoint
				continue;
			}
			else { // intersect
				if (dcmp(RM) == 0 && dcmp(PR) != 0) {

					double PS_l = Length(pr) + radius;
					double t = PS_l / Length(pq);
					if ((p < r && r < q) || (r < p && q < r)) {
						t = -t;
					}
					if (LineIsValid(type, t)) {
						Point s_l = p + norm_pr * PS_l;
						intersects.push_back(s_l);
					}

					double PS_r = 2 * radius - PS_l;
					t = PS_r / Length(pq);
					if ((p < r && r < q) || (r < p && q < r)) {
						t = -t;
					}
					if (LineIsValid(type, t)) {
						Point s_r = p + norm_pr * PS_r;
						intersects.push_back(s_r);
					}
				}
				else {
					double PM = CalculatePM(c, p, pq);
					double PS_l = CalculatePS_l(c, p, pq);
					double t = PS_l / Length(pq);
					if (LineIsValid(type, t)) {
						Point s_l = p + norm_pq * PS_l;
						intersects.push_back(s_l);
					}

					double PS_r = 2 * PM - PS_l;
					t = PS_r / Length(pq);
					if (LineIsValid(type, t)) {
						Point s_r = p + norm_pq * PS_r;
						intersects.push_back(s_r);
					}
				}
			}
		}
	}
}

void Intersection::solveCircleCircleIntersection() {
	int i, j;
	for (i = 0; i < (int)circles.size(); i++) {
		if (!circles[i].isExist) {
			continue;
		}
		for (j = i + 1; j < (int)circles.size(); j++) {
			if (!circles[j].isExist) {
				continue;
			}
			Heart p = circles[i].center;
			Heart q = circles[j].center;
			Vector pq = q - p;
			Vector norm_pq = Norm(pq);
			double p2q = Length(pq);
			double radius_1 = circles[i].radius;
			double radius_2 = circles[j].radius;

			if (dcmp(p.x - q.x) == 0 && dcmp(p.y - q.y) == 0 && dcmp(radius_1 - radius_2) == 0) {
				throw string("Բ��Բ�غ�");
				continue;
			}

			int status = dcmp(p2q - radius_1 - radius_2);
			if (status == 0) { // outside tangency
				intersects.push_back(p + norm_pq * radius_1);
			}
			else if (status > 0) { // outside disjoint
				continue;
			}
			else {
				status = dcmp(fabs(radius_1 - radius_2) - p2q);
				if (status == 0) { // inside tangency
					intersects.push_back(p + norm_pq * radius_1);
				}
				else if (status > 0) { // inside disjoint
					continue;
				}
				else {
					// double rad = CalculateAngle(circles[i], circles[j]);
					double ratio = (radius_1 * radius_1 + p2q * p2q - radius_2 * radius_2) / (2 * radius_1 * p2q);
					if (ratio > 1 - eps) {
						ratio = 1 - eps;
					}
					else if (ratio < eps - 1) {
						ratio = eps - 1;
					}
					double rad = acos(ratio);
					Vector s_l = Rotate(norm_pq, rad) * radius_1;
					Vector s_r = Rotate(norm_pq, -rad) * radius_1;
					intersects.push_back(p + s_l);
					intersects.push_back(p + s_r);
				}
			}
		}
	}
}

int Intersection::solveIntersection() {
	vector<Point>().swap(intersects);
	if (points.size() > 1) {
		solveLineLineIntersection();
	}
	if (circles.size() > 1) {
		solveCircleCircleIntersection();
	}
	if (points.size() > 0 && circles.size() > 0) {
		solveLineCircleIntersection();
	}

	// ------------------ Delete Duplicates ------------------------

	int size = (int)intersects.size();

	if (isPrintAllIntersections) {
		cout << "----------------------------------------------------------------------" << endl;
		cout << "before unique: " << size << endl;
		printAllIntersections();
	}

	sort(intersects.begin(), intersects.end());
	auto new_end = unique(intersects.begin(), intersects.end());

	assert(size == intersects.size()); // Fake Delete Duplicates

	intersects.erase(new_end, intersects.end()); // Real Delete Duplicates

	if (isPrintAllIntersections) {
		cout << "----------------------------------------------------------------------" << endl;
		cout << "after unique: " << intersects.size() << endl;
		printAllIntersections();
	}

	return (int)intersects.size();
}


void Intersection::printAllPoints(vector<Point> v) {
	auto it = v.begin();
	while (it != v.end()) {
		printf("%.10lf %.10lf\n", it->x, it->y);
		it++;
	}
}

void Intersection::printAllIntersections() {
	printAllPoints(intersects);
}

void Intersection::removeVector(int index) {
	points[index].isExist = false;
	vectors[index].isExist = false;
}

void Intersection::removeCircle(int index) {
	circles[index].isExist = false;
}

vector<Point> Intersection::getPoints(void) {
	return points;
}
vector<Vector> Intersection::getVectors(void) {
	return vectors;
}
vector<Point> Intersection::getIntersects(void) {
	return intersects;
}
vector<Circle> Intersection::getCircles(void) {
	return circles;
}

void Intersection::setVectorNotExist(int index) {
	points[index].isExist = false;
	vectors[index].isExist = false;
}

void Intersection::setCircleNotExist(int index) {
	circles[index].isExist = false;
}

void Intersection::clearGraph() {
	points.clear();
	vectors.clear();
	intersects.clear();
	circles.clear();
}
