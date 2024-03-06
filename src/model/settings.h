#ifndef _3DVIEWER_MODEL_INCLUDE_SETTINGS_H_
#define _3DVIEWER_MODEL_INCLUDE_SETTINGS_H_

#include <QSettings>
#include <QString>

#include "view/sceneparameters.h"

namespace s21 {

class MySettings {
 public:
  MySettings(const QString &, QSettings::Format);

  SceneParameters GetSettings();

  void UpdateSettings(const SceneParameters &);

 private:
  QSettings settings_;
};

}  // namespace s21

#endif  // _3DVIEWER_MODEL_INCLUDE_SETTINGS_H_
