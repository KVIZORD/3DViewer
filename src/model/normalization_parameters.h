#ifndef _3DVIEWER_MODEL_INCLUDE_NORMALIZATION_PARAMETERS_H_
#define _3DVIEWER_MODEL_INCLUDE_NORMALIZATION_PARAMETERS_H_

namespace s21 {

struct NormalizationParameters {
  float min = 0;
  float max = 0;
  float step;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_NORMALIZATION_PARAMETERS_H_
