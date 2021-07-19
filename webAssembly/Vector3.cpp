#include <Eigen/Core>
#include <iostream>
using namespace std;

int main() {
  return 0;
}
class Vector3;

class Vector3
{
public:
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3 set(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    return *this;
  }

  Vector3 setScalar(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  Vector3 setX(float _x) {
    x = x;
    return *this;
  }

  Vector3 setY(float _y){
    y = _y;
    return *this;
  }

  Vector3 setZ(float _z){
    z = _z;
    return *this;
  }

  Vector3 setComponent(int index, float value)
  {
    switch (index) {
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
      cout<<"index is out of range:" << index<<endl;
    }

    return * this;
  }

  float getComponent(int index)
  {
    switch (index) {
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
    return * this;
  }

  add(v, w)
  {

    if (w != = undefined)
    {

      console.warn('THREE.Vector3: .add() now only accepts one argument. Use .addVectors( a, b ) instead.');
      return this.addVectors(v, w);
    }

    this.x += v.x;
    this.y += v.y;
    this.z += v.z;

    return this;
  }

private:
  float x;
  float y;
  float z;
};
