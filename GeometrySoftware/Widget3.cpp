#include "Widget3.h"

Widget3::Widget3(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	connect(ui.pushButton, &QPushButton::clicked, this, &Widget3::inputButton_do);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &Widget3::cleanButton_do);
	update();
}

Widget3::~Widget3()
{}

void Widget3::inputButton_do()
{
	button_flag_31 = 1;
	update();
}

void Widget3::cleanButton_do()
{
	button_flag_32 = 1;
	update();
}

void Widget3::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	//填充背景
	QBrush brush(qRgb(255, 255, 130));
	painter.setBrush(brush);
	painter.drawRect(0, 0, 800, 600);
	//绘制坐标系
	QPen pen(Qt::black);
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);
	painter.setPen(pen);
	painter.drawLine(QPoint(100, 300), QPoint(500, 300));
	painter.drawLine(QPoint(300, 100), QPoint(300, 500));
	if (button_flag_31)
	{
		QStringList A = ui.lineEdit_1->text().split(",");
		QStringList B = ui.lineEdit_2->text().split(",");
		QStringList C = ui.lineEdit_3->text().split(",");
		QStringList D = ui.lineEdit_4->text().split(",");
		Point a = {A[0].toInt(), A[1].toInt()};
		Point b = {B[0].toInt(), B[1].toInt()};
		Point c = {C[0].toInt(), C[1].toInt()};
		Point d = {D[0].toInt(), D[1].toInt()};
		//设置画笔样式
		QPen pen1(Qt::red);                  //画笔颜色
		pen1.setWidth(4);                    //画笔宽度
		pen1.setCapStyle(Qt::RoundCap);      //笔帽样式
		pen1.setJoinStyle(Qt::RoundJoin);    //结合点样式
		pen1.setStyle(Qt::SolidLine);        //线段样式
		painter.setPen(pen1);
		painter.drawPoint(a.x + 300, -a.y + 300);
		painter.drawPoint(b.x + 300, -b.y + 300);
		painter.drawPoint(c.x + 300, -c.y + 300);
		painter.drawPoint(d.x + 300, -d.y + 300);
		//设置画笔样式
		QPen pen2;
		pen2.setWidth(2);                    //画笔宽度
		pen2.setCapStyle(Qt::RoundCap);      //笔帽样式
		pen2.setJoinStyle(Qt::RoundJoin);    //结合点样式
		pen2.setStyle(Qt::SolidLine);        //线段样式
		pen2.setColor(Qt::blue);
		painter.setPen(pen2);
		painter.drawLine(QPoint(a.x + 300, -a.y + 300), QPoint(b.x + 300, -b.y + 300));
		painter.drawLine(QPoint(c.x + 300, -c.y + 300), QPoint(d.x + 300, -d.y + 300));
		//判断是否相交
		if (cross_line(a, b, c, d))
		{
			ui.label->setText("两线段相交");
		}
		else
		{
			ui.label->setText("两线段没有相交");
		}
		button_flag_31 = 0;
	}

	if (button_flag_32)
	{
		ui.label->setText("");
		button_flag_32 = 0;
	}
}
