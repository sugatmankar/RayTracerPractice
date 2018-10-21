#pragma once

#include "Hitable.h"

class hitable_list : public hitable {

public:

	hitable **list;
	int list_size;

	hitable_list() {}
	hitable_list(hitable **l,int n) {
		list = l;
		list_size = n;
	}

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec)const;
	   
};

bool hitable_list::hit(const ray& r, float tmin, float tmax, hit_record& rec)const {
	hit_record tempRecord;
	bool hit_anything = false;
	double closest_so_far = tmax;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, tmin, closest_so_far, tempRecord)) {
			hit_anything = true;
			closest_so_far = tempRecord.t;
			rec = tempRecord;
		}
	}
	return hit_anything;
}
