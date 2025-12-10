#include "controller.h"

#include <exception>

namespace s21 {

void Controller::LoadModel(const QString &path) {
  try {
    model_->loadFromFile(path.toStdString());
    emit ModelLoaded(model_->vertexCount(), model_->edgeCount());
    emit ModelChanged();
  } catch (const std::exception &e) {
    emit ModelLoadError(QString::fromUtf8(e.what()));
  }
}

void Controller::Translate(float dx, float dy, float dz) {
  model_->translate(dx, dy, dz);
  emit ModelChanged();
}
void Controller::RotateX(float rad) {
  model_->rotateX(rad);
  emit ModelChanged();
}
void Controller::RotateY(float rad) {
  model_->rotateY(rad);
  emit ModelChanged();
}
void Controller::RotateZ(float rad) {
  model_->rotateZ(rad);
  emit ModelChanged();
}
void Controller::Scale(float sx, float sy, float sz) {
  model_->scale(sx, sy, sz);
  emit ModelChanged();
}

void Controller::SetTranslateAbs(float tx, float ty, float tz) {
  model_->setTranslation(tx, ty, tz);
  emit ModelChanged();
}
void Controller::SetRotateAbs(float rx, float ry, float rz) {
  model_->setRotation(rx, ry, rz);
  emit ModelChanged();
}
void Controller::SetScaleAbs(float s) {
  model_->setScale(s);
  emit ModelChanged();
}

}  // namespace s21
