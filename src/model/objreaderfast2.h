#ifndef _3DVIEWER_MODEL_INCLUDE_OBJREADERFAST2_H_
#define _3DVIEWER_MODEL_INCLUDE_OBJREADERFAST2_H_

#include <string>
#include <vector>

#include "basefilereader.h"
#include "normalization_parameters.h"
#include "scene.h"

namespace s21 {

class OBJReaderFast2 : public BaseFileReader {
 public:
  const int kMaxLineLength = 256;
  Scene ReadScene(const std::string &path) const override;

 private:
  const char kVertexToken = 'v';
  const char kFaceToken = 'f';
  struct Line {
    size_t size_buf;
    char *buf;
    Line(size_t sz) : size_buf(sz), buf(new char[sz]) {}
    ~Line() { delete[] buf; }
  };
  bool ReadLine(FILE *obj_file, Line *line) const;
  void ResizeLine(Line *line) const;

  void ReadFace(char *str, std::vector<int> &edges,
                size_t count_vertices) const;
  void ReadVertices(const Line *line, std::vector<float> &vertices) const;
  void CalculateNormalizationParams(const std::vector<float> &vertices,
                                    Scene &scene) const;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_OBJREADERFAST2_H_
