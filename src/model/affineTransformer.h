#pragma once

#include <array>
#include <cmath>

namespace s21 {

struct Vertex;

class AffineTransformer {
 public:
  using Matrix = std::array<std::array<float, 4>, 4>;

  AffineTransformer();

  void multiplication(const Matrix &other);
  void translate(float dx, float dy, float dz);
  void scale(float sx, float sy, float sz);
  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);
  void applyToVertex(Vertex &ver);
  void resetMatrix();

 private:
  Matrix matrix_;
};

}  // namespace s21