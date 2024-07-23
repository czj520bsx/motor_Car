#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>//串口
#include <QSerialPortInfo>//串口信息
#include <QPainter>//画家
#include <QPaintEvent>//绘图事件
#include <QMediaPlayer>//媒体播放类


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent*);//绘图事件

private slots:
    void do_serial_recv();

    void on_pushButton_Open_clicked();


    void on_pushButton_go_pressed();

    void on_pushButton_go_released();





    void on_pushButton_left_pressed();

    void on_pushButton_right_pressed();

    void on_pushButton_back_pressed();

    void on_pushButton_Auto_pressed();

    void on_pushButton_left_released();

    void on_pushButton_right_released();

    void on_pushButton_back_released();

    void on_pushButton_Auto_released();

    void on_pushButton_UnAUto_pressed();

    void on_pushButton_UnAUto_released();
    void onReadyRead();

    void on_pushButton__pressed();

    void on_pushButton__released();
    void readSerialData();

private:
    Ui::Widget *ui;


    QSerialPort serial;
};
#endif // WIDGET_H
