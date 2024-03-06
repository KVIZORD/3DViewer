#ifndef _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_BUILDER_H_
#define _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_BUILDER_H_

#include <cmath>

#include "model/transform_matrix.h"

namespace s21 {

class TransformMatrixBuilder {
 public:
  static TransformMatrix CreateRotationMatrix(float, float, float);
  static TransformMatrix CreateMoveMatrix(float, float, float);
  static TransformMatrix CreateScaleMatrix(float, float, float);
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_BUILDER_H_
