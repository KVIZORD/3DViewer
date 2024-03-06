#include "model/settings.h"

namespace s21 {

MySettings::MySettings(const QString& path_file, QSettings::Format format_file)
    : settings_(path_file, format_file) {}

SceneParameters MySettings::GetSettings() {
  SceneParameters scene_params{};

  settings_.beginGroup("Other");
  scene_params.type_projection = static_cast<SceneParameters::TypeProjection>(
      settings_.value("projection", 0).toInt());
  scene_params.background_color =
      settings_.value("background", QColor(Qt::white)).value<QColor>();
  settings_.endGroup();

  settings_.beginGroup("Edges");
  scene_params.edge_type = static_cast<SceneParameters::TypeEdges>(
      settings_.value("type", 0).toInt());
  scene_params.edge_width = settings_.value("width", 1).toInt();
  scene_params.edge_color =
      settings_.value("color", QColor(Qt::red)).value<QColor>();
  settings_.endGroup();

  settings_.beginGroup("Vertex");
  scene_params.vertex_type = static_cast<SceneParameters::TypeVertex>(
      settings_.value("type", 1).toInt());
  scene_params.vertex_size = settings_.value("size", 3).toInt();
  scene_params.vertex_color =
      settings_.value("color", QColor(Qt::blue)).value<QColor>();
  settings_.endGroup();
  return scene_params;
}

void MySettings::UpdateSettings(const SceneParameters& scene_params) {
  settings_.beginGroup("Other");
  settings_.setValue(
      "projection",
      QString::number(static_cast<int>(scene_params.type_projection)));
  settings_.setValue("background", scene_params.background_color);
  settings_.endGroup();

  settings_.beginGroup("Edges");
  settings_.setValue("type",
                     QString::number(static_cast<int>(scene_params.edge_type)));
  settings_.setValue("width", QString::number(scene_params.edge_width));
  settings_.setValue("color", scene_params.edge_color);
  settings_.endGroup();

  settings_.beginGroup("Vertex");
  settings_.setValue(
      "type", QString::number(static_cast<int>(scene_params.vertex_type)));
  settings_.setValue("size", QString::number(scene_params.vertex_size));
  settings_.setValue("color", scene_params.vertex_color);
  settings_.endGroup();

  settings_.sync();
}

}  // namespace s21
