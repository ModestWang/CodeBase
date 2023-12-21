#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
//using namespace std;

struct Point
{
    int x;
    int y;
}; //点
typedef std::vector<Point> Points;

struct Vector 
{
    int x;
    int y;
}; //向量

struct MXY
{
    int xmax, xmin; //矩形在x轴的最小值和最大值
    int ymax, ymin; //矩形在y轴的最小值和最大值
}; //最小外包矩形

//函数声明
// <1>//排序
void angle_sort(Points& v);
// <2>//判断两个点是否相等(运算符重载)
bool operator==(const Point& point1, const Point& point2);
// <3>//比较两个向量point1和point2分别与x轴向量(1, 0)的夹角
bool CompareVector(const Point& point1, const Point& point2);
// <4>//创建点
void create_points(Points& points, int x1 = -200, int y1 = -200, int x2 = -200, int y2 = -200, int num = 100);
// <5>//计算凸包
void CalcConvexHull(Points& points);
// <6>//开始“凸包”问题
void start_ConvexHull(Points& points);
// <7>//确定两线段是否相交
bool cross_line(Point A, Point B, Point C, Point D);
