#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IntersectionGUI.h"
#include "..\src\Intersection.h"

class IntersectionGUI : public QMainWindow
{
	Q_OBJECT

public:
	Intersection* intersection;
	IntersectionGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::IntersectionGUIClass ui;
private slots:
	void openFile(void);
	
};
