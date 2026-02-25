#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "item.h"
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPainter>
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QMediaPlayer* player;
    QMediaPlayer* winplayer = new QMediaPlayer;
    void DrawChessBroad();
    void DrawItems();
    const int size = 20;
    //    QVector<Item> items;
    //    QVector<Item> xitems;
    //    char op;
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void chessop1();
    int luozi(char op);
    static int chesswin(char chess_flag, int chess_i, int chess_j, int flag_jinshou);
    int luoziAI(char op);
    QLabel* m_imageLabel;

private slots:
    // void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_aiwrite_clicked();

    void on_exit_clicked();

    void on_aiblack_clicked();


    void on_fupan_clicked();

    void on_next_clicked();

    void on_before_clicked();

    void on_huiqi_clicked();

    void on_AI_clicked();

    void on_tishi_clicked();

    void on_jinshou_shi_triggered();

    void on_jinshou_fou_triggered();

    void on_actionkai_triggered();

    void on_actionguan_triggered();

    void on_action11_11_triggered();

    void on_action15_15_triggered();

    void on_action23_23_triggered();

    void on_action19_19_triggered();

    void on_action_sanshou_shi_triggered();

    void on_action_sanshou_fou_triggered();

    void on_action_wushou_shi_triggered();

    void on_action_wushou_fou_triggered();

    void resizeEvent(QResizeEvent* event);

    void setBackground();

    void on_pushButton_clicked();

    void on_shuangren_clicked();

    void on_pushButton_2_clicked();

    void on_actionA_triggered();

    void check();

private:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
