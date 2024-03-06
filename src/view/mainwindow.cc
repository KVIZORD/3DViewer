#include "view/mainwindow.h"

#include "model/gifgenerator.h"
#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Controller &ctrl, QWidget *parent)
    : QMainWindow(parent),
      controller_(ctrl),
      ui_(new Ui::MainWindow),

      scene_params_(ctrl.GetSettings()) {
  ui_->setupUi(this);

  InitSettings();
  InitSceneDraw();

  ui_->screenPath->setText(screen_params_.dir_path);
  ui_->screenPath->setToolTip(screen_params_.dir_path);

  ui_->gifPath->setText(gif_params_.gif_dir);
  ui_->gifPath->setToolTip(gif_params_.gif_dir);

  connect(ui_->buttonSelectFile, SIGNAL(clicked()), this,
          SLOT(SlotSelectFile()));
  connect(ui_->buttonRenderObj, SIGNAL(clicked()), this,
          SLOT(SlotRenderScene()));

  connect(ui_->typeProjection, SIGNAL(activated(int)), this,
          SLOT(SlotChangeTypeProjection(int)));
  connect(ui_->backgroundColor, SIGNAL(clicked()), this,
          SLOT(SlotChangeBackground()));
  connect(ui_->lineType, SIGNAL(activated(int)), this,
          SLOT(SlotChangeEdgeType(int)));
  connect(ui_->lineWidth, SIGNAL(valueChanged(int)), this,
          SLOT(SlotChangeEdgeWidth(int)));
  connect(ui_->lineColor, SIGNAL(clicked()), this, SLOT(SlotChangeEdgeColor()));
  connect(ui_->vertexType, SIGNAL(activated(int)), this,
          SLOT(SlotChangeVertexType(int)));
  connect(ui_->vertexSize, SIGNAL(valueChanged(int)), this,
          SLOT(SlotChangeVertexSize(int)));
  connect(ui_->vertexColor, SIGNAL(clicked()), this,
          SLOT(SlotChangeVertexColor()));

  connect(ui_->moveX, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectX(int)));
  connect(ui_->moveY, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectY(int)));
  connect(ui_->moveZ, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectZ(int)));
  connect(ui_->sliderMoveX, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectX(int)));
  connect(ui_->sliderMoveY, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectY(int)));
  connect(ui_->sliderMoveZ, SIGNAL(valueChanged(int)), this,
          SLOT(SlotMoveObjectZ(int)));

  connect(ui_->rotateX, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectX(int)));
  connect(ui_->rotateY, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectY(int)));
  connect(ui_->rotateZ, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectZ(int)));
  connect(ui_->sliderRotateX, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectX(int)));
  connect(ui_->sliderRotateY, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectY(int)));
  connect(ui_->sliderRotateZ, SIGNAL(valueChanged(int)), this,
          SLOT(SlotRotateObjectZ(int)));

  connect(ui_->scale, SIGNAL(valueChanged(int)), this,
          SLOT(SlotScaleObjectXYZ(int)));
  connect(ui_->sliderScale, SIGNAL(valueChanged(int)), this,
          SLOT(SlotScaleObjectXYZ(int)));

  connect(ui_->screenPath, SIGNAL(clicked()), this,
          SLOT(SlotSelectScreenPath()));
  connect(ui_->buttonPreentScreenBmp, SIGNAL(clicked()), this,
          SLOT(SlotPrintScreenBMP()));
  connect(ui_->buttonPreentScreenJpeg, SIGNAL(clicked()), this,
          SLOT(SlotPrintScreenJPEG()));

  connect(ui_->gifPath, SIGNAL(clicked()), this, SLOT(SlotSelectGifPath()));
  connect(ui_->buttonCreateGif, SIGNAL(clicked()), this, SLOT(SlotMakeGif()));
}

MainWindow::~MainWindow() {
  controller_.SetParentForSceneDraw(nullptr);
  delete ui_;
}

void MainWindow::InitSettings() {
  ui_->typeProjection->setCurrentIndex(scene_params_.type_projection);
  ui_->lineType->setCurrentIndex(static_cast<int>(scene_params_.edge_type));
  ui_->vertexType->setCurrentIndex(static_cast<int>(scene_params_.vertex_type));
  ui_->lineWidth->setValue(scene_params_.edge_width);
  ui_->vertexSize->setValue(scene_params_.vertex_size);
  ui_->lineColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                    .arg(scene_params_.edge_color.red())
                                    .arg(scene_params_.edge_color.green())
                                    .arg(scene_params_.edge_color.blue()));
  ui_->backgroundColor->setStyleSheet(
      QString("background-color: rgb(%1, %2, %3)")
          .arg(scene_params_.background_color.red())
          .arg(scene_params_.background_color.green())
          .arg(scene_params_.background_color.blue()));
  ui_->vertexColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                      .arg(scene_params_.vertex_color.red())
                                      .arg(scene_params_.vertex_color.green())
                                      .arg(scene_params_.vertex_color.blue()));
}

void MainWindow::InitSceneDraw() {
  controller_.SetParentForSceneDraw(ui_->widgetOpenGL);
  controller_.SetParamsScene(&scene_params_);
}

void MainWindow::InitSceneParameters() {
  previous_offsets_ = {0, 0, 0};
  previous_rotation_ = {0, 0, 0};
  previous_scales_ = {100, 100, 100};
  ui_->sliderMoveX->setSliderPosition(0);
  ui_->moveX->setValue(0);
  ui_->sliderMoveY->setSliderPosition(0);
  ui_->moveY->setValue(0);
  ui_->sliderMoveZ->setSliderPosition(0);
  ui_->moveZ->setValue(0);
  ui_->sliderRotateX->setSliderPosition(0);
  ui_->rotateX->setValue(0);
  ui_->sliderRotateY->setSliderPosition(0);
  ui_->rotateY->setValue(0);
  ui_->sliderRotateZ->setSliderPosition(0);
  ui_->rotateZ->setValue(0);
  ui_->sliderScale->setSliderPosition(100);
  ui_->scale->setValue(100);
}

void MainWindow::Notify() {
  controller_.UpdateSceneDraw();
  controller_.UpdateSettings(scene_params_);
}

void MainWindow::SlotSelectFile() {
  file_path_ =
      QFileDialog::getOpenFileName(this, "Open File", "./", tr("*.obj"));
  QFileInfo fileinfo(file_path_);
  ui_->fileName->setText(fileinfo.fileName());
}

void MainWindow::SlotRenderScene() {
  OperationResult result = controller_.LoadScene(file_path_);
  if (!result.is_success) {
    ShowMessage(QString::fromStdString(result.error_message), QColor(Qt::red));
    return;
  }
  ui_->countVertexes->setText(QString::number(controller_.GetCountVertices()));
  ui_->countEdges->setText(QString::number(controller_.GetCountEdges()));
  InitSceneParameters();
}

void MainWindow::SlotMoveObjectX(int offset) {
  if (offset == previous_offsets_.x) {
    return;
  }
  controller_.MoveScene((offset - previous_offsets_.x), 0, 0);
  previous_offsets_.x = offset;
  ui_->sliderMoveX->setSliderPosition(offset);
  ui_->moveX->setValue(offset);
}

void MainWindow::SlotMoveObjectY(int offset) {
  if (offset == previous_offsets_.y) {
    return;
  }
  controller_.MoveScene(0, offset - previous_offsets_.y, 0);
  previous_offsets_.y = offset;
  ui_->sliderMoveY->setSliderPosition(offset);
  ui_->moveY->setValue(offset);
}

void MainWindow::SlotMoveObjectZ(int offset) {
  if (offset == previous_offsets_.z) {
    return;
  }
  controller_.MoveScene(0, 0, offset - previous_offsets_.z);
  previous_offsets_.z = offset;
  ui_->sliderMoveZ->setSliderPosition(offset);
  ui_->moveZ->setValue(offset);
}

void MainWindow::SlotRotateObjectX(int angle_deg) {
  if (angle_deg == previous_rotation_.x) {
    return;
  }
  controller_.RotateScene((angle_deg - previous_rotation_.x) * M_PI / 180, 0,
                          0);
  previous_rotation_.x = angle_deg;
  ui_->sliderRotateX->setSliderPosition(angle_deg);
  ui_->rotateX->setValue(angle_deg);
}

void MainWindow::SlotRotateObjectY(int angle_deg) {
  if (angle_deg == previous_rotation_.y) {
    return;
  }
  controller_.RotateScene(0, (angle_deg - previous_rotation_.y) * M_PI / 180,
                          0);
  previous_rotation_.y = angle_deg;
  ui_->sliderRotateY->setSliderPosition(angle_deg);
  ui_->rotateY->setValue(angle_deg);
}

void MainWindow::SlotRotateObjectZ(int angle_deg) {
  if (angle_deg == previous_rotation_.z) {
    return;
  }
  controller_.RotateScene(0, 0,
                          (angle_deg - previous_rotation_.z) * M_PI / 180);
  previous_rotation_.z = angle_deg;
  ui_->sliderRotateZ->setSliderPosition(angle_deg);
  ui_->rotateZ->setValue(angle_deg);
}

void MainWindow::SlotScaleObjectXYZ(int scale) {
  if (scale == previous_scales_.x) {
    return;
  }
  controller_.ScaleScene(scale / previous_scales_.x, scale / previous_scales_.y,
                         scale / previous_scales_.z);
  previous_scales_.x = scale;
  previous_scales_.y = scale;
  previous_scales_.z = scale;
  ui_->sliderScale->setSliderPosition(scale);
  ui_->scale->setValue(scale);
}

void MainWindow::SlotChangeTypeProjection(int ind_type_proj) {
  scene_params_.type_projection =
      static_cast<SceneParameters::TypeProjection>(ind_type_proj);
  Notify();
}

void MainWindow::SlotChangeBackground() {
  QColor color = QColorDialog::getColor(scene_params_.background_color);
  if (color.isValid()) {
    ui_->backgroundColor->setStyleSheet(
        QString("background-color: rgb(%1, %2, %3)")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue()));
    scene_params_.background_color = std::move(color);
    Notify();
  }
}

void MainWindow::SlotChangeEdgeType(int ind_edge_type) {
  scene_params_.edge_type =
      static_cast<SceneParameters::TypeEdges>(ind_edge_type);
  Notify();
}

void MainWindow::SlotChangeVertexType(int ind_vertex_type) {
  scene_params_.vertex_type =
      static_cast<SceneParameters::TypeVertex>(ind_vertex_type);
  Notify();
}

void MainWindow::SlotChangeEdgeWidth(int width) {
  scene_params_.edge_width = width;
  Notify();
}

void MainWindow::SlotChangeVertexSize(int size) {
  scene_params_.vertex_size = size;
  Notify();
}

void MainWindow::SlotChangeEdgeColor() {
  QColor color = QColorDialog::getColor(scene_params_.edge_color);
  if (color.isValid()) {
    ui_->lineColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                      .arg(color.red())
                                      .arg(color.green())
                                      .arg(color.blue()));
    scene_params_.edge_color = std::move(color);
    Notify();
  }
}

void MainWindow::SlotChangeVertexColor() {
  QColor color = QColorDialog::getColor(scene_params_.vertex_color);
  if (color.isValid()) {
    ui_->vertexColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                        .arg(color.red())
                                        .arg(color.green())
                                        .arg(color.blue()));
    scene_params_.vertex_color = std::move(color);
    Notify();
  }
}

void MainWindow::SlotSelectGifPath() {
  QString new_dir =
      QFileDialog::getExistingDirectory(0, "Выбор директории записи gif", "./");
  if (!new_dir.isEmpty()) {
    gif_params_.gif_dir = new_dir;
    ui_->gifPath->setText(gif_params_.gif_dir);
    ui_->gifPath->setToolTip(gif_params_.gif_dir);
  }
}

void MainWindow::SlotSelectScreenPath() {
  QString new_dir = QFileDialog::getExistingDirectory(
      0, "Выбор директории записи скринов", "./");
  if (!new_dir.isEmpty()) {
    screen_params_.dir_path = new_dir;
    ui_->screenPath->setText(screen_params_.dir_path);
    ui_->screenPath->setToolTip(screen_params_.dir_path);
  }
}

void MainWindow::SlotMakeGif() {
  ui_->buttonCreateGif->setEnabled(false);
  gif_params_.gif_before_time_left = gif_params_.gif_before_time;
  PreparationMakingGif();
}

void MainWindow::PreparationMakingGif() {
  if (gif_params_.gif_before_time_left <= 0) {
    StartMakingGif();
    return;
  }
  ShowMessage(QString("Запись GIF начнется через %1 сек.")
                  .arg(gif_params_.gif_before_time_left * 0.001),
              QColor(30, 144, 255), 0);
  gif_params_.gif_before_time_left -= 1000;
  QTimer::singleShot(1000, this, SLOT(PreparationMakingGif()));
}

void MainWindow::StartMakingGif() {
  ShowMessage(QString("Идет запись GIF"), QColor(39, 174, 96), 0);
  QString uniq_name =
      QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-z");
  gif_params_.gif_file_path =
      QString("%1/video_%2.gif").arg(gif_params_.gif_dir).arg(uniq_name);

  controller_.CreateGif(gif_params_.gif_file_path.toStdString(),
                        gif_params_.gif_width, gif_params_.gif_height,
                        gif_params_.gif_fps, gif_params_.gif_duration / 10);
  CreateFrameToGif();
}

void MainWindow::CreateFrameToGif() {
  if (controller_.AddGifFrame()) {
    ui_->buttonCreateGif->setEnabled(true);
    ShowMessage(QString("Создана GIF: %1").arg(gif_params_.gif_file_path),
                QColor(50, 205, 50), 5000);
    return;
  }

  QTimer::singleShot(controller_.GetGifDelay() * 10, this,
                     SLOT(CreateFrameToGif()));
}

void MainWindow::SlotPrintScreenBMP() { MakeScreenshot("bmp"); }

void MainWindow::SlotPrintScreenJPEG() { MakeScreenshot("jpeg"); }

void MainWindow::MakeScreenshot(QString extension) {
  QImage img = controller_.GetFrameBuffer();
  QString uniq_name =
      QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-z");
  QString file_name = QString("%1/image_%2.%3")
                          .arg(screen_params_.dir_path)
                          .arg(uniq_name)
                          .arg(extension);
  img.save(file_name);
  ShowMessage(QString("Создан снимок экрана: %1").arg(file_name),
              QColor(0, 128, 0), 5000);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    ui_->sliderScale->setSliderPosition(previous_scales_.x + 5);
  } else {
    ui_->sliderScale->setSliderPosition(previous_scales_.x - 5);
  }
}

void MainWindow::ShowMessage(QString msg, QColor color, int message_timeout) {
  ui_->statusbar->setStyleSheet(QString("color: " + color.name()));
  ui_->statusbar->showMessage(msg);
  if (message_timeout > 0) {
    QTimer::singleShot(message_timeout, this, SLOT(ShowMessage()));
  }
}

}  // namespace s21
