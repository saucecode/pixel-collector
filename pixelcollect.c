#include "pixelcollect.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Color pixel_at(unsigned char *data, int width, int height, int channels, int x, int y) {
	Color pixel = {
		data[(y*width + x)*channels],
		data[(y*width + x)*channels+1],
		data[(y*width + x)*channels+2]
	};
	return pixel;
}

#define shortcut(x, y) pixel_at(data, width, height, channels, (x), (y))

int already_collected(AABB *buffer, int buffer_size, int x, int y) {
	for(int i = 0; i < buffer_size; i++) {
		if( x >= buffer[i].left && y >= buffer[i].top && x < buffer[i].left + buffer[i].width && y < buffer[i].top + buffer[i].height )
			return 1;
	}
	return 0;
}

void collect_pixels(unsigned char *data, int width, int height, int channels, AABB **buffer_ptr, int *buffer_size, Color ignore) {
	// search for a non-white point
	// store the non-white color
	// search for AABBs that capture only the new color
	// store it in the list, and clear the rectangle in the data
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			Color pixel = shortcut(x, y);
			
			if(memcmp(&ignore, &pixel, sizeof(Color)) == 0) continue;
			
			if(already_collected(*buffer_ptr, *buffer_size, x,y)) continue;
			
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
				if(memcmp(&test, &box.color, sizeof(Color)) != 0) {
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
					if(memcmp(&query, &box.color, sizeof(Color)) != 0) goto query_exit;
				}
			}
			query_exit:
			
			box.height = by - box.top;
			
			*buffer_size += 1;
			*buffer_ptr = (AABB*) realloc(*buffer_ptr, (*buffer_size) * sizeof(AABB));
			(*buffer_ptr)[*buffer_size-1] = box;
		}
	}
}