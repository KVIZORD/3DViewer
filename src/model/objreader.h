#ifndef _3DVIEWER_MODEL_INCLUDE_OBJREADER_H_
#define _3DVIEWER_MODEL_INCLUDE_OBJREADER_H_

#include <sstream>
#include <string>
#include <vector>

#include "model/basefilereader.h"
#include "model/normalization_parameters.h"
#include "model/scene.h"

namespace s21 {

class OBJReader : public BaseFileReader {
 public:
  const std::string kVertexToken = "v";
  const std::string kFaceToken = "f";

 public:
  Scene ReadScene(const std::string &) const override;

 private:
  void ReadFace(std::stringstream &, std::vector<int> &, size_t) const;
  void Read3DCoords(std::stringstream &, std::vector<float> &) const;
  void CalculateNormalizationParams(const std::vector<float> &, Scene &) const;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_OBJREADER_H_
