#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GeometrySoftware.h"
#include "Widget1.h"
#include "Widget2.h"
#include "Widget3.h"
#include <qpainter.h>
#include <qinputdialog.h>
#include <Windows.h>
#include "Solution.h"


class GeometrySoftware : public QMainWindow
{
    Q_OBJECT

public:

    GeometrySoftware(QWidget *parent = nullptr);
    void button1_do();
    void button2_do();
    void button3_do();
    void button4_do();
    void button5_do();
    void actionRandom_do();
    void actionInput_do();
    ~GeometrySoftware();
protected:
    void paintEvent(QPaintEvent*);
    void secret_do();
private:
    Ui::GeometrySoftwareClass ui;
    bool randomCreateConvexHull = true;
    bool randomCreateLine = true;
    Widget1* w1 = new Widget1;
    Widget2* w2 = new Widget2;
    Widget3* w3 = new Widget3;
};
