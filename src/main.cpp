#include <QApplication>

#include "Controller/controller.h"
#include "View/mainwindow.h"
#include "model/model.h"

int main(int argc, char *argv[]) {
  QSurfaceFormat fmt;
  fmt.setRenderableType(QSurfaceFormat::OpenGL);
  fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
  fmt.setVersion(2, 1);
  QSurfaceFormat::setDefaultFormat(fmt);

  QApplication app(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::MainWindow w(&controller);

  w.show();
  return app.exec();
}