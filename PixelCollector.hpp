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

#pragma once

#include <vector>

namespace PixelCollector {

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;

typedef struct {
	int left; int top; int width; int height;
	Color color;
} AABB;

bool operator==(Color left, Color right);
bool operator!=(Color left, Color right);

/*
	Collect pixels from image data into AABBs, ignoring the `ignore` color.
	
	Designed to be used in conjunction with stb_image.h, but will work as long
	as you can provide the correct parameters.
	
	Currently only works with 3-channel (RGB) images.
	
	For example usage, see main.cpp.
*/
void collect(unsigned char *data, int width, int height, int channels, std::vector<AABB> &boxes, Color ignore);

};