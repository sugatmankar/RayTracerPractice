#include<iostream>
#include "vec3.h"
int mainraw() {

	int nx = 200;
	int ny = 55;
	FILE *gpFile = NULL;
	if (fopen_s(&gpFile, "Hello.ppm", "w") != 0) {
		std::cout << "File Can Not Be Created\nExitting ...\n" << std::endl;
		exit(0);
	}
	else {
		std::cout << "File Is Successfully Opened.\n";
	}
	fprintf(gpFile, "P3\n %d %d \n255\n", nx, ny);
	for (int j = 0; j < ny - 1; j++) {
		for (int i = 0; i < nx; i++) {
			/* without vec3
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;*/
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			/*without vec3
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);*/
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			fprintf(gpFile, "%d %d %d\n", ir, ig, ib);
		}
	}
	if (gpFile)
	{
		std::cout << "File Is Successfully Closed.\n";
		fclose(gpFile);
		gpFile = NULL;
	}
	return 0;
}