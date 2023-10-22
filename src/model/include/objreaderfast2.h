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
  Scene ReadScene(const std::string &path) override;

private:
  const char kVertexToken = 'v';
  const char kFaceToken = 'f';
  struct Line {
    size_t size_buf;
    char *buf;
    Line(size_t sz) : size_buf(sz), buf(new char[sz]) {}
    ~Line() { delete[] buf; }
  };
  bool ReadLine(FILE *obj_file, Line *line);
  void ResizeLine(Line *line);

  void ReadFace(char *str, std::vector<int> &edges, size_t count_vertices);
  void ReadVertices(const Line *line, std::vector<float> &vertices);
  void CalculateNormalizationParams(const std::vector<float> &vertices,
                                    Scene &scene);
};

} // namespace s21

#endif // _3DVIEWER_MODEL_INCLUDE_OBJREADERFAST2_H_
