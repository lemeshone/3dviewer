#include "model.h"

namespace s21 {

void Model::loadFromFile(const std::string &filename) {
  clear();
  filename_ = filename;

  std::ifstream file(filename);
  if (!file.is_open())
    throw std::runtime_error("Cannot open file: " + filename);

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    if (prefix == "v")
      parseVertex(line);
    else if (prefix == "f")
      parsePolygon(line);
  }
  if (!vertices_.empty()) normalize();

  originalVertices_ = vertices_;
  current_ = Transform{};
  rebuildFromTransform();
}

void Model::parseVertex(const std::string &line) {
  std::istringstream iss(line);
  std::string prefix;
  iss >> prefix;
  Vertex v{};
  if (iss >> v.x >> v.y >> v.z)
    vertices_.push_back(v);
  else
    throw std::runtime_error("Invalid vertex line: " + line);
}

void Model::parsePolygon(const std::string &line) {
  std::istringstream iss(line);
  std::string prefix;
  iss >> prefix;

  Polygon polygon;
  std::string token;
  while (iss >> token) {
    size_t pos = token.find('/');
    if (pos != std::string::npos) token = token.substr(0, pos);
    unsigned idx = static_cast<unsigned>(std::stoul(token));
    polygon.vertexIndices.push_back(idx - 1);
  }

  if (polygon.vertexIndices.size() >= 3) {
    polygons_.push_back(std::move(polygon));
  } else {
    throw std::runtime_error("Invalid polygon (less than 3 vertices): " + line);
  }
}

void Model::normalize() {
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float minZ = std::numeric_limits<float>::max();
  float maxX = std::numeric_limits<float>::lowest();
  float maxY = std::numeric_limits<float>::lowest();
  float maxZ = std::numeric_limits<float>::lowest();

  for (const auto &v : vertices_) {
    minX = std::min(minX, v.x);
    minY = std::min(minY, v.y);
    minZ = std::min(minZ, v.z);
    maxX = std::max(maxX, v.x);
    maxY = std::max(maxY, v.y);
    maxZ = std::max(maxZ, v.z);
  }

  float scale = std::max({maxX - minX, maxY - minY, maxZ - minZ});
  if (scale == 0.f) scale = 1.f;

  float cx = (maxX + minX) * 0.5f;
  float cy = (maxY + minY) * 0.5f;
  float cz = (maxZ + minZ) * 0.5f;

  for (auto &v : vertices_) {
    v.x = (v.x - cx) / scale;
    v.y = (v.y - cy) / scale;
    v.z = (v.z - cz) / scale;
  }
}

void Model::translate(float dx, float dy, float dz) {
  current_.tx += dx;
  current_.ty += dy;
  current_.tz += dz;
  rebuildFromTransform();
}
void Model::rotateX(float angle) {
  current_.rx += angle;
  rebuildFromTransform();
}
void Model::rotateY(float angle) {
  current_.ry += angle;
  rebuildFromTransform();
}
void Model::rotateZ(float angle) {
  current_.rz += angle;
  rebuildFromTransform();
}
void Model::scale(float sx, float sy, float sz) {
  (void)sy;
  (void)sz;
  current_.s *= sx;
  if (current_.s <= 0.f) current_.s = 1.f;
  rebuildFromTransform();
}

void Model::setTranslation(float tx, float ty, float tz) {
  current_.tx = tx;
  current_.ty = ty;
  current_.tz = tz;
  rebuildFromTransform();
}
void Model::setRotation(float rx, float ry, float rz) {
  current_.rx = rx;
  current_.ry = ry;
  current_.rz = rz;
  rebuildFromTransform();
}
void Model::setScale(float s) {
  current_.s = (s > 0.f ? s : 1.f);
  rebuildFromTransform();
}

Vertex Model::centerOfOriginal() const {
  Vertex c{0.f, 0.f, 0.f};
  if (originalVertices_.empty()) return c;
  for (const auto &v : originalVertices_) {
    c.x += v.x;
    c.y += v.y;
    c.z += v.z;
  }
  float inv = 1.f / static_cast<float>(originalVertices_.size());
  c.x *= inv;
  c.y *= inv;
  c.z *= inv;
  return c;
}

void Model::rebuildFromTransform() {
  transformer_.resetMatrix();
  const Vertex c = centerOfOriginal();

  transformer_.translate(current_.tx, current_.ty, current_.tz);
  transformer_.translate(c.x, c.y, c.z);
  transformer_.rotateZ(current_.rz);
  transformer_.rotateY(current_.ry);
  transformer_.rotateX(current_.rx);
  transformer_.scale(current_.s, current_.s, current_.s);
  transformer_.translate(-c.x, -c.y, -c.z);

  vertices_ = originalVertices_;
  for (auto &v : vertices_) transformer_.applyToVertex(v);

  transformer_.resetMatrix();
}
std::vector<Vertex> &Model::getVertices() { return vertices_; }
std::vector<Polygon> &Model::getPolygons() { return polygons_; }

size_t Model::vertexCount() const { return vertices_.size(); }

size_t Model::edgeCount() const {
  size_t edges = 0;
  for (const auto &p : polygons_) edges += p.vertexIndices.size();
  return edges / 2;
}

void Model::clear() {
  vertices_.clear();
  originalVertices_.clear();
  polygons_.clear();
  current_ = Transform{};
}

}  // namespace s21