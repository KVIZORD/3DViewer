#ifndef _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_H_
#define _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_H_

#include <vector>

namespace s21 {

class TransformMatrix {
 public:
  TransformMatrix();
  float &operator()(int, int);
  float operator()(int, int) const;
  TransformMatrix operator*(const TransformMatrix &) const;
  void TransformVertices(std::vector<float> &) const;

 private:
  float matrix_[4][4];
  static const int matrix_size_ = 3;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_TRANSFORM_MATRIX_H_
