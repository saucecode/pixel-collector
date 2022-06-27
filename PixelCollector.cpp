/*
	MIT License

	Copyright (c) 2022 Julian Cahill <cahill.juilan@gmail.com>

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/


#include "PixelCollector.hpp"

#include <vector>
#include <functional>

namespace PixelCollector {

bool operator==(Color left, Color right) {
	return left.red == right.red && left.green == right.green && left.blue == right.blue;
}

bool operator!=(Color left, Color right) {
	return !(left == right);
}

bool already_collected(const std::vector<AABB> &boxes, int x, int y) {
	for(const AABB &box : boxes) {
		if( x >= box.left && y >= box.top && x < box.left + box.width && y < box.top + box.height )
			return true; 
	}
	return false;
}

Color pixel_at(unsigned char *data, int width, int height, int channels, int x, int y) {
	Color pixel = {
			data[(y*width + x)*channels],
			data[(y*width + x)*channels+1],
			data[(y*width + x)*channels+2]
		};
	return pixel;
}

void collect(unsigned char *data, int width, int height, int channels, std::vector<AABB> &boxes, Color ignore) {
	
	// search for a non-white point
	// store the non-white color
	// search for AABBs that capture only the new color
	// store it in the list, and clear the rectangle in the data
	
	auto shortcut = std::bind(pixel_at, data, width, height, channels, std::placeholders::_1, std::placeholders::_2);
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			Color pixel = shortcut(x, y);
			
			if(pixel == ignore) continue;
			
			if(already_collected(boxes, x,y)) continue;
			
			AABB box;
			box.color = pixel;
			box.left = x;
			box.top = y;
			box.height = 1;
			box.width = 1;
			
			// traverse right until running out
			int bx;
			for(bx = box.left+1; bx < width; bx++) {
				Color test = shortcut(bx, box.top);
				if(test != box.color) {
					break;
				}
			}
			box.width = bx - box.left;
			
			// extend vertically until it fails to capture
			int by;
			for(by = box.top+1; by < height; by++) {
				// check all pixels on this row, and jump out if
				// any of the pixels do not match
				for(int qx = box.left; qx < box.left + box.width; qx++) {
					Color query = shortcut(qx, by);
					if(query != box.color) goto query_exit;
				}
			}
			query_exit:
			
			box.height = by - box.top;
			
			boxes.push_back(box);
		}
	}
}



}