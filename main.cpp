#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Enterprise Architect 延长试用助手");
    MainWindow w;
    w.show();

    return a.exec();
}
