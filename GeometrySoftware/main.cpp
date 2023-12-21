#include "GeometrySoftware.h"
#include <QtWidgets/QApplication>
#include "Solution.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeometrySoftware w;
    w.show();

    return a.exec();
}
