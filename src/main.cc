
#include <QApplication>
#include <QDir>
#include <iostream>

#include "controller/controller.h"
#include "model/objreader.h"
#include "model/objreaderfast2.h"
#include "model/scene.h"
#include "view/mainwindow.h"
#include "view/scenedrawer.h"

const QString kSettingsFileName = QString("settings.conf");

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QString settings_path =
      QDir::currentPath() + QString("/") + kSettingsFileName;

  s21::MySettings settings(settings_path, QSettings::IniFormat);
  s21::SceneDrawer scene_drawer;
  s21::OBJReaderFast2 reader;

  s21::Controller controller(reader, scene_drawer, settings);

  s21::MainWindow window(controller);

  window.show();
  return app.exec();
}
