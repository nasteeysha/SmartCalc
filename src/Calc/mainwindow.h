#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern "C" {
#include "../polish.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void s21_equal_clicked();
    void s21_draw_graph(const char* str);
    void s21_null_fields();
    void s21_count_clicked();
};

#endif // MAINWINDOW_H
