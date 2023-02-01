#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "pixelcollect.h"
#include <stdio.h>

int color_format(Color c) {
	return c.red << 16 | c.green << 8 | c.blue;
}

int main() {
	assert(sizeof(Color) == 3*sizeof(unsigned char));
	int width, height, channels;
	unsigned char * data = stbi_load("sample.png", &width, &height, &channels, 3);
	
	AABB *boxes = NULL;
	int buffer_size = 0;
	
	Color white = {255,255,255};
	collect_pixels(data, width, height, channels, &boxes, &buffer_size, white);
	
	for(int i = 0; i < buffer_size; i++) {
		printf("AABB{ (%d, %d), (%d, %d), 0x%06x }\n", boxes[i].left, boxes[i].top, boxes[i].width, boxes[i].height, color_format(boxes[i].color));
	}
}