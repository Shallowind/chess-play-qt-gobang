#include "Headers/form.h"
#include "Headers/mainwindow.h"
#include "Headers/quanju.h"
#include "ui_form.h"
#include <QMessageBox>
int pain=0;
Form::Form(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    this->setWindowTitle("ChessPlay！");
    ui->setupUi(this);resize(1200, 900);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_6->setVisible(false);

    ui->pushButton_3->setStyleSheet("border-image: url(:/new/prefix1/resource/kaishi.png);");
    ui->pushButton_5->setStyleSheet("border-image: url(:/new/prefix1/resource/hei.png);");
    ui->pushButton_6->setStyleSheet("border-image: url(:/new/prefix1/resource/bai.png);");
    ui->pushButton->setStyleSheet("border-image: url(:/new/prefix1/resource/ai.png);");
    ui->pushButton_2->setStyleSheet("border-image: url(:/new/prefix1/resource/shuangren.png);");
    ui->pushButton_22->setStyleSheet("border-image: url(:/new/prefix1/resource/fanhui.png);");
    ui->pushButton_17->setStyleSheet("border-image: url(:/new/prefix1/resource/shezhi.png);");

    ui->label->setVisible(false);ui->label_2->setVisible(false);ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);ui->label_6->setVisible(false);ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);ui->label_13->setVisible(false);ui->label_14->setVisible(false);
    ui->label_17->setVisible(false);ui->label_18->setVisible(false);ui->label_19->setVisible(false);
    ui->label_21->setVisible(false);ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);ui->label_27->setVisible(false);ui->label_28->setVisible(false);
    ui->label_30->setVisible(false);//1 2 3 5 6 17
    ui->pushButton_4->setVisible(false);ui->pushButton_7->setVisible(false);
    ui->pushButton_8->setVisible(false);ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);ui->pushButton_15->setVisible(false);
    ui->pushButton_16->setVisible(false);ui->pushButton_18->setVisible(false);
    ui->pushButton_19->setVisible(false);ui->pushButton_20->setVisible(false);
    ui->pushButton_21->setVisible(false);ui->pushButton_22->setVisible(false);
    //
    ui->label->setAlignment(Qt::AlignCenter);ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_4->setAlignment(Qt::AlignCenter);ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_6->setAlignment(Qt::AlignCenter);ui->label_10->setAlignment(Qt::AlignCenter);
    ui->label_11->setAlignment(Qt::AlignCenter);ui->label_13->setAlignment(Qt::AlignCenter);
    ui->label_14->setAlignment(Qt::AlignCenter);ui->label_17->setAlignment(Qt::AlignCenter);
    ui->label_18->setAlignment(Qt::AlignCenter);ui->label_19->setAlignment(Qt::AlignCenter);
    ui->label_21->setAlignment(Qt::AlignCenter);
    ui->label_23->setAlignment(Qt::AlignCenter);
    ui->label_24->setAlignment(Qt::AlignCenter);ui->label_27->setAlignment(Qt::AlignCenter);
    ui->label_28->setAlignment(Qt::AlignCenter);ui->label_30->setAlignment(Qt::AlignCenter);

    ui->label->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_2->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_4->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_5->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_6->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_10->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_11->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_13->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_14->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_17->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_18->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_19->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_21->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_23->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_24->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_27->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_28->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_30->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->pushButton_7->setStyleSheet("border-image: url(:/new/prefix1/resource/ti.png);");
    ui->pushButton_4->setStyleSheet("border-image: url(:/new/prefix1/resource/ti.png);");
    ui->pushButton_14->setStyleSheet("border-image: url(:/new/prefix1/resource/ti.png);");
    seticon();

}

Form::~Form()
{
    delete ui;
}

void Form::setBackground()
{
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/resource/begin.png");
    QImage fitimgpic = ImgAllbackground.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

void Form::seticon(){
    ui->pushButton_18->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_19->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_20->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_21->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_11->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_12->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_16->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_8->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_10->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_13->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_15->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    ui->pushButton_9->setStyleSheet("border-image: url(:/new/prefix1/resource/weixuan.png);");
    switch (chess_n) {
    case 11:
        ui->pushButton_18->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    case 15:
        ui->pushButton_19->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    case 19:
        ui->pushButton_20->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    case 23:
        ui->pushButton_21->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    }
    switch (value_jinshou) {
    case 1:
        ui->pushButton_11->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    case 0:
        ui->pushButton_10->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    }
    switch (ikun) {
    case 1:
        ui->pushButton_8->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    case 0:
        ui->pushButton_9->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
        break;
    }
    if(wushouliangda||sanshoujiaohuan)ui->pushButton_12->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
    else ui->pushButton_13->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
    if(yin)ui->pushButton_16->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
    else ui->pushButton_15->setStyleSheet("border-image: url(:/new/prefix1/resource/yixuan.png);");
}

void Form::resizeEvent(QResizeEvent* event)
{
    this->setBackground();
    ui->label->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_2->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_4->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_5->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_6->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_10->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_11->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_13->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_14->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_17->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_18->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_19->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_21->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_23->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_24->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_27->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_28->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->label_30->setFont(QFont("黑体", min(this->width(), this->height()) / 50));

}

void Form::on_pushButton_clicked()
{
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
}

void Form::on_pushButton_2_clicked()
{
    fupan = -1;
    aiop = '3';
    num_step = 0;
    op = '1';
    items.clear();
    xitems.clear();
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }
    this->close();
    MainWindow* w = new MainWindow();
    w->setWindowTitle("ChessPlay！");
    w->show();
}

void Form::on_pushButton_5_clicked()
{
    fupan = -1;
    aiop = '2';
    items.clear();
    xitems.clear();
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }

    this->close();
    MainWindow* w = new MainWindow();
    w->setWindowTitle("ChessPlay！");
    w->show();
}

void Form::on_pushButton_6_clicked()
{
    fupan = -1;
    aiop = '1';
    items.clear();
    xitems.clear();
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }
    QPoint pt;
    int x = chess_n / 2, y = chess_n / 2;
    pt.setX(y);
    pt.setY(x);
    Item item(pt, '1'); // 设定棋子坐标及颜色
    items.append(item); // 添加棋子到所有的棋子Q
    chess[x][y] = '1';
    this->close();
    MainWindow* w = new MainWindow();
    w->setWindowTitle("ChessPlay！");
    w->show();
}

void Form::on_pushButton_3_clicked()
{
    ui->pushButton_17->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);

//    fupan = -1;
//    aiop = '1';
//    items.clear();
//    xitems.clear();
//    for (int i = 0; i < chess_n; i++) {
//        for (int j = 0; j < chess_n; j++) {
//            chess[i][j] = '0';
//        }
//    }
//    this->close();
//    MainWindow* w = new MainWindow();
//    w->setWindowTitle("ChessPlay！");
//    w->show();
}

void Form::on_pushButton_17_clicked()
{
    pain=1;
    ui->label->setVisible(true);ui->label_2->setVisible(true);ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);ui->label_6->setVisible(true);ui->label_10->setVisible(true);
    ui->label_11->setVisible(true);ui->label_13->setVisible(true);ui->label_14->setVisible(true);
    ui->label_17->setVisible(true);ui->label_18->setVisible(true);ui->label_19->setVisible(true);
    ui->label_21->setVisible(true);ui->label_23->setVisible(true);
    ui->label_24->setVisible(true);ui->label_27->setVisible(true);ui->label_28->setVisible(true);
    ui->label_30->setVisible(true);//1 2 3 5 6 17
    ui->pushButton_4->setVisible(true);ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);ui->pushButton_9->setVisible(true);
    ui->pushButton_10->setVisible(true);ui->pushButton_11->setVisible(true);
    ui->pushButton_12->setVisible(true);ui->pushButton_13->setVisible(true);
    ui->pushButton_14->setVisible(true);ui->pushButton_15->setVisible(true);
    ui->pushButton_16->setVisible(true);ui->pushButton_18->setVisible(true);
    ui->pushButton_19->setVisible(true);ui->pushButton_20->setVisible(true);
    ui->pushButton_21->setVisible(true);ui->pushButton_22->setVisible(true);
    ui->pushButton_17->setVisible(false);ui->pushButton_3->setVisible(false);


}
void Form::paintEvent(QPaintEvent*){
    if(pain==0)return;
    int a, b;
    a = (this->width() * 90 / 100);
    b = (this->height() * 90 / 100);


    QPainter painter(this);
    QRect rect;
    rect.setWidth(a);
    rect.setHeight(b);
    rect.moveCenter(this->rect().center());
    QPen pen;
    pen.setColor(QColor(150, 120, 100));
    pen.setWidth(a / 80); // Decrease the width of the pen
    painter.setPen(pen);
    painter.setBrush(QColor(226, 201, 177));
    painter.drawRect(rect);
    update();




}
void Form::on_pushButton_22_clicked()
{
    pain=0;
    ui->label->setVisible(false);ui->label_2->setVisible(false);ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);ui->label_6->setVisible(false);ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);ui->label_13->setVisible(false);ui->label_14->setVisible(false);
    ui->label_17->setVisible(false);ui->label_18->setVisible(false);ui->label_19->setVisible(false);
    ui->label_21->setVisible(false);ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);ui->label_27->setVisible(false);ui->label_28->setVisible(false);
    ui->label_30->setVisible(false);//1 2 3 5 6 17
    ui->pushButton_4->setVisible(false);ui->pushButton_7->setVisible(false);
    ui->pushButton_8->setVisible(false);ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);ui->pushButton_11->setVisible(false);
    ui->pushButton_12->setVisible(false);ui->pushButton_13->setVisible(false);
    ui->pushButton_14->setVisible(false);ui->pushButton_15->setVisible(false);
    ui->pushButton_16->setVisible(false);ui->pushButton_18->setVisible(false);
    ui->pushButton_19->setVisible(false);ui->pushButton_20->setVisible(false);
    ui->pushButton_21->setVisible(false);ui->pushButton_22->setVisible(false);
    ui->pushButton_17->setVisible(true);ui->pushButton_3->setVisible(true);
}



void Form::on_pushButton_18_clicked()
{
    chess_n=11;
    seticon();
}

void Form::on_pushButton_19_clicked()
{
    chess_n=15;
    seticon();
}

void Form::on_pushButton_20_clicked()
{
    chess_n=19;
    seticon();
}

void Form::on_pushButton_21_clicked()
{
    chess_n=23;
    seticon();
}

void Form::on_pushButton_11_clicked()
{
    value_jinshou=1;
    seticon();
}

void Form::on_pushButton_10_clicked()
{
    value_jinshou=0;
    seticon();
}



void Form::on_pushButton_12_clicked()
{
    sanshoujiaohuan=1;
    wushouliangda=1;
    seticon();
}

void Form::on_pushButton_13_clicked()
{
    sanshoujiaohuan=0;
    wushouliangda=0;
    seticon();
}

void Form::on_pushButton_8_clicked()
{
    ikun=1;
    seticon();
}

void Form::on_pushButton_9_clicked()
{
    ikun=0;
    seticon();
}

void Form::on_pushButton_7_clicked()
{
    QString strTip = "仅黑棋有禁手限制：\n\n长连禁手：不允许在棋盘上形成长连（六个或更多黑色棋子相连的形状）\n\n双三禁手：不允许在棋盘上形成两个或更多的活三\n\n四四禁手：不允许在棋盘上形成两个或更多的四四形状";

    QMessageBox::information(this, "禁手", strTip, QMessageBox::Yes);
}

void Form::on_pushButton_4_clicked()
{
    QString strTip="三手交换 ：第三步之后白方选择是否与黑方交换\n\n五手两打 :第五步之后黑方在两处落子，白方选择一处留下";
    QMessageBox::information(this, "黑棋弱化", strTip, QMessageBox::Yes);
}

void Form::on_pushButton_14_clicked()
{
    QString strTip="打开有惊喜哟";
    QMessageBox::information(this, "特殊模式", strTip, QMessageBox::Yes);
}

void Form::on_pushButton_16_clicked()
{
    yin=1;
    seticon();
}

void Form::on_pushButton_15_clicked()
{
    yin=0;
    seticon();
}
