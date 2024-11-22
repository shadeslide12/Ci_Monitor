#include <QApplication>
#include "mainwindow.h"
#include <QDir>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QDir::setCurrent("/home/tux/ZJUI_Test/Rotor67_GUI");
    MainWindow w;
    w.show();

    return app.exec();
}
