#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IntersectionGUI.h"

class IntersectionGUI : public QMainWindow
{
	Q_OBJECT

public:
	IntersectionGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::IntersectionGUIClass ui;
};
