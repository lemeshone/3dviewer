#pragma once
#include <QObject>
#include <QString>

#include "model/model.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT
 public:
  explicit Controller(Model *model, QObject *parent = nullptr)
      : QObject(parent), model_(model) {}
  Model *model() const { return model_; }

 public slots:
  void LoadModel(const QString &path);

  void Translate(float dx, float dy, float dz);
  void RotateX(float rad);
  void RotateY(float rad);
  void RotateZ(float rad);
  void Scale(float sx, float sy, float sz);

  void SetTranslateAbs(float tx, float ty, float tz);
  void SetRotateAbs(float rx, float ry, float rz);
  void SetScaleAbs(float s);

 signals:
  void ModelLoaded(size_t vertices, size_t edges);
  void ModelLoadError(const QString &message);
  void ModelChanged();

 private:
  Model *model_;
};
}  // namespace s21
