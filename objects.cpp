/*
 * Copyright (C) 2003-2004 Josh A. Beam
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdio>
#include "objects.h"

#define SQUARE(x) ((x)*(x))

const int MAX_REFLECTION_RECURSION = 8;
const float AMBIENT = 0.2f;

const Vector light_pos(-2.0f, -10.0f, 12.0f);

/*
 * Object class
 */
void
Object::Sample(std::vector <Object *> &objects, const Ray &ray, float t_arg, float color_arg[4], int level)
{
	// calculate point on object
	Vector p = ray.GetOrigin() + ray.GetDirection() * t_arg;

	// calculate normal of point on object
	Vector normal = NormalAtSurfacePoint(p);

	// calculate light to point vector
	Vector l = light_pos - p;
	l.Normalize();

	// calculate diffuse lighting
	float diffuse = dot_product(normal.vec, l.vec);
	diffuse += 1.0f;
	diffuse /= 2.0f;
	if(diffuse < AMBIENT)
		diffuse = AMBIENT;

	// calculate specular lighting
	float specular = 0.0f;
	Vector sv = l - normal * dot_product(l.vec, normal.vec) * 2.0f;
	float dot = dot_product(sv.vec, ray.GetDirection().vec);
	if(dot > 0.0f)
		specular = SQUARE(SQUARE(SQUARE(dot)));

	// write to color array
	for(int i = 0; i < 4; i++)
		color_arg[i] = (color[i] * diffuse * (1.0f - reflectance)) + specular;

#if 1
	if(level <= MAX_REFLECTION_RECURSION && reflectance > 0.0f) {
		// create reflection vector
		Vector rv = ray.GetDirection() - normal * dot_product(ray.GetDirection().vec, normal.vec) * 2.0f;

		// create ray from intersection point in direction of reflection vector
		Ray r;
		r.SetOrigin(p);
		r.SetDirection(rv);

		Object *closest_object = NULL;
		float closest_t = 9999999.0f;
		for(unsigned int i = 0; i < objects.size(); i++) {
			float t;
			if(objects[i]->Intersection(r, &t)) {
				if(t < closest_t) {
					closest_object = objects[i];
					closest_t = t;
				}
			}
		}
		if(closest_object) {
			float fcolor[4];
			closest_object->Sample(objects, r, closest_t, fcolor, level+1);
			color_arg[0] += fcolor[0] * reflectance;
			color_arg[1] += fcolor[1] * reflectance;
			color_arg[2] += fcolor[2] * reflectance;
			color_arg[3] += fcolor[3] * reflectance;
		}
	}
#endif

	for(int i = 0; i < 4; i++) {
		if(color_arg[i] > 1.0f)
			color_arg[i] = 1.0f;
	}
}

/*
 * Sphere class
 */
Vector
Sphere::NormalAtSurfacePoint(const Vector &p)
{
	Vector tmp;

	tmp = p - origin;
	tmp.Normalize();

	return tmp;
}

bool
Sphere::Intersection(const Ray &ray, float *t_arg)
{
	Vector ro, rd, tmp;

	ro = ray.GetOrigin();
	rd = ray.GetDirection();
	tmp = ro;
	tmp.Subtract(&origin);

	float a = SQUARE(rd.vec[0]) + SQUARE(rd.vec[1]) + SQUARE(rd.vec[2]);
	float b = dot_product(rd.vec, tmp.vec) * 2.0f;
	float c = SQUARE(ro.vec[0] - origin.vec[0]) +
	          SQUARE(ro.vec[1] - origin.vec[1]) +
	          SQUARE(ro.vec[2] - origin.vec[2]) - SQUARE(radius);

	float disc = SQUARE(b) - (4.0f*a*c);

	if(disc < 0.0f)
		return false;

	float t1 = (-b + sqrtf(disc)) / (2.0f*a);
	float t2 = (-b - sqrtf(disc)) / (2.0f*a);
	float t = (t1 < t2) ? t1 : t2;

	if(t < 0.0f)
		return false;

	if(t_arg)
		*t_arg = t;

	return true;
}
