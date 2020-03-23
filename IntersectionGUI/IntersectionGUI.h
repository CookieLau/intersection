#pragma once

#include <QtWidgets/QMainWindow>
#include <map>
#include <string>
#include <QtCharts>

#include "ui_IntersectionGUI.h"
#include "../src/Intersection.h"
#include "ShowPic.h"

QT_CHARTS_USE_NAMESPACE

class IntersectionGUI : public QMainWindow
{
	Q_OBJECT

public:
	Intersection* intersection;
	std::map<std::string, int> vectorNameToIndex;
	std::map<std::string, int> circleNameToIndex;
	IntersectionGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::IntersectionGUIClass ui;
	ShowPic *showPic;
private slots:
	void openFile(void);
	void loadShape(QStringList& strList);
	void getResult(void);
	void deleteItem(void);
	void zoom_in(void);
	void zoom_out(void);
	void wheelEvent(QWheelEvent *event);
};
