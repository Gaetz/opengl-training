#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "../engine/maths/Matrix4.h"

class Shader;
class CubeMesh;

class CubeObject {
public:
  CubeObject(float xP, float yP, CubeMesh* cubeMeshP);

  void update();
  void draw(Shader& shader);

  float getX() const { return x; }
  float getY() const { return y; }
  void setPosition(float xP, float yP);
  Matrix4 computeTransform();

private:
  float x { 0.0f };
  float y { 0.0f };
  Matrix4 transform {};

  CubeMesh* cubeMesh { nullptr };
};

#endif