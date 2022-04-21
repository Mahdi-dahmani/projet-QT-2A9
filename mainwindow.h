#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <evenement.h>
#include <avis.h>
#include <arduino.h>

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
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_excel_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_9_clicked();



    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();
    void update_label();

    void on_pushButton_8_pressed();

    void on_pushButton_8_released();

    void on_pushButton_13_pressed();

    void on_pushButton_13_released();

    void on_pushButton_12_pressed();

    void on_pushButton_12_released();

    void on_pushButton_14_pressed();

    void on_pushButton_14_released();

private:
    Ui::MainWindow *ui;
     EVENEMENT Event;
     avis A;
     Arduino ar;
     QByteArray data;

};
#endif // MAINWINDOW_H
