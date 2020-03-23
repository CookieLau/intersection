#include <QFileDialog>
#include <QtCharts>
#include <fstream>
#include <map>
#include <QPixmap>
#include <regex>

#include "IntersectionGUI.h"
#include "../src/Intersection.h"
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

	QWidget *midShow = ui.centralWidget->findChild<QWidget *>("midShow");
	showPic = new ShowPic(midShow);
	showPic->setGeometry(0, 0, midShow->width(), midShow->height());
	showPic->setOffset(midShow->width() / 2, midShow->height() / 2);

}

void IntersectionGUI::zoom_in(void) {
	showPic->setScale(1.1);
	showPic->update();
}

void IntersectionGUI::zoom_out(void) {
	showPic->setScale(0.9);
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
			continue;
		}
		int index = item.index;
		if (index > intersection->getPoints().size()) {
			printf("%d %d\n", index, intersection->getPoints().size());
			return;
		}
		auto ppoint = intersection->getPoints().at(index);
		QString linename = QString("%1(%2,%3,%4,%5)").arg(item.type).arg(ppoint.x).arg(ppoint.y).arg(item.x).arg(item.y);
		strList << linename;
		vectorNameToIndex[item.getName()] = indexCnt++;
	}
	indexCnt = 0;
	for (auto item : intersection->getCircles()) {
		if (!item.isExist) {
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
}

void IntersectionGUI::deleteItem(void) {
	//QPoint pnt = QCursor::pos();
	//pnt = mapFromGlobal(pnt);
	//QListWidgetItem* item = ui.allShapes->itemAt(pnt);
	//string text = (item->text()).toStdString();
	int currenRow = ui.allShapes->currentRow();
	std::string text = (ui.allShapes->item(currenRow)->text()).toStdString();
	std::smatch sm;
	if (text[0] != 'C') {
		std::regex reg("*(*,*,*,*)");
		if (std::regex_match(text, sm, reg)) {
			for (int k = 0; k < sm.size(); k++) {
				std::cout << sm[k] << endl;
			}
		}
	}
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
