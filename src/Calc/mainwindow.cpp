#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->EqualButton, SIGNAL(clicked()), this,
              SLOT(s21_equal_clicked()));
    connect(ui->count, SIGNAL(clicked()), this,
              SLOT(s21_count_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::s21_equal_clicked() {
  QString text = ui->expression->text();
  std::string str2 = text.toStdString();
  const char* str = str2.c_str();
  int error = 0;

  if (ui->expression->text().contains("x")){
    s21_null_fields();
    s21_draw_graph(str);
  }
  else {
    double result = parse_str(str, &error, 0);
    if(!error){
        QString strResult = QString::number(result);
        ui->Result_label->setText(strResult);
    }
    else
        ui->Result_label->setText("ERROR");
  }
}

void MainWindow::s21_null_fields(){
    if (ui->ValueX->displayText().isEmpty())
        ui->ValueX->setText("5");
    if (ui->MinX->displayText().isEmpty())
        ui->MinX->setText("0");
    if (ui->MinY->displayText().isEmpty())
        ui->MinY->setText("0");
    if (ui->MaxX->displayText().isEmpty())
        ui->MaxX->setText("10");
    if (ui->MaxY->displayText().isEmpty())
        ui->MaxY->setText("10");
    if (ui->step->displayText().isEmpty())
        ui->step->setText("0.00001");
}

void MainWindow::s21_draw_graph(const char* str) {
    double a = ui->MinX->text().toDouble(); //Начало интервала, где рисуем график по оси Ox
    double b = ui->MaxX->text().toDouble(); //Конец интервала, где рисуем график по оси Ox
    double y1 = ui->MinY->text().toDouble();
    double y2 = ui->MaxY->text().toDouble();
    int error = 0;
    double h = ui->step->text().toDouble(); //Шаг, с которым будем пробегать по оси Ox
    if(a < b){
    int N = (b - a) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); //Массивы координат точек

    //Вычисляем наши данные
    int i=0;
    //Пробегаем по всем точкам
    for (double X = a; X <= b && !error; X += h) {
      x[i] = X;
      y[i] = parse_str(str, &error, X);//Формула нашей функции
      if(!(isinf(y[i]) && isnan(y[i])))
        i++;
    }
    ui->graphX->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->graphX->addGraph();

    if(!error)
        ui->graphX->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->graphX->xAxis->setLabel("x");
    ui->graphX->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    ui->graphX->xAxis->setRange(a, b);//Для оси Ox
    ui->graphX->yAxis->setRange(y1, y2);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->graphX->replot();
    }
    else
            ui->Result_label->setText("ERROR");
    error = 0;
    double res = parse_str(str, &error, ui->ValueX->text().toDouble());
    if(!error){
        QString strResult = QString::number(res);
        ui->Result_label->setText(strResult);
     }
    else
        ui->Result_label->setText("ERROR");
}

void MainWindow::s21_count_clicked() {
    if(ui->Summ->displayText().isEmpty() || ui->Date->displayText().isEmpty() || ui->Procent->displayText().isEmpty()){
        ui->pereplata->setText("ERROR");
        ui->All_money->setText("ERROR");
        ui->Monthplate->setText("ERROR");
    }
    else{
        double sum = ui->Summ->text().toDouble();
        double procent = ui->Procent->text().toDouble() / 100 / 12;
        double srok = ui->Date->text().toDouble();
        if(ui->year->currentIndex() == 0)
            srok = srok * 12;
        char str[255] = "";
        if(ui->type->currentIndex() == 0){
            std::sprintf(str, "%f*(%f*(1+%f)^%f)/((1+%f)^%f-1)", sum, procent, procent, srok, procent, srok);
            int error = 0;
            double month = parse_str(str, &error, 0);
            if(!error){
                QString strResult = QString::number(month);
                ui->Monthplate->setText(strResult);
                double all = month * srok;
                double pereplata = all - sum;
                QString strResult2 = QString::number(all);
                ui->All_money->setText(strResult2);
                QString strResult3 = QString::number(pereplata);
                ui->pereplata->setText(strResult3);
            }
        }
        else{
            double plat[(int)srok];
            double copy_sum = sum;
            double new_sum = 0, min = sum, max = 0;
            for(int i = 0; i < (int)srok; i++){
                plat[i] = sum * procent + copy_sum/srok;
                sum = sum - copy_sum/srok;
                if(plat[i] > max)
                        max = plat[i];
                if(plat[i] < min)
                        min = plat[i];
                new_sum = new_sum + plat[i];
            }
            double pereplata = new_sum - copy_sum;
            std::sprintf(str, "%.2f", new_sum);
            QString strResult2 = QString::fromStdString(str);
            ui->All_money->setText(strResult2);
            std::sprintf(str, "%.2f", pereplata);
            QString strResult3 = QString::fromStdString(str);
            ui->pereplata->setText(strResult3);
            std::sprintf(str, "%.2f..%.2f", min, max);
            QString strResult = QString::fromStdString(str);
            ui->Monthplate->setText(strResult);
        }
    }
}

