#include "controller/controller.h"

#include <stdexcept>

namespace s21 {

Controller::Controller(BaseFileReader &file_reader_,
                       SceneDrawerBase &scene_drawer_, MySettings &settings_)
    : file_reader_(file_reader_),
      scene_drawer_(scene_drawer_),
      settings_(settings_) {}

SceneParameters Controller::GetSettings() const {
  return settings_.GetSettings();
}

void Controller::UpdateSettings(const SceneParameters &scene_params) const {
  return settings_.UpdateSettings(scene_params);
}

OperationResult Controller::LoadScene(const QString &path) {
  try {
    scene_ = file_reader_.ReadScene(path.toStdString());
  } catch (const std::exception &e) {
    return {e.what(), false};
  }
  SetScene();

  return {"", true};
}

void Controller::SetParentForSceneDraw(QWidget *parent) const {
  scene_drawer_.SetParentOpenGL(parent);
}

void Controller::UpdateSceneDraw() const { scene_drawer_.UpdateScene(); }

void Controller::SetScene() {
  scene_drawer_.SetScene(&scene_);
  scene_drawer_.UpdateScene();
}

void Controller::SetParamsScene(SceneParameters *params_scene) const {
  scene_drawer_.SetParamsScene(params_scene);
  scene_drawer_.UpdateScene();
}

QImage Controller::GetFrameBuffer() const {
  return scene_drawer_.GetFrameBuffer();
}

size_t Controller::GetCountVertices() const {
  return scene_.GetCountVertices();
}

size_t Controller::GetCountEdges() const { return scene_.GetCountEdges(); }

void Controller::MoveScene(float x, float y, float z) {
  float step = scene_.GetNormalizationParams().step;
  scene_.TransformVertices(
      TransformMatrixBuilder::CreateMoveMatrix(x * step, y * step, z * step));
  scene_drawer_.UpdateScene();
}

void Controller::RotateScene(float x, float y, float z) {
  scene_.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(x, y, z));
  scene_drawer_.UpdateScene();
}

void Controller::ScaleScene(float x, float y, float z) {
  scene_.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(x, y, z));
  scene_drawer_.UpdateScene();
}

void Controller::CreateGif(const std::string &filename, int gif_width,
                           int gif_height, int fps, int duration) {
  gif_generator_.InitializeGenerator(filename, gif_width, gif_height, fps,
                                     duration);
}

bool Controller::AddGifFrame() {
  gif_generator_.AddFrame(
      GetFrameBuffer()
          .scaled(gif_generator_.GetWidth(), gif_generator_.GetHeight())
          .convertToFormat(QImage::Format_RGBA8888)
          .bits());

  return gif_generator_.GetFinished();
}

int Controller::GetGifDelay() const { return gif_generator_.GetDelay(); }

}  // namespace s21
