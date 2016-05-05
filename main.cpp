#include "mainwindow.h"
#include <QApplication>

QTextStream qtErr(stderr);
QTextStream qtCout(stdout);


int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }
    catch (const std::exception & e) {
        qtErr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}
