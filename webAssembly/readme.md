> source /Users/dushi/Documents/c++/emsdk/emsdk_env.sh

#### Vector3
```js
emcc --bind -o build/Vector3.js Vector3.cpp -I "/usr/local/include/eigen3/" -std=c++17
```
#include <emscripten/bind.h>
EMSCRIPTEN_BINDINGS(my_class_example)
{
  emscripten::class_<Vector3>("Vector3")
      .constructor<int, std::string>()
      .function("incrementX", &Vector3::incrementX)
      .property("x", &Vector3::getX, &Vector3::setX);
}

