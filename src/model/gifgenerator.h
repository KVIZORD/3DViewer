#ifndef _3DVIEWER_MODEL_INCLUDE_GIFGENERATOR_H_
#define _3DVIEWER_MODEL_INCLUDE_GIFGENERATOR_H_

#include <QImage>
#include <cstdint>
#include <string>
#include <vector>

#include "lib/gif/gif.h"

namespace s21 {

class GifGenerator {
 public:
  GifGenerator() {}

  void InitializeGenerator(const std::string &, int, int, int, int);
  void AddFrame(const uint8_t *);

  bool GetFinished() const;
  bool GetInitialized() const;
  int GetWidth() const;
  int GetHeight() const;
  int GetDelay() const;

  ~GifGenerator();

 private:
  GifWriter gifWriter_{};
  std::string filename_{};
  int width_{};
  int height_{};
  int fps_{};
  int delay_{};
  int duration_{};
  int currentTime_ = 0;
  bool finished_ = false;
  bool initialized_ = false;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_GIFGENERATOR_H_
