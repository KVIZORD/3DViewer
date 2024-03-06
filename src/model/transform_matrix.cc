#include "model/transform_matrix.h"

#include <stdexcept>

namespace s21 {
TransformMatrix::TransformMatrix() {
  for (int row = 0; row <= matrix_size_; ++row) {
    for (int col = 0; col <= matrix_size_; ++col) {
      matrix_[row][col] = (row == col) ? 1 : 0;
    }
  }
}

float& TransformMatrix::operator()(int row, int col) {
  if (row < 0 || row > matrix_size_ || col < 0 || col > matrix_size_) {
    throw std::out_of_range("IndexError: matrix index out of range");
  }
  return matrix_[row][col];
}

float TransformMatrix::operator()(int row, int col) const {
  if (row < 0 || row > matrix_size_ || col < 0 || col > matrix_size_) {
    throw std::out_of_range("IndexError: matrix index out of range");
  }
  return matrix_[row][col];
}

TransformMatrix TransformMatrix::operator*(
    const TransformMatrix& rhs_matrix) const {
  TransformMatrix result;
  for (int row = 0; row <= matrix_size_; ++row) {
    for (int col = 0; col <= matrix_size_; ++col) {
      result(row, col) = 0;
      for (int k = 0; k <= matrix_size_; ++k) {
        result(row, col) += matrix_[row][k] * rhs_matrix(k, col);
      }
    }
  }
  return result;
}

void TransformMatrix::TransformVertices(std::vector<float>& vertices) const {
  for (size_t i = 0; i + 3 <= vertices.size(); i += 3) {
    float x = vertices[i] * matrix_[0][0] + vertices[i + 1] * matrix_[0][1] +
              vertices[i + 2] * matrix_[0][2] + matrix_[0][3];
    float y = vertices[i] * matrix_[1][0] + vertices[i + 1] * matrix_[1][1] +
              vertices[i + 2] * matrix_[1][2] + matrix_[1][3];
    float z = vertices[i] * matrix_[2][0] + vertices[i + 1] * matrix_[2][1] +
              vertices[i + 2] * matrix_[2][2] + matrix_[2][3];

    vertices[i] = x;
    vertices[i + 1] = y;
    vertices[i + 2] = z;
  }
}

}  // namespace s21
