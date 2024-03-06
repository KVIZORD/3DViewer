#include "model/objreaderfast2.h"

#include <cstring>
#include <locale>

namespace s21 {

void OBJReaderFast2::CalculateNormalizationParams(
    const std::vector<float> &vertices, Scene &scene) const {
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

void OBJReaderFast2::ReadFace(char *str, std::vector<int> &edges,
                              size_t count_vertices) const {
  str += 1;
  int ind_vertex = 0;
  int ind_texture = 0;
  int ind_normal = 0;
  int first_ind_vertex = 0;
  bool is_first = true;
  while (*str) {
    while (*str && *str == ' ') {
      str += 1;
    }
    if (sscanf(str, "%d/%d/%d", &ind_vertex, &ind_texture, &ind_normal) > 0) {
      while (*str && *str != ' ') {
        str += 1;
      }
      if (ind_vertex < 0) {
        ind_vertex = count_vertices + ind_vertex;
      } else {
        ind_vertex -= 1;
      }
      if (ind_vertex < 0 || ind_vertex >= static_cast<int>(count_vertices)) {
        throw std::invalid_argument("Invalid face index: " +
                                    std::to_string(ind_vertex));
      }
      if (is_first) {
        first_ind_vertex = ind_vertex;
        is_first = false;
      } else {
        edges.push_back(ind_vertex);
      }
      edges.push_back(ind_vertex);
    } else {
      break;
    }
  }
  if (!is_first) {
    edges.push_back(first_ind_vertex);
  }
}

void OBJReaderFast2::ReadVertices(const Line *line,
                                  std::vector<float> &vertices) const {
  float x, y, z;
  if (std::sscanf(line->buf, "v %f %f %f", &x, &y, &z) == 3) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
  } else {
    throw std::invalid_argument("Invalid vertex: " + std::string(line->buf));
  }
}

Scene OBJReaderFast2::ReadScene(const std::string &path) const {
  setlocale(LC_ALL, "C");
  Scene scene;
  std::vector<float> vertices;
  std::vector<int> edges;

  FILE *obj_file = fopen(path.c_str(), "r");

  if (obj_file) {
    Line line(kMaxLineLength);
    int i = 0;
    while (!feof(obj_file) && ReadLine(obj_file, &line)) {
      char first_ch = line.buf[0];
      char second_ch = line.buf[1];
      if (first_ch == kVertexToken && second_ch == ' ') {
        ReadVertices(&line, vertices);
        CalculateNormalizationParams(vertices, scene);
      } else if (first_ch == kFaceToken && second_ch == ' ') {
        ++i;
        ReadFace(line.buf, edges, vertices.size() / 3);
      }
    }
    fclose(obj_file);
  } else {
    throw std::runtime_error("Failed to open file: " + path);
  }

  scene.SetVertices(std::move(vertices));
  scene.SetEdges(std::move(edges));

  return scene;
}

bool OBJReaderFast2::ReadLine(FILE *obj_file, Line *line) const {
  char *ptr = line->buf;
  while (true) {
    if (!fgets(ptr, kMaxLineLength - 1, obj_file)) {
      return false;
    }
    size_t len = strlen(line->buf);
    if (line->buf[len - 1] == '\n' || feof(obj_file)) {
      return true;
    }
    if (line->size_buf < len + kMaxLineLength + 2) {
      ResizeLine(line);
    }
    ptr = line->buf + len;
  }
  return true;
}

void OBJReaderFast2::ResizeLine(Line *line) const {
  char *new_str = new char[line->size_buf * 2];
  delete[] line->buf;
  line->size_buf *= 2;
  line->buf = new_str;
}

}  // namespace s21
