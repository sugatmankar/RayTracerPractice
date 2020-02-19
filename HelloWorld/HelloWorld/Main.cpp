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
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"

int main(void) {

	void HelloSTBPNGCheckerBoard(const char* fileName, int nx, int ny);

	void HelloSTBPNGSimple(const char* fileName, int nx, int ny);

	void HelloSTBPNGVec3(const char* fileName, int nx, int ny);

	void HelloSTBPNGVec3Ray(const char* fileName, int nx, int ny);

	int nx = 64;
	int ny = 64;

	//HelloSTBPNGCheckerBoard("bar_out.png", 64, 64);
	
	HelloSTBPNGSimple("foo_bar.png",128,128);
	
	//HelloSTBPNGVec3("foo_bar.png", 256, 256);

	//HelloSTBPNGVec3Ray("foo_bar_ray.png", 200, 100);

	return 0;
}

float hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(),r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
		return -1.0;
	else {
		return (-b - sqrt(discriminant))/(2.0*a);
	}
	
}

vec3 color(const ray& r) {

	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);

		if (t > 0.0) {
			vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
			return 0.5 * vec3(N.x()+1,N.y()+1,N.z()+1);
		}
	
	vec3 unitDirection = unit_vector(r.direction());

	t = 0.5 * (unitDirection.y() + 1.0);
	
	//blended value = (1-t)* start values + t* end values

	return  (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		return 0.5 *vec3(rec.normal.x()+1, rec.normal.y()+1,rec.normal.z()+1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) *vec3(1.0, 1.0, 1.0) + t * vec3(0.5,0.7,1.0);
	}
}

void HelloSTBPNGVec3Ray(const char* fileName, int nx, int ny) {

	unsigned char* data = NULL;

	data = (unsigned char*)malloc(3 * nx * ny); // 3 for x y z

	memset(data,//dst
		0, //val
		3 * nx * ny //size_t
	);

	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);

	hitable *list[2];
	list[0] = new sphere(vec3(0,0,-1),0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable *world = new hitable_list(list,2);

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

			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			
			ray r(origin,lower_left_corner + u*horizontal + v*vertical);

			//vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r,world);

			data[(i + j * nx) * 3 + 0] = int(255.99* col[0]);
			data[(i + j * nx) * 3 + 1] = int(255.99* col[1]);
			data[(i + j * nx) * 3 + 2] = int(255.99* col[2]);
		}
	}

	stbi_write_png(fileName, nx, ny, 3, data, 0);
	//stbi_write_bmp("sugat.bmp", nx, ny, 3, data);
	free(data);
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