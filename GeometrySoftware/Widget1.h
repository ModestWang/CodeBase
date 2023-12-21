#pragma once

#include <QWidget>
#include <qpainter.h>
#include "ui_Widget1.h"

class Widget1 : public QWidget
{
	Q_OBJECT

public:
	Widget1(QWidget *parent = nullptr);
	void pushButton_do();
	~Widget1();
protected:
	void paintEvent(QPaintEvent*);
private:
	Ui::Widget1Class ui;
};
