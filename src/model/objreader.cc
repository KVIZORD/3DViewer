#include "model/objreader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace s21 {

void OBJReader::Read3DCoords(std::stringstream &tokens,
                             std::vector<float> &vertices) const {
  float x, y, z;
  tokens >> x >> y >> z;

  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);
}

void OBJReader::ReadFace(std::stringstream &tokens, std::vector<int> &edges,
                         size_t count_vertices) const {
  std::string line;
  std::vector<int> added_vertices;

  while (tokens >> line) {
    int vertex_index;
    std::string token;

    size_t slash_pos = line.find("//");

    if (slash_pos != std::string::npos) {
      token = line.substr(0, slash_pos);
    } else {
      token = line;
    }

    vertex_index = std::stoi(token);

    if (vertex_index < 0) {
      vertex_index = count_vertices + vertex_index;
    } else {
      vertex_index -= 1;
    }
    if (vertex_index < 0 || vertex_index >= static_cast<int>(count_vertices)) {
      throw std::invalid_argument("Invalid face index: " +
                                  std::to_string(vertex_index));
    }
    added_vertices.push_back(vertex_index);
  }

  int size = static_cast<int>(added_vertices.size());
  for (int i = 0; i < size; ++i) {
    int start = i;
    int end = i + 1 == size ? 0 : i + 1;

    edges.push_back(added_vertices[start]);
    edges.push_back(added_vertices[end]);
  }
}

void OBJReader::CalculateNormalizationParams(const std::vector<float> &vertices,
                                             Scene &scene) const {
  NormalizationParameters params = scene.GetNormalizationParams();

  float x = abs(vertices[vertices.size() - 1]);
  float y = abs(vertices[vertices.size() - 2]);
  float z = abs(vertices[vertices.size() - 3]);

  float max = std::max(x, std::max(y, z));
  params.max = std::max(max, params.max);
  params.min = -params.max;
  params.step = params.max / 100.0 * 5.0;

  scene.SetNormalizationParams(std::move(params));
}

Scene OBJReader::ReadScene(const std::string &path) const {
  Scene scene;
  std::vector<float> vertices;
  std::vector<int> edges;
  std::ifstream obj_file(path);

  if (obj_file.is_open()) {
    std::string curr_line;

    while (std::getline(obj_file, curr_line)) {
      std::stringstream tokens(curr_line);
      std::string curr_token;
      tokens >> curr_token;

      if (curr_token == kVertexToken) {
        Read3DCoords(tokens, vertices);
        CalculateNormalizationParams(vertices, scene);
      } else if (curr_token == kFaceToken) {
        ReadFace(tokens, edges, vertices.size() / 3);
      }
    }

    obj_file.close();
  } else {
    throw std::runtime_error("Failed to open file: " + path);
  }

  scene.SetVertices(std::move(vertices));
  scene.SetEdges(std::move(edges));

  return scene;
}

}  // namespace s21
