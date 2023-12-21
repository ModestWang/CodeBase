#include "Widget1.h"

//基本数据
extern int pointNumber;
extern int rangeX;
extern int rangeY;
//标志位
int button_flag_11 = 0;
int button_flag_12 = 0;


Widget1::Widget1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Widget1::~Widget1()
{}

void Widget1::pushButton_do()
{}

void Widget1::paintEvent(QPaintEvent*)
{}