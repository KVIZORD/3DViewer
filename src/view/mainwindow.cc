#include "include/mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

SceneDrawer *MainWindow::GetOpenglWidget() {
  return ui->widgetOpenGL;
  //        return ui->centralwidget;
}
} // namespace s21
