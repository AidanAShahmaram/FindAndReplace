#include "mainwindow.h"

#include <QApplication>
#include "DocFile.h"

int main(int argc, char *argv[])
{
    DocFile doc;
    QApplication a(argc, argv);
    MainWindow w;
    w.setDocFile(&doc);
    w.show();
    return a.exec();
}
