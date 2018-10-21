#include <stdio.h>
#include <iostream>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {

	void HelloPPM(const char* fileName,int nx,int ny);
	void HelloPPMCheckerBoard(const char* fileName, int nx, int ny);

	void HelloBMPCheckerBoard(const char* fileName, int nx, int ny);

	void HelloSTBPNGCheckerBoard(const char* fileName, int nx, int ny);

	int nx = 64;
	int ny = 64;
	
	//using naked code
	HelloPPM("Hello.ppm",nx,ny);
	HelloPPMCheckerBoard("checker.ppm", nx, ny);
	HelloBMPCheckerBoard("checker.bmp", nx, ny);
	//HelloBMPCheckerBoard("checker.bmp", nx, ny);
	//using stb image write
	int x,y,n;
	unsigned char* data = stbi_load("checker.bmp",&x,&y,&n,0);
	stbi_write_png("foo_out.png",x,y,3,data,0);
	
	HelloSTBPNGCheckerBoard("bar_out.png", 64, 64);

	return 0;
}

void HelloSTBPNGCheckerBoard(const char* fileName, int nx, int ny) {
	
	unsigned char* data = NULL;

	data = (unsigned char*)malloc(3 * nx * ny); // 3 for x y z

	memset(data,//dst
			0 , //val
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
}

void HelloPPM(const char* fileName,int nx,int ny) {
	
	FILE *gpFile = NULL;
	if (fopen_s(&gpFile, fileName, "w")) {
		std::cout << "File can't created \n" << std::endl;
		exit(0);
	}
	else {
		std::cout << "File created successfully " << std::endl;
	}

	fprintf(gpFile, "P3\n%d %d\n255\n", nx, ny);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;
			int ir = int(255.99f * r);
			int ig = int(255.99f * g);
			int ib = int(255.99f * b);
			fprintf(gpFile, "%d %d %d\n", ir, ig, ib);
		}
	}

	if (gpFile) {
		std::cout << "File closed successfully" << std::endl;
		fclose(gpFile);
		gpFile = NULL;
	}
}

void HelloPPMCheckerBoard(const char* fileName, int nx, int ny) {
	FILE *gpFile = NULL;
	if (fopen_s(&gpFile, fileName, "w")) {
		std::cout << "File can't created \n" << std::endl;
		exit(0);
	}
	else {
		std::cout << "File created successfully " << std::endl;
	}

	fprintf(gpFile, "P3\n%d %d\n255\n", nx, ny);
	int c = 0;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			fprintf(gpFile, "%d %d %d\n", c, c, c);
		}
	}

	if (gpFile) {
		std::cout << "File closed successfully" << std::endl;
		fclose(gpFile);
		gpFile = NULL;
	}

}

void HelloBMPCheckerBoard(const char* fileName, int nx, int ny) {

	//Referance : https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

	FILE *gpFile = NULL;
	int w = nx;
	int h = ny;
	//int x, y = 0;
	unsigned char* img = NULL;

	int filesize = 54 + 3 * w * h; //54 BMP header size on windows, 3 is for r g b aand w and h as per requirement

	img = (unsigned char*)malloc(3 * w * h);
	memset(img, 0, 3 * w * h);

	/*int c = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			x = i;
			y = (h - 1) - j;
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;

			img[(x + y * w) * 3 + 2] = (unsigned char)(c);
			img[(x + y * w) * 3 + 1] = (unsigned char)(c);
			img[(x + y * w) * 3 + 0] = (unsigned char)(c);
		}
	}*/

	int c = 0;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {

			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			
			img[(i + j * w) * 3 + 0] = (unsigned char)(c);
			img[(i + j * w) * 3 + 1] = (unsigned char)(c);
			img[(i + j * w) * 3 + 2] = (unsigned char)(c);
			//img[(i + j * w) * 3 + 3] = (unsigned char)(255);
		}
	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	if (fopen_s(&gpFile, fileName, "wb")) {
		std::cout << "File can't created \n" << std::endl;
		exit(0);
	}
	else {
		std::cout << "File created successfully " << std::endl;
	}

	fwrite(bmpfileheader, 1, 14, gpFile);
	fwrite(bmpinfoheader, 1, 40, gpFile);
	for (int i = 0; i<h; i++)
	{
	
		fwrite(img + (w*(h - i - 1) * 3), 3, w, gpFile);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, gpFile);
	}

	free(img);

	if (gpFile) {
		std::cout << "File closed successfully" << std::endl;
		fclose(gpFile);
		gpFile = NULL;
	}

}