#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "model/model.h"

namespace s21 {

class WireframeWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit WireframeWidget(QWidget *parent = nullptr);
  void setModel(Model *m);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  Model *model_ = nullptr;
};

}  // namespace s21