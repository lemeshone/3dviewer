#include "affineTransformer.h"

#include "model.h"

namespace s21 {

AffineTransformer::AffineTransformer() { resetMatrix(); }

void AffineTransformer::multiplication(const Matrix &other) {
  Matrix res{};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      res[i][j] = 0.0f;
      for (int k = 0; k < 4; k++) {
        res[i][j] += matrix_[i][k] * other[k][j];
      }
    }
  }
  matrix_ = res;
}

void AffineTransformer::translate(float dx, float dy, float dz) {
  Matrix transMatrix = {
      {{1, 0, 0, dx}, {0, 1, 0, dy}, {0, 0, 1, dz}, {0, 0, 0, 1}}};

  multiplication(transMatrix);
}

void AffineTransformer::scale(float sx, float sy, float sz) {
  Matrix scaleMatrix = {
      {{sx, 0, 0, 0}, {0, sy, 0, 0}, {0, 0, sz, 0}, {0, 0, 0, 1}}};

  multiplication(scaleMatrix);
}

void AffineTransformer::rotateX(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  Matrix rotateMatrix = {
      {{1, 0, 0, 0}, {0, c, -s, 0}, {0, s, c, 0}, {0, 0, 0, 1}}};

  multiplication(rotateMatrix);
}

void AffineTransformer::rotateY(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  Matrix rotateMatrix = {
      {{c, 0, s, 0}, {0, 1, 0, 0}, {-s, 0, c, 0}, {0, 0, 0, 1}}};

  multiplication(rotateMatrix);
}

void AffineTransformer::rotateZ(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  Matrix rotateMatrix = {
      {{c, -s, 0, 0}, {s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};

  multiplication(rotateMatrix);
}

void AffineTransformer::applyToVertex(Vertex &vertex) {
  float x = vertex.x;
  float y = vertex.y;
  float z = vertex.z;

  vertex.x =
      matrix_[0][0] * x + matrix_[0][1] * y + matrix_[0][2] * z + matrix_[0][3];
  vertex.y =
      matrix_[1][0] * x + matrix_[1][1] * y + matrix_[1][2] * z + matrix_[1][3];
  vertex.z =
      matrix_[2][0] * x + matrix_[2][1] * y + matrix_[2][2] * z + matrix_[2][3];
}

void AffineTransformer::resetMatrix() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}

}  // namespace s21