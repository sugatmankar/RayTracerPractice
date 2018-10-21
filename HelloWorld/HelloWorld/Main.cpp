#include <stdio.h>
#include <iostream>

#ifndef STBI_MSC_SECURE_CRT
#define STBI_MSC_SECURE_CRT
#endif // !STBI_MSC_SECURE_CRT

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION


#include "stb_image.h"
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include "vec3.h"

int main(void) {

	void HelloSTBPNGCheckerBoard(const char* fileName, int nx, int ny);

	void HelloSTBPNGSimple(const char* fileName, int nx, int ny);

	void HelloSTBPNGVec3(const char* fileName, int nx, int ny);

	int nx = 64;
	int ny = 64;

	//HelloSTBPNGCheckerBoard("bar_out.png", 64, 64);
	
	//HelloSTBPNGSimple("foo_bar.png",128,128);
	
	HelloSTBPNGVec3("foo_bar.png", 256, 256);

	return 0;
}


void HelloSTBPNGVec3(const char* fileName, int nx, int ny) {

	unsigned char* data = NULL;

	data = (unsigned char*)malloc(3 * nx * ny); // 3 for x y z

	memset(data,//dst
		0, //val
		3 * nx * ny //size_t
	);

	for (int j = 0; j < ny - 1; j++) {
		for (int i = 0; i < nx; i++) {
			/* without vec3
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2; */
			/*without vec3
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			*/
			vec3 color(float(i)/float(nx),float(j)/float(ny),0.2);

			data[(i + j * nx) * 3 + 0] = int(255.99* color[0]);
			data[(i + j * nx) * 3 + 1] = int(255.99* color[1]);
			data[(i + j * nx) * 3 + 2] = int(255.99* color[2]);
		}
	}

	stbi_write_png(fileName, nx, ny, 3, data, 0);

	free(data);
}

void HelloSTBPNGSimple(const char* fileName, int nx, int ny) {

	unsigned char* data = NULL;

	data = (unsigned char*)malloc(3 * nx * ny); // 3 for x y z

	memset(data,//dst
		0, //val
		3 * nx * ny //size_t
	);

	for (int j = 0; j < ny - 1; j++) {
		for (int i = 0; i < nx; i++) {
			// without vec3
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			//without vec3
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);

			data[(i + j * nx) * 3 + 0] = ir;
			data[(i + j * nx) * 3 + 1] = ig;
			data[(i + j * nx) * 3 + 2] = ib;
		}
	}

	stbi_write_png(fileName, nx, ny, 3, data, 0);

	free(data);
}

void HelloSTBPNGCheckerBoard(const char* fileName, int nx, int ny) {

	unsigned char* data = NULL;

	data = (unsigned char*)malloc(3 * nx * ny); // 3 for x y z

	memset(data,//dst
		0, //val
		3 * nx * ny //size_t
	);

	int c = 0;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {

			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;

			data[(i + j * nx) * 3 + 0] = (unsigned char)(c);
			data[(i + j * nx) * 3 + 1] = (unsigned char)(c);
			data[(i + j * nx) * 3 + 2] = (unsigned char)(c);
		}
	}

	stbi_write_png(fileName, nx, ny, 3, data, 0);

	free(data);
}