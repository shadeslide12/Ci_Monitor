#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("./mon_outlet.dat");
    qint64 filePos = 0;
    qint64 textPos = 0; 
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "failed to open file";
        return -1;
    }

    QTextStream in(&file);
    qDebug() << in.readLine();
    filePos = file.pos();
    qDebug() << filePos;
    textPos = in.pos();
    qDebug() << textPos;

    qDebug() << in.readLine();
    filePos = file.pos();
    qDebug() << filePos;
    textPos = in.pos();
    qDebug() << textPos;
    filePos = file.pos();
    qDebug() << filePos;
    return a.exec();
}