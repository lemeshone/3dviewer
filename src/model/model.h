#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "affineTransformer.h"

namespace s21 {

struct Vertex {
  float x, y, z;
};
struct Polygon {
  std::vector<unsigned int> vertexIndices;
};

struct Transform {
  float tx{0.f}, ty{0.f}, tz{0.f};
  float rx{0.f}, ry{0.f}, rz{0.f};
  float s{1.f};
};

class Model {
 public:
  Model() = default;

  void loadFromFile(const std::string &filename);
  void parseVertex(const std::string &line);
  void parsePolygon(const std::string &line);
  void normalize();

  void translate(float dx, float dy, float dz);
  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);
  void scale(float sx, float sy, float sz);

  void setTranslation(float tx, float ty, float tz);
  void setRotation(float rx, float ry, float rz);
  void setScale(float s);

  std::vector<Vertex> &getVertices();
  std::vector<Polygon> &getPolygons();
  size_t vertexCount() const;
  size_t edgeCount() const;
  void clear();

 private:
  void rebuildFromTransform();
  Vertex centerOfOriginal() const;

  AffineTransformer transformer_;
  std::vector<Vertex> vertices_;
  std::vector<Vertex> originalVertices_;
  std::vector<Polygon> polygons_;
  std::string filename_;
  Transform current_{};
};

}  // namespace s21
