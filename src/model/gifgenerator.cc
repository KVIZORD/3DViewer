#include "include/gifgenerator.h"

#include <QDebug>
namespace s21 {

void GifGenerator::InitializeGenerator(const std::string &filename, int width,
                                       int height, int fps, int duration) {
  initialized_ = true;
  finished_ = false;
  currentTime_ = 0;
  filename_ = filename;
  delay_ = 100 / fps;
  height_ = height;
  width_ = width;
  fps_ = fps;
  duration_ = duration;

  GifBegin(&gifWriter_, filename_.c_str(), width_, height_, delay_);
}

void GifGenerator::AddFrame(const uint8_t *image) {
  if (!initialized_) return;

  GifWriteFrame(&gifWriter_, image, width_, height_, delay_);
  currentTime_ += delay_;

  if (currentTime_ >= duration_) {
    GifEnd(&gifWriter_);
    finished_ = true;
  }
}

bool GifGenerator::GetFinished() { return finished_; }

bool GifGenerator::GetInitialized() { return initialized_; }

int GifGenerator::GetDelay() { return delay_; }

int GifGenerator::GetWidth() { return width_; }

int GifGenerator::GetHeight() { return height_; }

GifGenerator::~GifGenerator() {
  if (!finished_ && initialized_) {
    GifEnd(&gifWriter_);
  }
}
}  // namespace s21
