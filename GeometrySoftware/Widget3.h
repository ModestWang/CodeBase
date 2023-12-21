#pragma once

#include <QWidget>
#include <qpainter.h>
#include "ui_Widget3.h"
#include "Solution.h"

class Widget3 : public QWidget
{
	Q_OBJECT

public:
	Widget3(QWidget *parent = nullptr);
	void inputButton_do();
	void cleanButton_do();
	~Widget3();
protected:
	void paintEvent(QPaintEvent*);
private:
	Ui::Widget3Class ui;
	//标志位
	int button_flag_31 = 0;
	int button_flag_32 = 0;
};
