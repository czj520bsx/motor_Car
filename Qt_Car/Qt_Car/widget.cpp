#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //遍历PC的端口号，添加在下拉框中
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBox_COM->addItem(info.portName());
    }

    //初始化串口
    serial.setBaudRate(QSerialPort::Baud9600);//波特率
    serial.setDataBits(QSerialPort::Data8);//8位数据位
    serial.setParity(QSerialPort::NoParity);//没有奇偶校验
    serial.setStopBits(QSerialPort::OneStop);//1位停止位
    serial.setFlowControl(QSerialPort::NoFlowControl);//没有流控
    connect(&serial, SIGNAL(readyRead()), this, SLOT(do_serial_recv()));




    //初始化图片显示
    QImage img;
    img.load(":/logo.png");//加载图片数据

    //图片自适应
    img.scaled(ui->label_Logo->size(), Qt::KeepAspectRatio);
    ui->label_Logo->setScaledContents(true);

    ui->label_Logo->setPixmap(QPixmap::fromImage(img));//显示图片
    //静态成员函数 fromImage


}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_serial_recv()
{
    char recvbuff[5] = "";
    if(serial.bytesAvailable() > 0){
           QByteArray data = serial.readAll(); // 读取串口数据
           QString text = QString::fromUtf8(data); // 将数据转换为QString格式

           // 将收到的文本放大并显示在TextEdit控件上，并居中显示
           QString newText = "<center><font size=\"100\">Speed：" + text + "</font></center>"; // 设置文本大小为100，并居中显示
           ui->textEdit_Msg->setText(newText);
    }



}
void Widget::on_pushButton_Open_clicked()
{
    serial.close();

    QString PortName = ui->comboBox_COM->currentText();
    serial.setPortName(PortName);
    if(serial.open(QIODevice::ReadWrite)){
        qDebug() << "打开" << PortName << "成功！！！！";
        serial.flush();

    }else{
        qDebug() << "打开串口失败";
    }
}


void Widget::on_pushButton_go_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x11, 0x00, 0x00, 0xbb};//前进
    int speed = 700;
    //拆高8位
    send_buff[3] = (speed & ~(0xff)) >> 8;
    //拆低8位
    send_buff[4] = (speed & 0xff);
    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton_go_released()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}
void Widget::paintEvent(QPaintEvent *)
{
    //自动调用此函数
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/down.jpeg"));
}



void Widget::on_pushButton_left_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x33, 0x00, 0x00, 0xbb}; // 初始化数据包
    int speed = 700; // 设置速度



    // 拆分速度为高8位和低8位
    send_buff[3] = (speed & ~(0xff)) >> 8; // 高8位
    send_buff[4] = (speed & 0xff);          // 低8位

    // 发送数据包
    serial.write((char *)send_buff, 6);
    serial.flush(); // 刷新缓冲区
}

void Widget::on_pushButton_right_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x22, 0x00, 0x00, 0xbb}; // 初始化数据包
    int speed = 700; // 设置速度



    // 拆分速度为高8位和低8位
    send_buff[3] = (speed & ~(0xff)) >> 8; // 高8位
    send_buff[4] = (speed & 0xff);          // 低8位

    // 发送数据包
    serial.write((char *)send_buff, 6);
    serial.flush(); // 刷新缓冲区
}

void Widget::on_pushButton_back_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x44, 0x00, 0x00, 0xbb}; // 初始化数据包
    int speed = 700; // 设置速度



    // 拆分速度为高8位和低8位
    send_buff[3] = (speed & ~(0xff)) >> 8; // 高8位
    send_buff[4] = (speed & 0xff);          // 低8位

    // 发送数据包
    serial.write((char *)send_buff, 6);
    serial.flush(); // 刷新缓冲区
}



void Widget::on_pushButton_left_released()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton_right_released()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton_back_released()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton_Auto_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x22, 0x00, 0x00, 0x00, 0xbb}; // 初始化数据包
    int speed = 700; // 设置速度

    // 拆分速度为高8位和低8位
    send_buff[3] = (speed & ~(0xff)) >> 8; // 高8位
    send_buff[4] = (speed & 0xff);          // 低8位

    // 发送数据包
    serial.write((char *)send_buff, 6);
    serial.flush(); // 刷新缓冲区
}
void Widget::on_pushButton_Auto_released()
{
    uint8_t send_buff[6] = {0xaa, 0x22, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}



void Widget::on_pushButton_UnAUto_pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//前进
    int speed = 700;
    //拆高8位
    send_buff[3] = (speed & ~(0xff)) >> 8;
    //拆低8位
    send_buff[4] = (speed & 0xff);
    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton_UnAUto_released()
{
    uint8_t send_buff[6] = {0xaa, 0x11, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}




void Widget::on_pushButton__pressed()
{
    uint8_t send_buff[6] = {0xaa, 0x33, 0x00, 0x00, 0x00, 0xbb};//前进
    int speed = 700;
    //拆高8位
    send_buff[3] = (speed & ~(0xff)) >> 8;
    //拆低8位
    send_buff[4] = (speed & 0xff);
    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}

void Widget::on_pushButton__released()
{
    uint8_t send_buff[6] = {0xaa, 0x33, 0x00, 0x00, 0x00, 0xbb};//停止

    serial.write((char *)send_buff, 6);//发送
    serial.flush();//刷新缓存区，保证数据发送
}
