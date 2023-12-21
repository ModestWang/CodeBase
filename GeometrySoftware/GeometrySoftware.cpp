#include "GeometrySoftware.h"
extern Points points;

//标志位
int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;
int button4_flag = 0;
int button5_flag = 0;

//构造函数
GeometrySoftware::GeometrySoftware(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.stackedWidget->addWidget(w1);
    ui.stackedWidget->addWidget(w2);
    ui.stackedWidget->addWidget(w3);
    ui.stackedWidget->setCurrentIndex(0);
    //使用添加Qt资源 ": + 前缀名 + 文件名"
    //ui.actionnew->setIcon(QIcon(":/bk1.jpg"));
    //ui.setIcon(QIcon("D:\\VS cord\\Data Structure\\CourseDesign\\resourse\\image\\bk1.jpg"));
    
    //连接按钮事件
    //connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(repaint()));
    connect(ui.pushButton_1, &QPushButton::clicked, this, &GeometrySoftware::button1_do);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &GeometrySoftware::button2_do);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &GeometrySoftware::button3_do);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &GeometrySoftware::button4_do);
    connect(ui.pushButton_5, &QPushButton::clicked, this, &GeometrySoftware::button5_do);
    connect(ui.pushButton,   &QPushButton::clicked, this, &GeometrySoftware:: secret_do);
    //连接动作
    connect(ui.actionRandom, &QAction::triggered, this, &GeometrySoftware::actionRandom_do);
    connect(ui.actionInput,  &QAction::triggered, this, &GeometrySoftware::actionInput_do);
}

//析构函数
GeometrySoftware::~GeometrySoftware()
{}

//四个按钮
void GeometrySoftware::button1_do()
{
    button5_flag = 0;
    ui.stackedWidget->setCurrentIndex(0);
}
void GeometrySoftware::button2_do()
{
    button5_flag = 0;
    ui.stackedWidget->setCurrentIndex(3);
}
void GeometrySoftware::button3_do()
{
    button5_flag = 0;
    ui.stackedWidget->setCurrentIndex(4);
}
void GeometrySoftware::button4_do()
{
    button5_flag = 0;
    ui.stackedWidget->setCurrentIndex(2);
}

//隐藏事件
void GeometrySoftware::button5_do()
{
    button5_flag = 1;
}
void GeometrySoftware::secret_do()
{
    if (button5_flag)
    ui.stackedWidget->setCurrentIndex(1);
}

//随机生成
void GeometrySoftware::actionRandom_do()
{
    randomCreateConvexHull = false; 
    randomCreateLine = true;
}
//用户输入
void GeometrySoftware::actionInput_do()
{
    randomCreateConvexHull = false;
    randomCreateLine = false;
}


void GeometrySoftware::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
}