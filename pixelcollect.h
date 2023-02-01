#ifndef sxde_pixcollect_H
#define sxde_pixcollect_H

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;

typedef struct {
	int left; int top; int width; int height;
	Color color;
} AABB;

void collect_pixels(unsigned char *data, int width, int height, int channels, AABB **buffer_ptr, int *buffer_size, Color ignore);

#endif
