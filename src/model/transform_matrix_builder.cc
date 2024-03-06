#include "model/transform_matrix_builder.h"

namespace s21 {
TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(float x, float y,
                                                             float z) {
  TransformMatrix matrix;

  float sin_x = std::sin(x);
  float sin_y = std::sin(y);
  float sin_z = std::sin(z);
  float cos_x = std::cos(x);
  float cos_y = std::cos(y);
  float cos_z = std::cos(z);
  matrix(0, 0) = cos_y * cos_z;
  matrix(0, 1) = -cos_y * sin_z;
  matrix(0, 2) = sin_y;
  matrix(1, 0) = sin_x * sin_y * cos_z + cos_x * sin_z;
  matrix(1, 1) = -sin_x * sin_y * sin_z + cos_x * cos_z;
  matrix(1, 2) = -sin_x * cos_y;
  matrix(2, 0) = -cos_x * sin_y * cos_z + sin_x * sin_z;
  matrix(2, 1) = cos_x * sin_y * sin_z + sin_x * cos_z;
  matrix(2, 2) = cos_x * cos_y;

  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(float x, float y,
                                                         float z) {
  TransformMatrix matrix;

  matrix(0, 3) = x;
  matrix(1, 3) = y;
  matrix(2, 3) = z;

  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(float x, float y,
                                                          float z) {
  TransformMatrix matrix;

  matrix(0, 0) = x;
  matrix(1, 1) = y;
  matrix(2, 2) = z;

  return matrix;
}

}  // namespace s21
