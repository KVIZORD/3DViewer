#include "view/scenedrawer.h"

#include <QDebug>

#include "ui_mainwindow.h"

namespace s21 {

SceneDrawer::SceneDrawer(QWidget *parent_)
    : QOpenGLWidget{parent_}, parent_(parent_) {}

void SceneDrawer::UpdateScene() { update(); }

void SceneDrawer::SetScene(Scene *new_scene) { scene_ = new_scene; }

void SceneDrawer::SetParamsScene(SceneParameters *new_params) {
  scene_params_ = new_params;
}

void SceneDrawer::SetParentOpenGL(QWidget *parent) {
  setParent(parent);
  QVBoxLayout *layout = new QVBoxLayout(parent);
  layout->addWidget(this);
  layout->setContentsMargins(0, 0, 0, 0);
}

QImage SceneDrawer::GetFrameBuffer() { return grabFramebuffer(); }

void SceneDrawer::initializeGL() {
  QOpenGLWidget::initializeGL();
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void SceneDrawer::paintGL() {
  SetBackgroundScene();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (scene_ != nullptr && scene_params_ != nullptr) {
    SetTypeProjection();

    SetEdgesColor();
    SetEdgesWidth();
    SetEdgesType();

    RenderEdges();

    SetVerticesColor();
    SetVerticesSize();
    SetVerticesType();

    RenderVertices();
  }
}

void SceneDrawer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void SceneDrawer::RenderVertices() {
  if (scene_ == nullptr) {
    return;
  }
  if (scene_params_->vertex_type != SceneParameters::TypeVertex::kAbsent) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, scene_->GetVertices().data());

    glDrawArrays(GL_POINTS, 0, scene_->GetVertices().size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void SceneDrawer::RenderEdges() {
  if (scene_ == nullptr) {
    return;
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, scene_->GetVertices().data());

  glDrawElements(GL_LINES, scene_->GetEdges().size(), GL_UNSIGNED_INT,
                 scene_->GetEdges().data());

  glDisableClientState(GL_VERTEX_ARRAY);
}

void SceneDrawer::SetTypeProjection() {
  float value_max = scene_->GetNormalizationParams().max;
  float value_min = scene_->GetNormalizationParams().min;

  double ratio_x = width() > height() ? static_cast<float>(width()) /
                                            static_cast<float>(height())
                                      : 1;
  double ratio_y = width() > height() ? 1
                                      : static_cast<float>(height()) /
                                            static_cast<float>(width());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (scene_params_->type_projection ==
      SceneParameters::TypeProjection::kCentral) {
    float fov = 60.0 * M_PI / 180;
    float heapHeight = value_max / 2 / (2 * tan(fov / 2));
    float left = (value_min / 4) * ratio_x;
    float right = (value_max / 4) * ratio_x;
    float bottom = (value_min / 4) * ratio_y;
    float top = (value_max / 4) * ratio_y;
    glFrustum(left, right, bottom, top, heapHeight, value_max * 100);
    glTranslated(0.0f, 0.0f, -heapHeight * 4);
  } else if (scene_params_->type_projection ==
             SceneParameters::TypeProjection::kParallel) {
    float left = value_min * ratio_x * 2;
    float right = value_max * ratio_x * 2;
    float bottom = value_min * ratio_y * 2;
    float top = value_max * ratio_y * 2;
    glOrtho(left, right, bottom, top, value_min * 10, value_max * 50);
  }

  glMatrixMode(GL_MODELVIEW);
}

void SceneDrawer::SetBackgroundScene() {
  if (scene_params_ != nullptr) {
    glClearColor(scene_params_->background_color.redF(),
                 scene_params_->background_color.greenF(),
                 scene_params_->background_color.blueF(),
                 scene_params_->background_color.alphaF());
  }
}

void SceneDrawer::SetEdgesType() {
  if (scene_params_->edge_type == SceneParameters::TypeEdges::kSolid) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  } else if (scene_params_->edge_type == SceneParameters::TypeEdges::kDotted) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void SceneDrawer::SetEdgesColor() {
  glColor3f(scene_params_->edge_color.redF(),
            scene_params_->edge_color.greenF(),
            scene_params_->edge_color.blueF());
}

void SceneDrawer::SetEdgesWidth() { glLineWidth(scene_params_->edge_width); }

void SceneDrawer::SetVerticesType() {
  if (scene_params_->vertex_type == SceneParameters::TypeVertex::kCircle) {
    glEnable(GL_POINT_SMOOTH);
  } else if (scene_params_->vertex_type ==
             SceneParameters::TypeVertex::kSquare) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void SceneDrawer::SetVerticesColor() {
  glColor3f(scene_params_->vertex_color.redF(),
            scene_params_->vertex_color.greenF(),
            scene_params_->vertex_color.blueF());
}

void SceneDrawer::SetVerticesSize() { glPointSize(scene_params_->vertex_size); }

}  // namespace s21
