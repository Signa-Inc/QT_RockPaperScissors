#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слоты для кнопок
    void onRockClicked();
    void onPaperClicked();
    void onScissorsClicked();

private:
    Ui::MainWindow *ui;

    // Наши элементы интерфейса
    QLabel *win_lbl;
    QLabel *player_lbl;
    QLabel *VS_lbl;
    QLabel *enemy_lbl;

    QPushButton *rock_btn;
    QPushButton *paper_btn;
    QPushButton *scissors_btn;

    void playGame(int playerChoice);
};
#endif // MAINWINDOW_H
