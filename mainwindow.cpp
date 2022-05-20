#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this); //таймер
    connect(timer, SIGNAL(timeout()),this, SLOT(Aclock())); //соединяем таймер с нашим слотом
    connect(this, SIGNAL(TextC(const QString)), ui->lineEdit, SLOT(setText(const QString))); //соединяем написанный сигнал с системным слотом в QLineEdit

    timer->start(500); //таймер для перезапуска функции(слота) вывода времени и проверки будильника
}

void MainWindow::Aclock()
{
    QTime time = QTime::currentTime(); //  Получаем текущее время
    QString text = time.toString("hh:mm"); //Перевод времени в стринг
    ui->lcdNumber->display(text); //Вывод времени
    if(ui->checkBox->checkState() == Qt::Checked) //проверка, включен ли будильник
    {
        if (ui->spinBox_2->value()==time.hour() && ui->spinBox->value()==time.minute()) //сравнение времени
            emit TextC("ПОРА ХАВАТЬ!!"); //Вывод сообщения
    }
    else ui->lineEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
