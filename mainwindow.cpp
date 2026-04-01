#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QPixmap> // ОБЯЗАТЕЛЬНО ДОБАВИТЬ ЭТУ СТРОЧКУ!

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400, 380); // Немного увеличим высоту окна

    // --- Элементы UI (почти как раньше) ---

    win_lbl = new QLabel("Кто победит?", this);
    win_lbl->setGeometry(0, 20, 400, 40);
    win_lbl->setAlignment(Qt::AlignCenter);
    win_lbl->setStyleSheet("font-size: 20px; font-weight: bold;");

    // Выбор Игрока (ЛЕВО)
    player_lbl = new QLabel(this); // Текст пока убираем
    player_lbl->setGeometry(30, 100, 120, 120); // Делаем квадратным под картинку
    player_lbl->setAlignment(Qt::AlignCenter);
    // Добавим легкую рамку, чтобы было видно зону
    player_lbl->setStyleSheet("border: 2px solid #ccc; background: #f9f9f9;");

    VS_lbl = new QLabel("VS", this);
    VS_lbl->setGeometry(150, 100, 100, 120);
    VS_lbl->setAlignment(Qt::AlignCenter);
    VS_lbl->setStyleSheet("font-size: 30px; font-weight: bold; color: #555;");

    // Выбор Компьютера (ПРАВО)
    enemy_lbl = new QLabel(this);
    enemy_lbl->setGeometry(250, 100, 120, 120);
    enemy_lbl->setAlignment(Qt::AlignCenter);
    enemy_lbl->setStyleSheet("border: 2px solid #ccc; background: #f9f9f9;");

    rock_btn = new QPushButton("Камень", this);
    rock_btn->setGeometry(30, 260, 100, 40); // Сместили вниз

    paper_btn = new QPushButton("Бумага", this);
    paper_btn->setGeometry(150, 260, 100, 40);

    scissors_btn = new QPushButton("Ножницы", this);
    scissors_btn->setGeometry(270, 260, 100, 40);

    connect(rock_btn, &QPushButton::clicked, this, &MainWindow::onRockClicked);
    connect(paper_btn, &QPushButton::clicked, this, &MainWindow::onPaperClicked);
    connect(scissors_btn, &QPushButton::clicked, this, &MainWindow::onScissorsClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRockClicked() { playGame(0); }
void MainWindow::onPaperClicked() { playGame(1); }
void MainWindow::onScissorsClicked() { playGame(2); }

// *** НОВАЯ ЛОГИКА С КАРТИНКАМИ ***
void MainWindow::playGame(int playerChoice) {
    // 1. Создаем массив путей к картинкам
    QString imagePaths[] = {":/new/prefix1/Stone.png", ":/new/prefix1/Paper.png", ":/new/prefix1/Scissors.png"};

    // Рандом компьютера
    int computerChoice = QRandomGenerator::global()->bounded(3);

    // 2. Загружаем и устанавливаем картинки
    // Функция .scaled() подгоняет размер картинки под размер лейбла, сохраняя пропорции
    QPixmap playerPix(imagePaths[playerChoice]);
    player_lbl->setPixmap(playerPix.scaled(player_lbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap compPix(imagePaths[computerChoice]);
    enemy_lbl->setPixmap(compPix.scaled(enemy_lbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    // 3. Проверка результата (логика осталась прежней, поменяли только текст)
    if (playerChoice == computerChoice) {
        win_lbl->setText("НИЧЬЯ!");
        win_lbl->setStyleSheet("color: orange; font-size: 20px; font-weight: bold;");
    } else if ((playerChoice == 0 && computerChoice == 2) || // Камень -> Ножницы
               (playerChoice == 1 && computerChoice == 0) || // Бумага -> Камень
               (playerChoice == 2 && computerChoice == 1)) { // Ножницы -> Бумага
        win_lbl->setText("ВЫ ПОБЕДИЛИ!");
        win_lbl->setStyleSheet("color: green; font-size: 20px; font-weight: bold;");
    } else {
        win_lbl->setText("ПК ПОБЕДИЛ!");
        win_lbl->setStyleSheet("color: red; font-size: 20px; font-weight: bold;");
    }
}
