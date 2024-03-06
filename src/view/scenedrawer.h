#ifndef _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_H_
#define _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_H_

#include <QColor>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <cmath>

#include "model/scene.h"
#include "view/scenedrawerbase.h"
#include "view/sceneparameters.h"

namespace s21 {

class SceneDrawer : public QOpenGLWidget,
                    protected QOpenGLFunctions,
                    public SceneDrawerBase {
  Q_OBJECT

 public:
  SceneDrawer(QWidget *parent = nullptr);
  ~SceneDrawer() {}

  void SetScene(Scene *);
  void UpdateScene();
  void SetParamsScene(SceneParameters *);
  void SetParentOpenGL(QWidget *);
  QImage GetFrameBuffer();

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int, int);

  void SetTypeProjection();
  void SetBackgroundScene();
  void SetEdgesType();
  void SetEdgesColor();
  void SetEdgesWidth();
  void RenderEdges();
  void SetVerticesType();
  void SetVerticesColor();
  void SetVerticesSize();
  void RenderVertices();

 private:
  QWidget *parent_;
  Scene *scene_ = nullptr;
  SceneParameters *scene_params_ = nullptr;
};

}  // namespace s21

#endif  // _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_H_
