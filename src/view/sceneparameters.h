#ifndef _3DVIEWER_VIEW_INCLUDE_SCENEPARAMETERS_H_
#define _3DVIEWER_VIEW_INCLUDE_SCENEPARAMETERS_H_

#include <QColor>

namespace s21 {

struct SceneParameters {
  enum TypeProjection { kParallel, kCentral };
  enum TypeEdges { kDotted, kSolid };
  enum TypeVertex { kAbsent, kCircle, kSquare };

  TypeProjection type_projection;
  QColor background_color;
  QColor edge_color;
  QColor vertex_color;
  TypeEdges edge_type;
  TypeVertex vertex_type;
  int edge_width;
  int vertex_size;
};

}  // namespace s21

#endif  // _3DVIEWER_VIEW_INCLUDE_SCENEPARAMETERS_H_
