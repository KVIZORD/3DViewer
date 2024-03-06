#include "model/scene.h"

#include <chrono>
#include <iostream>

namespace s21 {

void Scene::TransformVertices(const TransformMatrix &matrix) {
  matrix.TransformVertices(vertices_);
}

size_t Scene::GetCountVertices() const { return vertices_.size() / 3; }

size_t Scene::GetCountEdges() const { return edges_.size() * 0.5; }

NormalizationParameters Scene::GetNormalizationParams() {
  return normalization_params_;
}

void Scene::SetNormalizationParams(NormalizationParameters &&params) {
  std::swap(normalization_params_, params);
}

void Scene::SetVertices(std::vector<float> &&vertices) {
  std::swap(vertices_, vertices);
}

void Scene::SetEdges(std::vector<int> &&edges) { std::swap(edges_, edges); }

const std::vector<float> &Scene::GetVertices() const { return vertices_; }

const std::vector<int> &Scene::GetEdges() const { return edges_; }

}  // namespace s21
