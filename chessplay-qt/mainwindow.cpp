#include "Headers/mainwindow.h"

#include "Headers/form.h"
#include "Headers/quanju.h"
#include "ui_mainwindow.h"
#include <QFont>
#include <QMediaPlayer>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QtDebug>
#include <fstream>
#include <string>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowTitle("ChessPlay！");
    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/resource/beijing.mp3"));

    connect(player, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState) {
            player->setPosition(0);
            player->play();
        }
    });
    connect(player, &QMediaPlayer::mediaStatusChanged,
        [=](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::EndOfMedia) {
                player->setPosition(0);
                player->play();
            }
        });
    player->play();
    setBackground();
    if(ikun==0)
    winplayer->setMedia(QUrl("qrc:/new/prefix1/resource/over.mp3"));
    else winplayer->setMedia(QUrl("qrc:/resource/niganma.mp3"));

    ui->setupUi(this);
    resize(1200, 900);
    ui->pushButton_2->setVisible(false);
    ui->lable->setEnabled(false);
    ui->next->setVisible(false);
    ui->before->setVisible(false);
    ui->fupan->setVisible(false);
    ui->aiwrite->setVisible(false);
    ui->aiblack->setVisible(false);
    ui->lable->setAlignment(Qt::AlignCenter);
    ui->lable->setFont(QFont("黑体"));
    ui->lable->setStyleSheet("background-color:rgb(	230,230,250);color:rgb(255,20,147);");
    ui->lable->setFont(QFont("黑体"));
    ui->exit->setFont(QFont("黑体"));
    ui->fupan->setFont(QFont("黑体"));
    ui->huiqi->setFont(QFont("黑体"));
    ui->next->setFont(QFont("黑体"));
    ui->before->setFont(QFont("黑体"));
    ui->tishi->setFont(QFont("黑体"));

    ui->lable->setText("　⁣⁣⁣⁣　游戏中⁣⁣⁣⁣⁣⁣⁣⁣　　");
    ui->AI->setVisible(false);
    ui->shuangren->setVisible(false);
    ui->huiqi->setVisible(true);
    ui->tishi->setVisible(true);
    ui->exit->setVisible(true);
    op = '1'; // 初始化落子颜色

    ui->actionkai->setCheckable(true);
    ui->actionguan->setCheckable(true);
    ui->action11_11->setCheckable(true);
    ui->action15_15->setCheckable(true);
    ui->action19_19->setCheckable(true);
    ui->action23_23->setCheckable(true);
    ui->action_wushou_fou->setCheckable(true);
    ui->action_wushou_shi->setCheckable(true);
    ui->action_sanshou_fou->setCheckable(true);
    ui->action_sanshou_shi->setCheckable(true);
    ui->jinshou_fou->setCheckable(true);
    ui->jinshou_shi->setCheckable(true);

    check();

    ui->shuangren->setStyleSheet("border-image: url(:/new/prefix1/resource/shuangren.png);");
    ui->fupan->setStyleSheet("border-image: url(:/new/prefix1/resource/fupan.png);");
    ui->tishi->setStyleSheet("border-image: url(:/new/prefix1/resource/tishi.png);");
    ui->next->setStyleSheet("border-image: url(:/new/prefix1/resource/xiayibu.png);");
    ui->before->setStyleSheet("border-image: url(:/new/prefix1/resource/shangyibu.png);");
    ui->huiqi->setStyleSheet("border-image: url(:/new/prefix1/resource/hui.png);");
    ui->pushButton_2->setStyleSheet("border-image: url(:/new/prefix1/resource/kong.png);");
    ui->exit->setStyleSheet("border-image: url(:/new/prefix1/resource/renshu.png);");
    ui->pushButton->setStyleSheet("border-image: url(:/new/prefix1/resource/zhujiemina.png);");
    ui->AI->setStyleSheet("border-image: url(:/new/prefix1/resource/ai.png);");

    ui->aiwrite->setStyleSheet("border-image: url(:/new/prefix1/resource/bai.png);");
    ui->aiblack->setStyleSheet("border-image: url(:/new/prefix1/resource/hei.png);");



}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setBackground()
{
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/new/prefix1/resource/background2.png");
    QImage fitimgpic = ImgAllbackground.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    this->setBackground();
}

void MainWindow::DrawChessBroad()
{

    ui->lable->setFont(QFont("黑体", min(this->width(), this->height()) / 70));
    ui->exit->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->fupan->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->huiqi->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->next->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->before->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    ui->tishi->setFont(QFont("黑体", min(this->width(), this->height()) / 50));
    int a, b;
    a = (this->width() * 2 / 3) / chess_n;
    b = (this->height() * 15 / 16) / chess_n;
    a = min(a, b);

    QPainter painter(this);
    QRect rect(a / 2 - 20, a * 3 / 2 - 20, (chess_n - 1) * a + 40, (chess_n - 1) * a + 40);
    QPen pent;
    pent.setColor(QColor(150, 120, 100));
    pent.setWidth(a / 5);
    painter.setPen(pent);
    // 绘制红十字

    QPolygon polygon;
    polygon << QPoint(a / 2 - 20, a * 3 / 2 - 20)
            << QPoint(a / 2 - 20, a * (chess_n - 1) + a * 3 / 2 + 20)
            << QPoint(a / 2 + (chess_n - 1) * a + 20, a * (chess_n - 1) + a * 3 / 2 + 20)
            << QPoint(a / 2 + (chess_n - 1) * a + 20, a * 3 / 2 - 20);
    painter.setBrush(QColor(226, 201, 177));
    painter.drawPolygon(polygon);
    // 填充矩形区域
    painter.fillRect(rect, QColor(226, 201, 177));

    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    for (int j = 0; j < chess_n - 1; j++) {
        for (int i = 0; i < chess_n - 1; i++) {
            // 我们使用drawRect(int x, int y, int width, int
            // height)来绘制一个矩形（棋盘格子）
            // 前两个参数代表矩形的左上顶点，后两个参数代表矩形的宽高
            painter.drawRect((i + 0.5) * a, (j + 1.5) * a, a, a);
        }
    }
    QBrush brush = QColor(0, 0, 0, 0);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    for (int j = 0; j < chess_n - 1; j++) {
        for (int i = 0; i < chess_n - 1; i++) {
            if ((i == chess_n / 2 && j == chess_n / 2)
                || (i == chess_n / 4 && j == chess_n / 4)
                || (i == chess_n - chess_n / 4 - 1 && j == chess_n - chess_n / 4 - 1)
                || (i == chess_n / 4 && j == chess_n - chess_n / 4 - 1)
                || (i == chess_n - chess_n / 4 - 1 && j == chess_n / 4)) {
                painter.drawEllipse((i + 0.5) * a - (a / 4) / 2,
                    (j + 1.5) * a - (a / 4) / 2, a / 4, a / 4);
            }
        }
    }

    // 创建一个矩形，表示四条线框住的区域
}

void MainWindow::DrawItems()
{
    int a, b;
    a = (this->width() * 2 / 3) / chess_n;
    b = (this->height() * 15 / 16) / chess_n;
    a = min(a, b);

    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::black); // 设置画笔颜色为透明色
    painter.setPen(pen);
    // 循环我们的所有落子，并绘制出来

    // cout<<text1<<"hello "<<text2<<" "<<endl;
    for (int i = 0; i < items.size(); i++) {
        Item item = items[i];
        // 判断是黑方还是白方落子
        if (item.opr == '1') {
            if (ikun == 0) {
                QPixmap pixmap(":/new/prefix1/resource/hei.png");
                painter.drawPixmap(item.p.x() * a + a / 20, item.p.y() * a + a + a / 20, a * 9 / 10, a * 9 / 10, pixmap);
            } else {
                QPixmap pixmap(":/resource/kun.png");
                painter.drawPixmap(item.p.x() * a + a / 20, item.p.y() * a + a + a / 20, a * 9 / 10, a * 9 / 10, pixmap);
            }
        } else {
            if (ikun == 0) {
                QPixmap pixmap(":/new/prefix1/resource/bai.png");
                painter.drawPixmap(item.p.x() * a + a / 20, item.p.y() * a + a + a / 20, a * 9 / 10, a * 9 / 10, pixmap);
            } else {
                QPixmap pixmap(":/resource/lanqiu.png");
                painter.drawPixmap(item.p.x() * a + a / 20, item.p.y() * a + a + a / 20, a * 9 / 10, a * 9 / 10, pixmap);
            }

            // 获取棋子的位置
            QPoint ptCenter((item.p.x() + 0.5) * a, (item.p.y() + 1.5) * a);
            // 绘制棋子

            if (i == items.size() - 1) {
                pen.setColor(Qt::red);
                pen.setWidth(a / 40);
                painter.setPen(pen);
                // 绘制红十字
                painter.drawLine(ptCenter.x() - a / 6, ptCenter.y(), ptCenter.x() + a / 6, ptCenter.y());
                painter.drawLine(ptCenter.x(), ptCenter.y() - a / 6, ptCenter.x(), ptCenter.y() + a / 6);
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int a, b;
    a = (this->width() * 2 / 3) / chess_n;
    b = (this->height() * 15 / 16) / chess_n;
    a = min(a, b);

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    QBrush brush;
    brush.setColor(Qt::red);
    QPoint ptCenter(text1, text2);
    painter.drawEllipse(ptCenter, a / 2, a / 2);
    if (aiop == '0' || aiop == '4')
        return;
    else if (aiop == '1')
        op = '2';
    else if (aiop == '2')
        op = '1';
    QPoint pt; // 定义一个点
    int chess_x = event->pos().x(); // 获取鼠标点击的x坐标
    int chess_y = event->pos().y() - a; // 获取鼠标点击的y坐标
    if (chess_x / a >= chess_n || chess_y / a >= chess_n) {
        return;
    }
    pt.setX(chess_x / a); // 设置棋子x坐标
    pt.setY(chess_y / a); // 设置棋子y坐标

    if (wushou_flag == 0 && num_step == 6 && aiop == '3' && wushouliangda == 1) {
        if (pt == items[items.size() - 1].p) {
            items.pop_back();
            num_step = 5;
            wushou_flag = 1;
        } else if (pt == items[items.size() - 2].p) {
            items[items.size() - 2] = items[items.size() - 1];
            items.pop_back();
            num_step = 5;
            wushou_flag = 1;
        }
        return;
    } else {
        // 循环所有棋子判断落子处是否存在棋子
        for (int i = 0; i < items.size(); i++) {
            Item item = items[i];
            if (item.p == pt) {
                return;
            }
        }
    }

    if (aiop == '3') {
        text1 = chess_x / a;
        text2 = chess_y / a;
    }
    Item item(pt, op); // 设定棋子坐标及颜色
    items.append(item); // 添加棋子到所有的棋子Q
    for (int i = 0; i < items.size(); i++) {
        chess[items[i].p.y()][items[i].p.x()] = items[i].opr;
    }

    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            cout << chess[i][j] << " ";
            chess_jin[i][j] = chess[i][j];
        }
        cout << endl;
    }

    QString strTip;
    num_step++;
    if (sanshoujiaohuan == 1 && num_step == 3 && aiop == '3') {
        strTip = "白方选择是否与黑方交换";
        QMessageBox::information(this, "三手交换", strTip, QMessageBox::Yes,
            QMessageBox::No);
    }

    int chess_flag;
    if (value_jinshou == 1 && op == '1')
        chess_flag = jinshou(pt.y(), pt.x());
    else
        chess_flag = 0;
    int win = chesswin(op, pt.y(), pt.x(), chess_flag);
    if (win == 1) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);
        strTip = "黑棋胜利！";
        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // flagai=0;
        // ui->lable_3->setText("black winner !!!\n\n");
    } else if (win == 2 || win == 4 || win == 5 || win == 6) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);

        if (win == 2)
            strTip = "白棋胜利！";
        else if (win == 4)
            strTip = "白棋胜利！黑方触犯长连禁手";
        else if (win == 5)
            strTip = "白棋胜利！黑方触犯四四禁手";
        else if (win == 6)
            strTip = "白棋胜利！黑方触犯三三禁手";
        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // ui->lable_3->setText("white winner !!!\n\n");
    } else if (win == 3) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);
        strTip = "平局！";
        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // flagai=0;
        // ui->lable_3->setText("black winner !!!\n\n");
    }
    DrawItems();
    if (aiop == '2' || aiop == '1')
        luoziAI(aiop);
    else {
        if (num_step == 5 && aiop == '3' && wushouliangda == 1) {
            op = '1';
        } else {
            if (op == '2')
                op = '1'; // 切换棋子颜色
            else
                op = '2';
        }
    }

    if (num_step == 4 && aiop == '3' && wushouliangda == 1) {
        strTip = "黑方在两处落子白方选择一处留下";
        QMessageBox::information(this, "五手两打", strTip, QMessageBox::Yes,
            QMessageBox::No);
    }
}

void MainWindow::paintEvent(QPaintEvent*)
{
    DrawChessBroad();
    // 绘制棋子
    DrawItems();
    // 更新
    update();
}

void MainWindow::on_exit_clicked()
{
    winplayer->play();
    for (int i = 0; i < items.count(); i++) {
        xitems.append(items[i]);
    }
    ui->huiqi->setVisible(false);
    ui->fupan->setVisible(true);
    ui->huiqi->setVisible(false);
    ui->tishi->setVisible(false);
    ui->lable->setText("请选择游戏模式");
    items.clear();
    initchess();
    aiop = '4';
    ui->pushButton_2->setVisible(true);
    ui->exit->setVisible(false);
}

void MainWindow::on_fupan_clicked()
{
    if (xitems.count() == 0) {
        emit on_pushButton_2_clicked();
        return;
    }
    ui->fupan->setVisible(false);
    ui->next->setVisible(true);
    ui->before->setVisible(true);
    ui->pushButton_2->setVisible(true);
    fupan++;
    if (fupan == xitems.size()) {
        fupan -= xitems.size();
        items.clear();
    }
    items.append(xitems[fupan]);
    QString a = " 复盘：第 ";
    QString b = QString::number(fupan + 1);
    QString c = " 步";
    QString d = a + b + c;
    ui->lable->setText(d);
}

void MainWindow::on_next_clicked()
{
    if (xitems.count() == 0)
        return;
    cout << fupan;
    fupan++;
    if (fupan >= xitems.count()) {
        fupan -= xitems.count();
        items.clear();
    }
    items.append(xitems[fupan]);
    QString a = " 复盘：第 ";
    QString b = QString::number(fupan + 1);
    QString c = " 步";
    QString d = a + b + c;
    ui->lable->setText(d);
}

void MainWindow::on_before_clicked()
{
    if (xitems.count() == 0)
        return;
    items.remove(fupan);
    fupan--;
    if (fupan == -1) {
        fupan += xitems.count();
        for (int i = 0; i < xitems.count(); i++) {
            items.append(xitems[i]);
        }
    }
    QString a = " 复盘：第 ";
    QString b = QString::number(fupan + 1);
    QString c = " 步";
    QString d = a + b + c;
    ui->lable->setText(d);
}

void MainWindow::on_huiqi_clicked()
{
    if (items.size() > 2) {
        chess[items.back().p.y()][items.back().p.x()] = '0';
        items.pop_back();
        chess[items.back().p.y()][items.back().p.x()] = '0';
        items.pop_back();
        num_step -= 2;
        if (num_step <= 4)
            wushou_flag = 0;
    }
}

void MainWindow::on_tishi_clicked()
{
    num_step++;
    if (aiop == '2' || aiop == '1') {
        if (aiop == '2') {
            luoziAI('1');
            if (items.count() > 0)
                luoziAI('2');
        }
        if (aiop == '1') {
            luoziAI('2');
            if (items.count() > 0)
                luoziAI('1');
        }
    } else {
        if (op == '1') {
            luoziAI('1');
            op = '2';
        } else {
            luoziAI('2');
            op = '1';
        }
    }
}

void MainWindow::on_jinshou_shi_triggered()
{
    value_jinshou = 1;
    check();
}

void MainWindow::on_jinshou_fou_triggered()
{
    value_jinshou = 0;
    check();
}

void MainWindow::on_actionkai_triggered()
{
    yin=1;
    check();
}

void MainWindow::on_actionguan_triggered()
{
    yin=0;
    check();
}

void MainWindow::on_action11_11_triggered()
{
    if(aiop=='4')
    chess_n = 11;
    check();
}

void MainWindow::on_action15_15_triggered()
{
    if(aiop=='4')
    chess_n = 15;
    check();
}

void MainWindow::on_action19_19_triggered()
{
    if(aiop=='4')
    chess_n = 19;
    check();
}

void MainWindow::on_action23_23_triggered()
{
    if(aiop=='4')
    chess_n = 23;
    check();
}

void MainWindow::on_action_sanshou_shi_triggered()
{
    sanshoujiaohuan = 1;
    check();
}

void MainWindow::on_action_sanshou_fou_triggered()
{
    sanshoujiaohuan = 0;
    check();
}

void MainWindow::on_action_wushou_shi_triggered()
{
    wushouliangda = 1;
    check();
}

void MainWindow::on_action_wushou_fou_triggered()
{
    wushouliangda = 0;
    check();
}

void MainWindow::on_pushButton_clicked()
{
    player->stop();
    delete player;
    this->close();
    Form* f = new Form();
    f->setSizeIncrement(this->width(), this->height());
    f->show();
}

void MainWindow::on_AI_clicked()
{
    ui->AI->setVisible(false);
    ui->shuangren->setVisible(false);
    ui->aiblack->setVisible(true);
    ui->aiwrite->setVisible(true);
}

void MainWindow::on_shuangren_clicked()
{
    ui->lable->setText("⁣⁣⁣⁣　⁣⁣⁣⁣　游戏中⁣⁣⁣⁣⁣⁣⁣⁣　　");
    ui->AI->setVisible(false);
    ui->shuangren->setVisible(false);
    ui->aiblack->setVisible(false);
    ui->aiwrite->setVisible(false);
    ui->huiqi->setVisible(true);
    ui->tishi->setVisible(true);
    ui->exit->setVisible(true);
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
}

void MainWindow::on_aiblack_clicked()
{
    ui->lable->setText("　⁣⁣⁣⁣　游戏中⁣⁣⁣⁣⁣⁣⁣⁣　　");
    ui->AI->setVisible(false);
    ui->shuangren->setVisible(false);
    ui->aiblack->setVisible(false);
    ui->aiwrite->setVisible(false);
    ui->huiqi->setVisible(true);
    ui->tishi->setVisible(true);
    ui->exit->setVisible(true);
    fupan = -1;
    aiop = '2';
    items.clear();
    xitems.clear();
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }
}

void MainWindow::on_aiwrite_clicked()
{
    ui->lable->setText("　⁣⁣⁣⁣　游戏中⁣⁣⁣⁣⁣⁣⁣⁣　　");
    ui->AI->setVisible(false);
    ui->shuangren->setVisible(false);
    ui->aiblack->setVisible(false);
    ui->aiwrite->setVisible(false);
    ui->huiqi->setVisible(true);
    ui->tishi->setVisible(true);
    ui->exit->setVisible(true);
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
}

void MainWindow::on_pushButton_2_clicked()
{
    aiop = '0';
    ui->AI->setVisible(true);
    ui->lable->setText("请选择游戏模式");
    ui->shuangren->setVisible(true);
    ui->aiblack->setVisible(false);
    ui->aiwrite->setVisible(false);
    ui->fupan->setVisible(false);
    ui->next->setVisible(false);
    ui->before->setVisible(false);
    ui->pushButton_2->setVisible(false);
    items.clear();
    xitems.clear();
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }
}

void MainWindow::on_actionA_triggered()
{
    ikun++;
    ikun %= 2;
    if(ikun==0)
    winplayer->setMedia(QUrl("qrc:/new/prefix1/resource/over.mp3"));
    else winplayer->setMedia(QUrl("qrc:/resource/niganma.mp3"));
}

void MainWindow::check(){
    ui->jinshou_shi->setChecked(false);
    ui->jinshou_fou->setChecked(false);
    ui->action_wushou_fou->setChecked(false);
    ui->action_wushou_shi->setChecked(false);
    ui->actionkai->setChecked(false);
    ui->actionguan->setChecked(false);
    ui->action11_11->setChecked(false);
    ui->action15_15->setChecked(false);
    ui->action19_19->setChecked(false);
    ui->action23_23->setChecked(false);
    ui->action_sanshou_fou->setChecked(false);
    ui->action_sanshou_shi->setChecked(false);
    if(chess_n==11){ui->action11_11->setChecked(true);ui->menu_7->setTitle("棋盘大小 ：11 * 11");}
    else if(chess_n==15){ui->action15_15->setChecked(true);ui->menu_7->setTitle("棋盘大小 ：15 * 15");}
    else if(chess_n==19){ui->action19_19->setChecked(true);ui->menu_7->setTitle("棋盘大小 ：19 * 19");}
    else if(chess_n==23){ui->action23_23->setChecked(true);ui->menu_7->setTitle("棋盘大小 ：23 * 23");}

    if(value_jinshou==0){ui->jinshou_fou->setChecked(true);ui->menu_9->setTitle("禁手 ：fou");}
    else {ui->jinshou_shi->setChecked(true);ui->menu_9->setTitle("禁手 ：是");}

    if(sanshoujiaohuan==0){ui->action_sanshou_fou->setChecked(true);ui->menu_10->setTitle("三手交换 ：否");}
    else {ui->action_sanshou_shi->setChecked(true);ui->menu_10->setTitle("三手交换 ：是");}

    if(wushouliangda==0){ui->action_wushou_fou->setChecked(true);ui->menu_11->setTitle("五手两打 ：否");}
    else {ui->action_wushou_shi->setChecked(true);ui->menu_11->setTitle("五手两打 ：是");}

    if(yin==0){ui->actionguan->setChecked(true);ui->menu_8->setTitle("音量 ：关");player->setVolume(0);}
    else {ui->actionkai->setChecked(true);ui->menu_8->setTitle("音量 ：开");player->setVolume(100);}
}
