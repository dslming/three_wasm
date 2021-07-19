// #include <Eigen/Core>
#include <iostream>
#include <cmath>
using namespace std;
float PI = 3.1415926;

namespace THREE {
  class Attribute  {
    public:
      float x;
      float y;
      float z;
      float getX(int index)
      {
        return x;
      }
      float getY(int index)
      {
        return x;
      }
      float getZ(int index)
      {
        return x;
      }
  };
  class Q
  {
  public:
    float x;
    float y;
    float z;
    float w;
  };
  class Matrial4
  {
  public:
    float elements[16];
  };

  class Camera
  {
  public:
    Matrial4 matrixWorldInverse;
    Matrial4 projectionMatrix;
    Matrial4 projectionMatrixInverse;
    Matrial4 matrixWorld;
  };

  class Vector3
  {
  public:
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3 set(float _x, float _y, float _z)
    {
      x = _x;
      y = _y;
      z = _z;
      return *this;
    }

    Vector3 setScalar(float scalar)
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    Vector3 setX(float _x)
    {
      x = x;
      return *this;
    }

    Vector3 setY(float _y)
    {
      y = _y;
      return *this;
    }

    Vector3 setZ(float _z)
    {
      z = _z;
      return *this;
    }

    Vector3 setComponent(int index, float value)
    {
      switch (index)
      {
      case 0:
        x = value;
        break;
      case 1:
        y = value;
        break;
      case 2:
        z = value;
        break;
      default:
        cout << "index is out of range:" << index << endl;
      }

      return *this;
    }

    float getComponent(int index)
    {
      switch (index)
      {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        cout << "index is out of range:" << index << endl;
      }
    }

    Vector3 clone(void)
    {
      return Vector3(x, y, z);
    }

    Vector3 copy(Vector3 v)
    {
      x = v.x;
      y = v.y;
      z = v.z;
      return *this;
    }

    Vector3 add(Vector3 v)
    {
      x += v.x;
      y += v.y;
      z += v.z;
      return *this;
    }

    Vector3 addScalar(float s)
    {
      x += s;
      y += s;
      z += s;
      return *this;
    }

    Vector3 addVectors(Vector3 a, Vector3 b)
    {
      x = a.x + b.x;
      y = a.y + b.y;
      z = a.z + b.z;
      return *this;
    }

    Vector3 addScaledVector(Vector3 v, float s)
    {
      x += v.x * s;
      y += v.y * s;
      z += v.z * s;
      return *this;
    }

    Vector3 sub(Vector3 v)
    {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return *this;
    }

    Vector3 subScalar(float s)
    {

      x -= s;
      y -= s;
      z -= s;

      return *this;
    }

    Vector3 subVectors(Vector3 a, Vector3 b)
    {
      x = a.x - b.x;
      y = a.y - b.y;
      z = a.z - b.z;
      return *this;
    }

    Vector3 multiply(Vector3 v)
    {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      return *this;
    }

    Vector3 multiplyScalar(float scalar)
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    Vector3 multiplyVectors(Vector3 a, Vector3 b)
    {

      x = a.x * b.x;
      y = a.y * b.y;
      z = a.z * b.z;

      return *this;
    }

    Vector3 applyMatrix3(Matrial4 m)
    {
      float _x = x;
      float _y = y;
      float _z = z;
      auto e = m.elements;

      x = e[0] * _x + e[3] * _y + e[6] * _z;
      y = e[1] * _x + e[4] * _y + e[7] * _z;
      z = e[2] * _x + e[5] * _y + e[8] * _z;
      return *this;
    }

    Vector3 applyNormalMatrix(Matrial4 m)
    {
      return applyMatrix3(m).normalize();
    }

    Vector3 applyMatrix4(Matrial4 m)
    {

      auto x = this->x, y = this->y, z = this->z;
      auto e = m.elements;

      auto w = 1 / (e[3] * x + e[7] * y + e[11] * z + e[15]);

      x = (e[0] * x + e[4] * y + e[8] * z + e[12]) * w;
      y = (e[1] * x + e[5] * y + e[9] * z + e[13]) * w;
      z = (e[2] * x + e[6] * y + e[10] * z + e[14]) * w;
      return *this;
    }

    Vector3 applyQuaternion(Q q)
    {

      auto x = this->x, y = this->y, z = this->z;
      auto qx = q.x, qy = q.y, qz = q.z, qw = q.w;

      // calculate quat * vector
      auto ix = qw * x + qy * z - qz * y;
      auto iy = qw * y + qz * x - qx * z;
      auto iz = qw * z + qx * y - qy * x;
      auto iw = -qx * x - qy * y - qz * z;

      // calculate result * inverse quat
      x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
      y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
      z = iz * qw + iw * -qz + ix * -qy - iy * -qx;

      return *this;
    }

    Vector3 project(Camera camera)
    {

      return applyMatrix4(camera.matrixWorldInverse).applyMatrix4(camera.projectionMatrix);
    }

    Vector3 unproject(Camera camera)
    {

      return applyMatrix4(camera.projectionMatrixInverse).applyMatrix4(camera.matrixWorld);
    }

    Vector3 transformDirection(Matrial4 m)
    {

      // input: THREE.Matrix4 affine matrix
      // vector interpreted as a direction

      auto x = this->x, y = this->y, z = this->z;
      auto e = m.elements;

      x = e[0] * x + e[4] * y + e[8] * z;
      y = e[1] * x + e[5] * y + e[9] * z;
      z = e[2] * x + e[6] * y + e[10] * z;
      return this->normalize();
    }

    Vector3 divide(Vector3 v)
    {

      x /= v.x;
      y /= v.y;
      z /= v.z;

      return *this;
    }

    Vector3 divideScalar(float scalar)
    {

      return multiplyScalar(1 / scalar);
    }

    Vector3 min(Vector3 v)
    {

      x = std::min(x, v.x);
      y = std::min(y, v.y);
      z = std::min(z, v.z);

      return *this;
    }

    Vector3 max(Vector3 v)
    {

      x = std::max(x, v.x);
      y = std::max(y, v.y);
      z = std::max(z, v.z);

      return *this;
    }

    Vector3 clamp(Vector3 min, Vector3 max)
    {

      // assumes min < max, componentwise

      x = std::max(min.x, std::min(max.x, x));
      y = std::max(min.y, std::min(max.y, y));
      z = std::max(min.z, std::min(max.z, z));

      return *this;
    }

    Vector3 clampScalar(float minVal, float maxVal)
    {

      x = std::max(minVal, std::min(maxVal, x));
      y = std::max(minVal, std::min(maxVal, y));
      z = std::max(minVal, std::min(maxVal, z));

      return *this;
    }

    Vector3 clampLength(float min, float max)
    {

      auto length = this->length();
      return divideScalar(length || 1).multiplyScalar(std::max(min, std::min(max, length)));
    }

    Vector3 floor()
    {

      x = std::floor(x);
      y = std::floor(y);
      z = std::floor(z);

      return *this;
    }

    Vector3 ceil()
    {

      x = std::ceil(x);
      y = std::ceil(y);
      z = std::ceil(z);

      return *this;
    }

    Vector3 round()
    {

      x = std::round(x);
      y = std::round(y);
      z = std::round(z);

      return *this;
    }

    Vector3 roundToZero()
    {

      x = (x < 0) ? std::ceil(x) : std::floor(x);
      y = (y < 0) ? std::ceil(y) : std::floor(y);
      z = (z < 0) ? std::ceil(z) : std::floor(z);

      return *this;
    }

    Vector3 negate()
    {

      x = -x;
      y = -y;
      z = -z;

      return *this;
    }

    float dot(Vector3 v)
    {

      return x * v.x + y * v.y + z * v.z;
    }

    float lengthSq()
    {

      return x * x + y * y + z * z;
    }

    float length()
    {

      return sqrt(x * x + y * y + z * z);
    }

    float manhattanLength()
    {

      return abs(x) + abs(y) + abs(z);
    }

    Vector3 normalize()
    {

      return divideScalar(length() || 1);
    }

    Vector3 setLength(float length)
    {

      return normalize().multiplyScalar(length);
    }

    Vector3 lerp(Vector3 v, float alpha)
    {

      x += (v.x - x) * alpha;
      y += (v.y - y) * alpha;
      z += (v.z - z) * alpha;
      return *this;
    }

    Vector3 lerpVectors(Vector3 v1, Vector3 v2, float alpha)
    {

      x = v1.x + (v2.x - v1.x) * alpha;
      y = v1.y + (v2.y - v1.y) * alpha;
      z = v1.z + (v2.z - v1.z) * alpha;

      return *this;
    }

    Vector3 cross(Vector3 v)
    {
      return crossVectors(*this, v);
    }

    Vector3 crossVectors(Vector3 a, Vector3 b)
    {

      auto ax = a.x, ay = a.y, az = a.z;
      auto bx = b.x, by = b.y, bz = b.z;

      x = ay * bz - az * by;
      y = az * bx - ax * bz;
      z = ax * by - ay * bx;

      return *this;
    }

    Vector3 projectOnVector(Vector3 v)
    {

      auto denominator = v.lengthSq();

      if (denominator == 0)
        return this->set(0, 0, 0);

      auto scalar = v.dot(*this) / denominator;

      return this->copy(v).multiplyScalar(scalar);
    }

    float angleTo(Vector3 v)
    {
      auto denominator = sqrt(this->lengthSq() * v.lengthSq());

      if (denominator == 0)
        return PI / 2;

      auto theta = this->dot(v) / denominator;

      // clamp, to handle numerical problems

      // return acos(MathUtils.clamp(theta, -1, 1));
    }

    float distanceTo(Vector3 v)
    {

      return sqrt(this->distanceToSquared(v));
    }

    float distanceToSquared(Vector3 v)
    {

      auto dx = x - v.x, dy = y - v.y, dz = z - v.z;

      return dx * dx + dy * dy + dz * dz;
    }

    float manhattanDistanceTo(Vector3 v)
    {

      return abs(x - v.x) + abs(y - v.y) + abs(z - v.z);
    }

    Vector3 setFromMatrixPosition(Matrial4 m)
    {

      auto e = m.elements;
      this->x = e[12];
      this->y = e[13];
      this->z = e[14];

      return * this;
    }


    Vector3 setFromMatrixColumn(Matrial4 m, int index)
    {
      return this->fromArray(m.elements, index * 4);
    }

    Vector3 setFromMatrix3Column(Matrial4 m, int index)
    {
      return this->fromArray(m.elements, index * 3);
    }

    bool equals(Vector3 v)
    {
      return ((v.x == this->x) && (v.y == this->y) && (v.z == this->z));
    }

    Vector3 fromArray(float array[], int offset = 0)
    {
      this->x = array[offset];
      this->y = array[offset + 1];
      this->z = array[offset + 2];

      return *this;
    }

    float * toArray(float array[], int offset = 0)
    {

      array[offset] = this->x;
      array[offset + 1] = this->y;
      array[offset + 2] = this->z;

      return array;
    }

    Vector3 fromBufferAttribute(Attribute attribute, int index)
    {
      this->x = attribute.getX(index);
      this->y = attribute.getY(index);
      this->z = attribute.getZ(index);

      return * this;
    }

  public:
    float x;
    float y;
    float z;
  };
}


int main()
{
  THREE::Vector3 a(1, 2, 3);
  THREE::Vector3 b(4, 5, 6);
  a.add(b);
  cout << a.x << endl;
  return 0;
}
