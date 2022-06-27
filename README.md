# pixel-collector
Collects clumps of adjacent pixels into rectangles. This library easily drops into existing projects as a pair of header/source files.

The current implementation is in C++11 and requires `std::bind` and `std::vector`. Porting it to C is left as an exercise to the reader.

## Example usage

```cpp

#include "stb_image.h"

int main() {
    using namespace PixelCollector;

    int width, height, channels;
    unsigned char * data = stbi_load("sample.png", &width, &height, &channels, 3);

    std::vector<AABB> boxes;
    Color white = {255,255,255};
    collect(data, width, height, channels, boxes, white);
}
```

See `main.cpp` for more.

### Example input

![](https://raw.githubusercontent.com/saucecode/pixel-collector/master/sample.png)

A small PNG image, with regions of black, blue, and red. White will be ignored.

### Example output

In the format `{ (x, y), (width, height), color }`

```
AABB{ (2, 3), (106, 8), 0x000000 }
AABB{ (110, 3), (1, 56), 0x000000 }
AABB{ (7, 11), (12, 48), 0x000000 }
AABB{ (44, 28), (7, 9), 0x000000 }
AABB{ (51, 28), (7, 9), 0x0000ff }
AABB{ (44, 55), (15, 4), 0xff0000 }
AABB{ (7, 59), (7, 5), 0x000000 }
AABB{ (14, 59), (100, 4), 0x0000ff }
AABB{ (14, 63), (5, 1), 0x000000 }
AABB{ (44, 63), (15, 3), 0xff0000 }
AABB{ (110, 63), (1, 13), 0x000000 }
```

# License

MIT