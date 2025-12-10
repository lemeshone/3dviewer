#include "wireframewidget.h"

namespace s21 {

WireframeWidget::WireframeWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void WireframeWidget::setModel(Model* m) {
  model_ = m;
  update();
}

void WireframeWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void WireframeWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void WireframeWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!model_) return;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -10, 10);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  const auto& verts = model_->getVertices();
  const auto& polys = model_->getPolygons();

  glColor3f(0.9f, 0.9f, 0.9f);
  glLineWidth(1.0f);

  for (const auto& p : polys) {
    if (p.vertexIndices.size() < 2) continue;
    glBegin(GL_LINES);
    for (size_t i = 0; i < p.vertexIndices.size(); ++i) {
      unsigned a = p.vertexIndices[i];
      unsigned b = p.vertexIndices[(i + 1) % p.vertexIndices.size()];
      const auto& va = verts[a];
      const auto& vb = verts[b];
      glVertex3f(va.x, va.y, va.z);
      glVertex3f(vb.x, vb.y, vb.z);
    }
    glEnd();
  }
}

}  // namespace s21