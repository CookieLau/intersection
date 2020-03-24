#include <QFileDialog>
#include <QtCharts>
#include <fstream>
#include <map>
#include <QPixmap>
#include <regex>
#include <vector>
#include <iostream>
#include <qinputdialog.h>

#include "IntersectionGUI.h"
#include "../intersection/Intersection.h"
IntersectionGUI::IntersectionGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	intersection = new Intersection();
	connect(ui.openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.getResult, SIGNAL(clicked()), this, SLOT(getResult()));
	connect(ui.deleteShape, SIGNAL(clicked()), this, SLOT(deleteItem()));
	connect(ui.zoom_in, SIGNAL(clicked()), this, SLOT(zoom_in()));
	connect(ui.zoom_out, SIGNAL(clicked()), this, SLOT(zoom_out()));
	connect(ui.addItem, SIGNAL(clicked()), this, SLOT(addItem()));
	connect(ui.zoom_reset, SIGNAL(clicked()), this, SLOT(zoom_reset()));
	connect(ui.left, SIGNAL(clicked()), this, SLOT(moveLeft()));
	connect(ui.right, SIGNAL(clicked()), this, SLOT(moveRight()));
	connect(ui.up, SIGNAL(clicked()), this, SLOT(moveUp()));
	connect(ui.down, SIGNAL(clicked()), this, SLOT(moveDown()));

	QWidget *midShow = ui.centralWidget->findChild<QWidget *>("midShow");
	showPic = new ShowPic(midShow);
	showPic->setGeometry(0, 0, midShow->width(), midShow->height());
	showPic->setOffset(midShow->width() / 2, midShow->height() / 2);
	showPic->max_x = midShow->width();
	showPic->max_y = midShow->height();
}

void IntersectionGUI::zoom_in(void) {
	showPic->setScale(1.1);
	showPic->update();
}

void IntersectionGUI::zoom_out(void) {
	showPic->setScale(0.9);
	showPic->update();
}

void IntersectionGUI::zoom_reset(void) {
	showPic->zoom = 20;
	QWidget *midShow = ui.centralWidget->findChild<QWidget *>("midShow");
	showPic->setOffset(midShow->width() / 2, midShow->height() / 2);
	showPic->update();
}

void IntersectionGUI::moveLeft(void) {
	showPic->x_offset += 10;
	showPic->update();
}

void IntersectionGUI::moveRight(void) {
	showPic->x_offset -= 10;
	showPic->update();
}

void IntersectionGUI::moveUp(void) {
	showPic->y_offset += 10;
	showPic->update();
}

void IntersectionGUI::moveDown(void) {
	showPic->y_offset -= 10;
	showPic->update();
}



void IntersectionGUI::loadShape(QStringList& strList) {
	this->getResult();
	ui.allShapes->clear();
	vectorNameToIndex.erase(vectorNameToIndex.begin(), vectorNameToIndex.end());
	circleNameToIndex.erase(circleNameToIndex.begin(), circleNameToIndex.end());
	int indexCnt = 0;
	// int test = intersection->getVectors().size();
	for (auto item : intersection->getVectors()) {
		if (!item.isExist) {
			indexCnt++;
			continue;
		}
		int index = item.index;
		if (index > intersection->getPoints().size()) {
			printf("index:%d size:%d\n", index, intersection->getPoints().size());
			return;
		}
		auto ppoint = intersection->getPoints().at(index);
		QString linename = QString("%1(%2,%3,%4,%5)").arg(item.type).arg(ppoint.x).arg(ppoint.y).arg(ppoint.x + item.x).arg(ppoint.y + item.y);
		std::cout << linename.toStdString() << std::endl;
		strList << linename;
		vectorNameToIndex[linename.toStdString()] = indexCnt++;
	}
	indexCnt = 0;
	for (auto item : intersection->getCircles()) {
		if (!item.isExist) {
			indexCnt++;
			continue;
		}
		strList << QString::fromStdString(item.getName());
		circleNameToIndex[item.getName()] = indexCnt++;
	}
}

void IntersectionGUI::openFile(void) {
	intersection->clearGraph();
	QString filePath = QFileDialog::getOpenFileName(this, "Open File to Load", "./");
	QFileInfo fileInfo = QFileInfo(filePath);
	string file_path = fileInfo.absoluteFilePath().toStdString();
	ifstream in(file_path);
	intersection->getAllPoints(in);
	QStringList strList;
	loadShape(strList);
	ui.allShapes->addItems(strList);
	showPic->setIntersection(intersection);
	showPic->update();
	// add all names to the <shapeName, int> map
	// int res = intersection->solveIntersection();
	// ui.pointNumResult->setText(QString::number(res, 10));
}

void IntersectionGUI::getResult(void) {
	int res = intersection->solveIntersection();
	ui.pointNumResult->setText(QString("Answer:%1").arg(res));
	vector<Point> inters = intersection->getIntersects();
	ui.allIntersects->clear();
	for (auto p : inters) {
		ui.allIntersects->addItem(QString("(%1,%2)").arg(p.x).arg(p.y));
	}
}

void IntersectionGUI::addItem(void) {
	QStringList items;//ComboBox控件的内容
	items << QStringLiteral("Circle") << QStringLiteral("Line") << QStringLiteral("Ray") << QStringLiteral("Segments");
	QString dlgTitle = QStringLiteral("New figure: ");//对话框标题
	QString txtLabel = QStringLiteral("Choose a new one: ");//对话框Label显示内容
	int curIndex = 0;//ComboBox控件默认哪个索引的内容
	bool editable = true;//ComboBox控件内容是否可被编辑
	bool ok = false;
	QString text = QInputDialog::getItem(this, dlgTitle, txtLabel, items, curIndex, editable, &ok);
	if (ok && !text.isEmpty()) {
		std::cout << text.toStdString() << endl;
		std::string ttext = text.toStdString();
		ok = false;
		if (ttext != "Circle") {
			int x1 = QInputDialog::getInt(this, "X1:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			ok = false;
			int y1 = QInputDialog::getInt(this, "y1:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			ok = false;
			int x2 = QInputDialog::getInt(this, "X2:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			ok = false;
			int y2 = QInputDialog::getInt(this, "y2:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			intersection->addItem(ttext[0], x1, y1, x2, y2);
			ui.allShapes->addItem(QString("%1(%2,%3,%4,%5)").arg(ttext[0]).arg(x1).arg(y1).arg(x2 - x1).arg(y2 - y1));
		}
		else {
			int x1 = QInputDialog::getInt(this, "X1:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			ok = false;
			int y1 = QInputDialog::getInt(this, "y1:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			ok = false;
			int radius = QInputDialog::getInt(this, "radius:", "", 0, -99999, 99999, 1, &ok);
			if (!ok) {
				return;
			}
			try {
				intersection->addItem('C', x1, y1, radius, 0);
				ui.allShapes->addItem(QString("%1(%2,%3,%4)").arg(ttext[0]).arg(x1).arg(y1).arg(radius));
			}
			catch (std::string msg) {
				std::cout << "hhhhhhhhhhhhhhhhhhhhhh" << std::endl;
				//                QMessageBox::critical(0 , "critical message" , QString::fromStdString(msg), QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel | QMessageBox::Escape);
			}
		}
	}
	showPic->setIntersection(intersection);
	this->getResult();
}

void IntersectionGUI::deleteItem(void) {
	//QPoint pnt = QCursor::pos();
	//pnt = mapFromGlobal(pnt);
	//QListWidgetItem* item = ui.allShapes->itemAt(pnt);
	//string text = (item->text()).toStdString();
	int currenRow = ui.allShapes->currentRow();
	std::string text = (ui.allShapes->item(currenRow)->text()).toStdString();
	std::cout << text << endl;
	if (vectorNameToIndex.find(text) != vectorNameToIndex.end()) {
		int index = vectorNameToIndex[text];
		intersection->setVectorNotExist(index);
	}
	else if (circleNameToIndex.find(text) != circleNameToIndex.end()) {
		int index = circleNameToIndex[text];
		intersection->setCircleNotExist(index);
	}
	else {
		return;
	}
	ui.allShapes->takeItem(currenRow);
	showPic->setIntersection(intersection);
	this->getResult();
	showPic->update();
}

void IntersectionGUI::wheelEvent(QWheelEvent *event)
{
	QPoint pos;
	QPoint pos1;
	QPoint pos2;
	pos1 = mapToGlobal(QPoint(0, 0));
	pos2 = event->globalPos();
	pos = pos2 - pos1;

	//判断鼠标位置是否在图像显示区域
	if (pos.x() > showPic->x() && pos.x() < showPic->x() + showPic->width()
		&& pos.y() > showPic->y() && pos.y() < showPic->y() + showPic->height())
	{
		// 当滚轮远离使用者时进行放大，当滚轮向使用者方向旋转时进行缩小
		if (event->delta() > 0)
		{
			zoom_in();
		}
		else
		{
			zoom_out();
		}
	}

}
