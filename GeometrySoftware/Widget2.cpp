#include "Widget2.h"

Widget2::Widget2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    connect(ui.pushButton_1, &QPushButton::clicked, this, &Widget2::randomButton_do);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &Widget2::inputButton_do);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &Widget2::cleanButton_do);
    repaint();
}

Widget2::~Widget2()
{}

//随机生成
void Widget2::randomButton_do()
{
    points.resize(0);
    pointNumber1 = ui.spinBox_1->value();
    button_flag_random = 1;
    repaint();
}

//用户输入
void Widget2::inputButton_do()
{
    button_flag_input++;
    if (button_flag_input == 1)
    {
        points.resize(0);
        button_input = 1;
        pointNumber2 = ui.spinBox_2->value();
        if (pointNumber2 != 0) limit = true;
    }
    else if (button_flag_input == 2)
        ok = true;
    repaint();
}

//清除
void Widget2::cleanButton_do()
{
    points.resize(0);
    button_flag_clean= 1;
    repaint();
}

void Widget2::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QBrush brush(qRgb(160, 240, 240));
    painter.setBrush(brush);
    painter.drawRect(0, 0, 800, 600);
    //绘制坐标系
    QPen pen(Qt::black);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(QPoint(100, 300), QPoint(500, 300));
    painter.drawLine(QPoint(300, 100), QPoint(300, 500));

    if (button_flag_random)
    {
        //设置画笔样式
        QPen pen1(Qt::red);                  //画笔颜色
        pen1.setWidth(4);                    //画笔宽度
        pen1.setCapStyle(Qt::RoundCap);      //笔帽样式
        pen1.setJoinStyle(Qt::RoundJoin);    //结合点样式
        pen1.setStyle(Qt::SolidLine);        //线段样式
        painter.setPen(pen1);
        create_points(points, rangeX1, rangeY1, rangeX2, rangeY2, pointNumber1);
        //绘点
        for (Points::iterator i = points.begin(); i != points.end(); ++i)
        {
            painter.drawPoint(i->x + 300, -i->y + 300);
        }
        if (!points.empty())
        {
            QPen pen2;
            pen2.setWidth(2);                    //画笔宽度
            pen2.setCapStyle(Qt::RoundCap);      //笔帽样式
            pen2.setJoinStyle(Qt::RoundJoin);    //结合点样式
            pen2.setStyle(Qt::SolidLine);        //线段样式
            pen2.setColor(Qt::blue);
            painter.setPen(pen2);
            //计算
            CalcConvexHull(points);
            for (Points::iterator i = points.begin(); i != points.end() - 1; i++)
            {
                Points::iterator j = i + 1;
                painter.drawLine(QPoint(i->x + 300, -i->y + 300),
                    QPoint(j->x + 300, -j->y + 300));
            }
            painter.drawLine(QPoint(points.begin()->x + 300, -points.begin()->y + 300),
                QPoint((points.end() - 1)->x + 300, -(points.end() - 1)->y + 300));
        }
        button_flag_random = 0;
    }

    if (button_flag_input)
    {
        //设置画笔样式
        QPen pen1(Qt::red);                  //画笔颜色
        pen1.setWidth(4);                    //画笔宽度
        pen1.setCapStyle(Qt::RoundCap);      //笔帽样式
        pen1.setJoinStyle(Qt::RoundJoin);    //结合点样式
        pen1.setStyle(Qt::SolidLine);        //线段样式
        painter.setPen(pen1);
        //绘点
        for (Points::iterator i = points.begin(); i != points.end(); i++)
        {
            painter.drawPoint(i->x, i->y);
        }
        if (!points.empty() && ok)
        {
            QPen pen2;
            pen2.setWidth(2);                    //画笔宽度
            pen2.setCapStyle(Qt::RoundCap);      //笔帽样式
            pen2.setJoinStyle(Qt::RoundJoin);    //结合点样式
            pen2.setStyle(Qt::SolidLine);        //线段样式
            pen2.setColor(Qt::blue);
            painter.setPen(pen2);
            //计算
            CalcConvexHull(points);
            for (Points::iterator i = points.begin(); i != points.end() - 1; i++)
            {
                Points::iterator j = i + 1;
                painter.drawLine(QPoint(i->x, i->y),
                    QPoint(j->x, j->y));
            }
            painter.drawLine(QPoint(points.begin()->x, points.begin()->y),
                QPoint((points.end() - 1)->x, (points.end() - 1)->y));
            button_flag_input = 0;
        }
        
    }

    if (button_flag_clean)
    {
        points.resize(0);
        button_flag_clean = 0; 
        button_flag_random = 0;
        button_flag_input = 0;
        button_input = 0;
        number_now = 0;
        limit = false;
        ok = false;
    }

}

void Widget2::mousePressEvent(QMouseEvent* e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        if (button_input && limit)
        {
            Point point = { e->x(), e->y()};
            points.push_back(point);
            number_now = points.size();
            if (number_now == pointNumber2)
                ok = true;
            repaint();
        }
        else if (button_input && !limit)
        {
            Point point = { e->x(), e->y()};
            points.push_back(point);
            number_now = points.size();
            repaint();
        }
    }
}