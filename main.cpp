#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "PixelCollector.hpp"

#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& stream, const PixelCollector::AABB& box) {
	using namespace std;
	stream << "AABB{ ("
	       << box.left << ", " << box.top << "), ("
	       << box.width << ", " << box.height << "), 0x"
	       << setfill('0') << setw(2) << hex << (int) box.color.red
	       << setfill('0') << setw(2) << hex << (int) box.color.green
	       << setfill('0') << setw(2) << hex << (int) box.color.blue
	       << " }";
	return stream;
}

int main() {
	using namespace PixelCollector;
	
	int width, height, channels;
	unsigned char * data = stbi_load("sample.png", &width, &height, &channels, 3);
	
	std::vector<AABB> boxes;
	Color white = {255,255,255};
	collect(data, width, height, channels, boxes, white);
	
	for(AABB& box : boxes) std::cout << box << "\n";
}