#pragma once

#include <QWidget>
#include <qevent.h>
#include <qpainter.h>
#include <qinputdialog.h>
#include "ui_Widget2.h"
#include <string>
#include "Solution.h"

class Widget2 : public QWidget
{
	Q_OBJECT

public:
	Widget2(QWidget *parent = nullptr);
	void randomButton_do();
	void inputButton_do();
	void cleanButton_do();
	~Widget2();
protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
private:
	Ui::Widget2Class ui;
	Points points;
	//基本数据
	int pointNumber1 = 20;
	int pointNumber2 = 3;
	int rangeX1 = -200;
	int rangeY1 = -200;
	int rangeX2 = 200;
	int rangeY2 = 200;
	//标志位
	int button_flag_random = 0;
	int button_flag_input = 0;
	int button_flag_clean = 0;
	int button_input = 0;
	int number_now = 0;
	bool limit = false;
	bool ok = 0;
};
