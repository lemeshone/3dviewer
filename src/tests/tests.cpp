#include <gtest/gtest.h>

#include "../model/affineTransformer.h"
#include "../model/model.h"

TEST(Test, LoadFile) {
  s21::Model model;
  EXPECT_NO_THROW(model.loadFromFile("test_figure.obj"));
  EXPECT_TRUE(model.vertexCount() > 0);
  EXPECT_TRUE(model.edgeCount() > 0);
}

TEST(Test, LoadInvalidFile) {
  s21::Model model;
  EXPECT_THROW(model.loadFromFile("test_invalid.obj"), std::runtime_error);
}

TEST(Test, LoadNonExistenFile) {
  s21::Model model;
  EXPECT_THROW(model.loadFromFile("123.obj"), std::runtime_error);
}

TEST(Test, VertexCount) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");
  EXPECT_EQ(model.getVertices().size(), 8);
}

TEST(Test, EdgeCount) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");
  EXPECT_EQ(model.edgeCount(), 12);
}

TEST(Test, PolygonCount) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");
  EXPECT_EQ(model.getPolygons().size(), 6);
}

TEST(Test, NormalizeModel) {
  s21::Model model;
  model.getVertices().push_back({-0.001f, -0.002f, -0.003f});
  model.getVertices().push_back({0.001f, 0.002f, 0.003f});
  model.normalize();
  auto vertices = model.getVertices();
  for (const auto& vertex : vertices) {
    EXPECT_GE(vertex.x, -1.0f);
    EXPECT_LE(vertex.x, 1.0f);
    EXPECT_GE(vertex.y, -1.0f);
    EXPECT_LE(vertex.y, 1.0f);
    EXPECT_GE(vertex.z, -1.0f);
    EXPECT_LE(vertex.z, 1.0f);
  }

  float centerX = 0.f, centerY = 0.f, centerZ = 0.f;
  for (const auto& v : vertices) {
    centerX += v.x;
    centerY += v.y;
    centerZ += v.z;
  }
  centerX /= vertices.size();
  centerY /= vertices.size();
  centerZ /= vertices.size();

  EXPECT_NEAR(centerX, 0.0f, 1e-6);
  EXPECT_NEAR(centerY, 0.0f, 1e-6);
  EXPECT_NEAR(centerZ, 0.0f, 1e-6);
}

TEST(Test, RotationXOn90) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateX(M_PI_2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.x, 1e-6);
  EXPECT_NEAR(after.y, -before.z, 1e-6);
  EXPECT_NEAR(after.z, before.y, 1e-6);
}

TEST(Test, RotationYOn90) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateY(M_PI_2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.z, 1e-6);
  EXPECT_NEAR(after.y, before.y, 1e-6);
  EXPECT_NEAR(after.z, -before.x, 1e-6);
}

TEST(Test, RotationZOn90) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateZ(M_PI_2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, -before.y, 1e-6);
  EXPECT_NEAR(after.y, before.x, 1e-6);
  EXPECT_NEAR(after.z, before.z, 1e-6);
}

TEST(Test, RotationXOn180) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateX(M_PI);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.x, 1e-6);
  EXPECT_NEAR(after.y, -before.y, 1e-6);
  EXPECT_NEAR(after.z, -before.z, 1e-6);
}

TEST(Test, RotationYOn180) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateY(M_PI);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, -before.x, 1e-6);
  EXPECT_NEAR(after.y, before.y, 1e-6);
  EXPECT_NEAR(after.z, -before.z, 1e-6);
}

TEST(Test, RotationZOn180) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateZ(M_PI);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, -before.x, 1e-6);
  EXPECT_NEAR(after.y, -before.y, 1e-6);
  EXPECT_NEAR(after.z, before.z, 1e-6);
}

TEST(Test, RotationXOn360) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateX(M_PI * 2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.x, 1e-6);
  EXPECT_NEAR(after.y, before.z, 1e-6);
  EXPECT_NEAR(after.z, before.y, 1e-6);
}

TEST(Test, RotationYOn360) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateY(M_PI * 2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.z, 1e-6);
  EXPECT_NEAR(after.y, before.y, 1e-6);
  EXPECT_NEAR(after.z, before.x, 1e-6);
}

TEST(Test, RotationZOn360) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.rotateZ(M_PI * 2);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x, before.y, 1e-6);
  EXPECT_NEAR(after.y, before.x, 1e-6);
  EXPECT_NEAR(after.z, before.z, 1e-6);
}

TEST(Test, Translate) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.translate(1.0f, 2.0f, 4.0f);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x - before.x, 1.0, 1e-6);
  EXPECT_NEAR(after.y - before.y, 2.0, 1e-6);
  EXPECT_NEAR(after.z - before.z, 4.0, 1e-6);
}

TEST(Test, Translate2) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.translate(-3.0f, -8.0f, -1.0f);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x - before.x, -3.0, 1e-6);
  EXPECT_NEAR(after.y - before.y, -8.0, 1e-6);
  EXPECT_NEAR(after.z - before.z, -1.0, 1e-6);
}

TEST(Test, ScaleUp) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.scale(2.0f, 2.0f, 2.0f);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x / before.x, 2.0, 1e-6);
  EXPECT_NEAR(after.y / before.y, 2.0, 1e-6);
  EXPECT_NEAR(after.z / before.z, 2.0, 1e-6);
}

TEST(Test, ScaleDown) {
  s21::Model model;
  model.loadFromFile("test_figure.obj");

  auto before = model.getVertices()[0];
  model.scale(0.5f, 0.5f, 0.5f);
  auto after = model.getVertices()[0];
  EXPECT_NEAR(after.x / before.x, 0.5, 1e-6);
  EXPECT_NEAR(after.y / before.y, 0.5, 1e-6);
  EXPECT_NEAR(after.z / before.z, 0.5, 1e-6);
}