#include "Solution.h"

//生成点集
void create_points(Points& points, int x1, int y1, int x2, int y2, int num) 
{
    srand((unsigned)time(0));
    
    int pointNum = num;         //生成的随机点数量
    int rangeX = x2 - x1 + 1;   //生成的随机点范围
    int rangeY = y2 - y1 + 1;   //生成的随机点范围

    for (int i = 0; i < pointNum; i++)
    {
        Point newPoint = { rand() % rangeX + x1, rand() % rangeY + y1 };
        points.push_back(newPoint);
        std::cout << "(" << newPoint.x << ", " << newPoint.y << ")" << std::endl;
    }
}

//开始凸包求解
void start_ConvexHull(Points& points)
{
    //创建点
    //create_points(points, x, y, num);
    //计算运行时间
    time_t   c_start, c_end;
    c_start = clock();
    CalcConvexHull(points);
    c_end = clock();

    std::cout << "\nConvex Hull:\n";
    for (Points::iterator i = points.begin(); i != points.end(); i++)
    {
        std::cout << "(" << i->x << ", " << i->y << ")" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "The running time is " << difftime(c_end, c_start) << "ms." << std::endl;
}

//判断两个点是否相等
bool operator==(const Point& point1, const Point& point2)
{
    return (point1.x == point2.x && point1.y == point2.y);
}

//比较两个向量point1和point2分别与x轴正向单位向量(1, 0)的夹角
bool CompareVector(const Point& point1, const Point& point2)
{
    //求向量的模
    double m1 = sqrt(((double)point1.x * (double)point1.x + (double)point1.y * (double)point1.y));
    double m2 = sqrt(((double)point2.x * (double)point2.x + (double)point2.y * (double)point2.y));

    //两个向量分别与(1, 0)求内积
    double v1 = point1.x / m1;
    double v2 = point2.x / m2;
    return (v1 > v2 || (v1 == v2 && m1 < m2));
}

//计算凸包
void CalcConvexHull(Points& points)
{
    //点集中至少应有3个点，才能构成多边形
    if (points.size() < 3)
        return;

    //查找基点
    Point pointBase = points.front(); //将第1个点预设为最小点
    for (Points::iterator i = points.begin() + 1; i != points.end(); i++)
    {
        //如果当前点的y值小于最小点，或y值相等，x值较小
        if (i->y < pointBase.y || (i->y == pointBase.y && i->x < pointBase.x))
        {
            //将当前点作为最小点
            pointBase = *i;
        }
    }

    //计算出各点与基点构成的向量
    for (Points::iterator i = points.begin(); i != points.end();)
    {
        //排除与基点相同的点，避免后面的排序计算中出现除0错误
        if (*i == pointBase)
        {
            i = points.erase(i);
        }
        else
        {
            //求向量，方向由基点到目标点
            i->x -= pointBase.x;
            i->y -= pointBase.y;
            i++;
        }
    }

    //按各向量与横坐标之间的夹角排序
    angle_sort(points);

    //删除相同的向量
    points.erase(unique(points.begin(), points.end()), points.end());

    //计算得到首尾依次相联的向量
    for (Points::reverse_iterator r = points.rbegin();
        r != points.rend() - 1; ++r)
    {
        Points::reverse_iterator rNext = r + 1;
        //向量三角形计算公式
        r->x -= rNext->x;
        r->y -= rNext->y;
    }

    //依次删除不在凸包上的向量
    for (Points::iterator i = points.begin() + 1; i != points.end(); i++)
    {
        //回溯删除旋转方向相反的向量，使用外积判断旋转方向
        for (Points::iterator iLast = i - 1; iLast != points.begin();)
        {
            int v1 = i->x * iLast->y;
            int v2 = i->y * iLast->x;
            //如果叉积小于0，则无没有逆向旋转
            //如果叉积等于0，还需判断方向是否相逆
            if (v1 < v2 || (v1 == v2 && i->x * iLast->x > 0 && i->y * iLast->y > 0))
            {
                break;
            }
            //删除前一个向量后，需更新当前向量，与前面的向量首尾相连
            //向量三角形计算公式
            i->x += iLast->x;
            i->y += iLast->y;
            iLast = (i = points.erase(iLast)) - 1;
        }
    }

    //将所有首尾相连的向量依次累加，换算成坐标
    points.front().x += pointBase.x, points.front().y += pointBase.y;
    for (Points::iterator i = points.begin() + 1; i != points.end(); i++)
    {
        i->x += (i - 1)->x;
        i->y += (i - 1)->y;
    }

    //添加基点，全部的凸包计算完成
    points.push_back(pointBase);
}

//排序
void angle_sort(Points& v)
{
    sort(v.begin(), v.end(), &CompareVector);
}

//确定两线段是否相交
/*
向量a(x1,y1)和b(x2,y2)的叉积
a×b = x1y2-x2y1
*/
int CrossProduct(Vector a, Vector b) 
{
    return a.x * b.y - a.y * b.x;
}
MXY MbrConstruct(Point A, Point B) 
{
    MXY m;
    /*将点A和点B中x值大的赋给xmax，小的赋给xmin*/
    if (A.x > B.x) 
    {
        m.xmax = A.x;
        m.xmin = B.x;
    }
    else 
    {
        m.xmax = B.x;
        m.xmin = A.x;
    }
    /*将点A和点B中y值大的赋给ymax，小的赋给ymin*/
    if (A.y > B.y) 
    {
        m.ymax = A.y;
        m.ymin = B.y;
    }
    else 
    {
        m.ymax = B.y;
        m.ymin = A.y;
    }
    return m;
}

/*
快速排斥实验【两个MXY在x以及y坐标的投影是否有重合】
判断两个MXY是否有交集，有返回1，否0
*/
bool MbrOverlap(MXY m1, MXY m2) 
{
    double xmin, xmax, ymin, ymax;
    xmin = std::max(m1.xmin, m2.xmin);   //两个外包矩形中最小x中的大者
    xmax = std::min(m1.xmax, m2.xmax);   //两个外包矩形中最大x中的小者
    ymin = std::max(m1.ymin, m2.ymin);   //两个外包矩形中最小y中的大者
    ymax = std::min(m1.ymax, m2.ymax);   //两个外包矩形中最大y中的小者

    /*
    如果：两个外包矩形中最大x中的小者 >= 两个外包矩形中最小x中的大者
    并且：两个外包矩形中最大y中的小者 >= 两个外包矩形中最小y中的大者
    则两个MXY是有交集，返回1
    */
    return (xmax >= xmin && ymax >= ymin);
}

/*
方法：快速排斥+跨立
判断两线段(线段AB和CD)是否相交，是返回1，否0
*/
bool cross_line(Point A, Point B, Point C, Point D) 
{
    MXY m1, m2;
    Vector CA, CB, CD, AC, AD, AB;
    /*求线段AB和CD所在的MXY*/
    m1 = MbrConstruct(A, B);
    m2 = MbrConstruct(C, D);
    /*【快速排斥实验】判断AB和CD所在的MXY是否相交*/
    if (MbrOverlap(m1, m2) == 0) //不相交，直接返回0
        return false;
    /*求向量CA、CB、CD的坐标表示*/
    CA = { C.x - A.x, C.y - A.y };
    CB = { C.x - B.x, C.y - B.y };
    CD = { C.x - D.x, C.y - D.y };
    /*求向量AC、AD、AB的坐标表示*/
    AC = { A.x - C.x, A.y - C.y };
    AD = { A.x - D.x, A.y - D.y };
    AB = { A.x - B.x, A.y - B.y };
    /*【跨立实验】进一步判断*/
    /*AB跨立CD，并且，CD跨立AB*/
    /*判断条件：(CA×CD)*(CB×CD)<= 0 && (AC×AB)*(AD×AB)<= 0*/
    if (CrossProduct(CA, CD) * CrossProduct(CB, CD) <= 0 && 
        CrossProduct(AC, AB) * CrossProduct(AD, AB) <= 0)
        return true;
    else
        return false;
}