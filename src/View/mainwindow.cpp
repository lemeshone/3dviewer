#include "mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSlider>
#include <cmath>

#include "Controller/controller.h"
#include "View/wireframewidget.h"
#include "ui_mainwindow.h"

namespace s21 {

static inline float DegToRadF(double deg) {
  return static_cast<float>(deg * M_PI / 180.0);
}

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      glview_(nullptr) {
  ui->setupUi(this);

  auto setMove = [](QSlider *s) {
    if (s) {
      s->setMinimum(-2000);
      s->setMaximum(2000);
      s->setSingleStep(1);
      s->setPageStep(5);
      s->setValue(0);
    }
  };
  setMove(ui->horizontalSlider);
  setMove(ui->horizontalSlider_2);
  setMove(ui->horizontalSlider_3);

  auto setRot = [](QSlider *s) {
    if (s) {
      s->setMinimum(-1800);
      s->setMaximum(1800);
      s->setSingleStep(1);
      s->setPageStep(5);
      s->setValue(0);
    }
  };
  setRot(ui->horizontalSlider_4);
  setRot(ui->horizontalSlider_5);
  setRot(ui->horizontalSlider_6);

  if (ui->horizontalSlider_7) {
    ui->horizontalSlider_7->setMinimum(10);
    ui->horizontalSlider_7->setMaximum(3000);
    ui->horizontalSlider_7->setSingleStep(1);
    ui->horizontalSlider_7->setPageStep(10);
    ui->horizontalSlider_7->setValue(100);
  }

  ui->openGLWidget->setModel(controller_->model());

  connect(ui->pushButtonOpenObj, &QPushButton::clicked, this,
          &MainWindow::OnOpenClicked);

  connect(controller_, &Controller::ModelLoaded, this,
          &MainWindow::OnModelLoaded);
  connect(controller_, &Controller::ModelLoadError, this,
          &MainWindow::OnModelError);
  connect(controller_, &Controller::ModelChanged, ui->openGLWidget,
          QOverload<>::of(&QOpenGLWidget::update));

  auto applyTranslate = [this] {
    const float tx =
        ui->horizontalSlider ? ui->horizontalSlider->value() / 100.0f : 0.f;
    const float ty =
        ui->horizontalSlider_2 ? ui->horizontalSlider_2->value() / 100.0f : 0.f;
    const float tz =
        ui->horizontalSlider_3 ? ui->horizontalSlider_3->value() / 100.0f : 0.f;
    controller_->SetTranslateAbs(tx, ty, tz);
  };
  if (ui->horizontalSlider)
    connect(ui->horizontalSlider, &QSlider::valueChanged, this,
            [applyTranslate](int) { applyTranslate(); });
  if (ui->horizontalSlider_2)
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, this,
            [applyTranslate](int) { applyTranslate(); });
  if (ui->horizontalSlider_3)
    connect(ui->horizontalSlider_3, &QSlider::valueChanged, this,
            [applyTranslate](int) { applyTranslate(); });

  auto applyRotate = [this] {
    auto val = [](QSlider *s) { return s ? s->value() * 0.1 : 0.0; };
    const float rx = DegToRadF(val(ui->horizontalSlider_4));
    const float ry = DegToRadF(val(ui->horizontalSlider_5));
    const float rz = DegToRadF(val(ui->horizontalSlider_6));
    controller_->SetRotateAbs(rx, ry, rz);
  };
  if (ui->horizontalSlider_4)
    connect(ui->horizontalSlider_4, &QSlider::valueChanged, this,
            [applyRotate](int) { applyRotate(); });
  if (ui->horizontalSlider_5)
    connect(ui->horizontalSlider_5, &QSlider::valueChanged, this,
            [applyRotate](int) { applyRotate(); });
  if (ui->horizontalSlider_6)
    connect(ui->horizontalSlider_6, &QSlider::valueChanged, this,
            [applyRotate](int) { applyRotate(); });

  if (ui->horizontalSlider_7) {
    connect(ui->horizontalSlider_7, &QSlider::valueChanged, this,
            [this](int v) {
              const float s = (v == 0 ? 1 : v) / 100.0f;
              controller_->SetScaleAbs(s);
            });
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::OnOpenClicked() {
  const QString file =
      QFileDialog::getOpenFileName(this, "Open OBJ", {}, "OBJ Files (*.obj)");
  if (file.isEmpty()) return;
  ui->label->setText(QFileInfo(file).fileName());
  controller_->LoadModel(file);

  auto reset = [](QSlider *s, int v) {
    if (!s) return;
    s->blockSignals(true);
    s->setValue(v);
    s->blockSignals(false);
  };
  reset(ui->horizontalSlider, 0);
  reset(ui->horizontalSlider_2, 0);
  reset(ui->horizontalSlider_3, 0);
  reset(ui->horizontalSlider_4, 0);
  reset(ui->horizontalSlider_5, 0);
  reset(ui->horizontalSlider_6, 0);
  reset(ui->horizontalSlider_7, 100);
}

void MainWindow::OnModelLoaded(size_t v, size_t e) {
  ui->label_11->setText(QString::number(v));
  ui->label_12->setText(QString::number(e));
}

void MainWindow::OnModelError(const QString &msg) {
  QMessageBox::warning(this, "Load error", msg);
}

}  // namespace s21
