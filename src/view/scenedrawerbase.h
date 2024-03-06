#ifndef _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_BASE_H_
#define _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_BASE_H_

#include <QOpenGLWidget>

#include "model/scene.h"
#include "sceneparameters.h"

namespace s21 {

class SceneDrawerBase {
 public:
  virtual void UpdateScene() = 0;
  virtual void SetScene(Scene *) = 0;
  virtual void SetParamsScene(SceneParameters *) = 0;
  virtual void SetParentOpenGL(QWidget *) = 0;
  virtual QImage GetFrameBuffer() = 0;
};

}  // namespace s21

#endif  // _3DVIEWER_VIEW_INCLUDE_SCENEDRAWER_BASE_H_
