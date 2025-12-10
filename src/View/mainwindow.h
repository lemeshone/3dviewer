#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSlider;

#include "Controller/controller.h"
#include "View/wireframewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void OnOpenClicked();
  void OnModelLoaded(size_t v, size_t e);
  void OnModelError(const QString &msg);

 private:
  void InitSlider(QSlider *s);
  void OnMoveChanged(QSlider *s, int axis, int value);
  void OnRotateChanged(QSlider *s, void (s21::Controller::*rotFn)(float),
                       int value);
  void OnScaleChanged(int value);

 private:
  Ui::MainWindow *ui = nullptr;
  s21::Controller *controller_ = nullptr;
  s21::WireframeWidget *glview_ = nullptr;
};

}  // namespace s21

#endif
