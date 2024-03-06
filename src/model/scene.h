#ifndef _3DVIEWER_MODEL_INCLUDE_SCENE_H_
#define _3DVIEWER_MODEL_INCLUDE_SCENE_H_

#include <cstddef>
#include <vector>

#include "model/normalization_parameters.h"
#include "model/transform_matrix.h"

namespace s21 {

class Scene {
 public:
  NormalizationParameters GetNormalizationParams();
  size_t GetCountVertices() const;
  size_t GetCountEdges() const;
  void SetNormalizationParams(NormalizationParameters &&);
  void SetEdges(std::vector<int> &&);
  void TransformVertices(const TransformMatrix &);
  void SetVertices(std::vector<float> &&);
  const std::vector<float> &GetVertices() const;
  const std::vector<int> &GetEdges() const;

 private:
  std::vector<float> vertices_;
  std::vector<int> edges_;
  NormalizationParameters normalization_params_;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_SCENE_H_
