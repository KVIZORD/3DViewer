#ifndef _3DVIEWER_VIEW_INCLUDE_MAINWINDOW_H_
#define _3DVIEWER_VIEW_INCLUDE_MAINWINDOW_H_

#include <QColorDialog>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <cmath>

#include "controller/controller.h"
#include "lib/gif/gif.h"
#include "model/gifgenerator.h"
#include "view/scenedrawer.h"
#include "view/sceneparameters.h"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller &, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  struct VectorCoordinates {
    float x{};
    float y{};
    float z{};
  };

  struct ScreenParameters {
    QString dir_path = QDir("./").absolutePath();
  };

  struct GifParameters {
    QString gif_dir{QDir("./").absolutePath()};
    QString gif_file_path{};
    int gif_before_time{5000};
    int gif_before_time_left{};
    int gif_width{640};
    int gif_height{480};
    int gif_fps{10};
    int gif_duration{5000};
  };

 private slots:
  void SlotRenderScene();
  void SlotSelectFile();

  void SlotChangeTypeProjection(int);
  void SlotChangeBackground();
  void SlotChangeEdgeType(int);
  void SlotChangeEdgeColor();
  void SlotChangeEdgeWidth(int);
  void SlotChangeVertexType(int);
  void SlotChangeVertexSize(int);
  void SlotChangeVertexColor();
  void SlotMoveObjectX(int);
  void SlotMoveObjectY(int);
  void SlotMoveObjectZ(int);
  void SlotRotateObjectX(int);
  void SlotRotateObjectY(int);
  void SlotRotateObjectZ(int);
  void SlotScaleObjectXYZ(int);

  void SlotSelectGifPath();
  void SlotSelectScreenPath();
  void SlotMakeGif();
  void SlotPrintScreenBMP();
  void SlotPrintScreenJPEG();

  void wheelEvent(QWheelEvent *);
  void PreparationMakingGif();
  void StartMakingGif();
  void MakeScreenshot(QString);
  void CreateFrameToGif();
  void ShowMessage(QString msg = "", QColor color = QColor(Qt::black),
                   int message_timeout = 0);

 private:
  void InitSettings();
  void InitSceneDraw();
  void InitSceneParameters();
  void Notify();

 private:
  Controller &controller_;
  Ui::MainWindow *ui_;
  SceneParameters scene_params_;
  ScreenParameters screen_params_;
  GifParameters gif_params_;
  QString file_path_;

  VectorCoordinates previous_offsets_{};
  VectorCoordinates previous_rotation_{};
  VectorCoordinates previous_scales_{100, 100, 100};
};

}  // namespace s21

#endif  // _3DVIEWER_VIEW_INCLUDE_MAINWINDOW_H_
