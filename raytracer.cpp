/*
 * Copyright (C) 2003-2004, 2012 Josh A. Beam
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
#include "raytracer.h"

const Vector screen_min(-4.0f, -3.0f, 0.0f);
const Vector screen_max(4.0f, 3.0f, 0.0f);

static void
color_floats_to_bytes(float f[4], unsigned char b[4])
{
	b[0] = (unsigned char)(f[0] * 255.0f);
	b[1] = (unsigned char)(f[1] * 255.0f);
	b[2] = (unsigned char)(f[2] * 255.0f);
	b[3] = (unsigned char)(f[3] * 255.0f);
}

/*
 * RayTracer class
 */
RayTracer::RayTracer()
{
	const int spheresPerDimension = 3;

	// create objects
	for(int x = 0; x < spheresPerDimension; ++x) {
		for(int y = 0; y < spheresPerDimension; ++y) {
			for(int z = 0; z < spheresPerDimension; ++z) {
				if(((x+y+z) % 3) == 0)
					continue;

				Sphere *sphere = new Sphere(1.0f);
				sphere->SetReflectance(0.2f);
				sphere->SetOrigin(Vector((float)x, (float)y, (float)z) * 2.5f + Vector(-2.5f, -2.5f, 0.0f));
				sphere->SetColor((x % 2) ? 1.0f : 0.5f, (y % 2) ? 1.0f : 0.5f, (z % 2) ? 1.0f : 0.5f);
				objects.insert(objects.end(), sphere);
			}
		}
	}
}

RayTracer::~RayTracer()
{
	for(unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];
}

unsigned int
RayTracer::TestPixelRay(int x, int y, const Ray &ray)
{
	Object *closest_object = NULL;
	float closest_t = 9999999.0f;

	for(unsigned int i = 0; i < objects.size(); i++) {
		float t;
		if(objects[i]->Intersection(ray, &t)) {
			if(t < closest_t) {
				closest_object = objects[i];
				closest_t = t;
			}
		}
	}

	if(closest_object) {
		float fcolor[4];
		unsigned char bcolor[4];

		closest_object->Sample(objects, ray, closest_t, fcolor);
		color_floats_to_bytes(fcolor, bcolor);

		return (bcolor[0] << 24) | (bcolor[1] << 16) | (bcolor[2] << 8) | bcolor[3];
	}

	return 0;
}

void
RayTracer::Draw(unsigned char *framebuf, int framewidth, int frameheight)
{
	float screen_x_step = (screen_max.vec[0] - screen_min.vec[0]) / (float)framewidth;
	float screen_y_step = (screen_max.vec[1] - screen_min.vec[1]) / (float)frameheight;

	float fx = screen_min.vec[0];
	float fy = screen_min.vec[1];

	for(int y = 0; y < frameheight; y++) {
		for(int x = 0; x < framewidth; x++) {
			Vector dir;
			dir.Clear();

			dir.vec[0] = fx;
			dir.vec[1] = fy;
			dir.vec[2] = 2.0f;

			Ray ray;
			ray.SetOrigin(Vector(0.0f, 0.0f, 0.0f));
			ray.SetDirection(dir);

			unsigned int p = TestPixelRay(x, y, ray);

			unsigned char r = p >> 24;
			unsigned char g = p >> 16;
			unsigned char b = p >> 8;

			framebuf[framewidth * y * 4 + x * 4 + 0] = r;
			framebuf[framewidth * y * 4 + x * 4 + 1] = g;
			framebuf[framewidth * y * 4 + x * 4 + 2] = b;
			framebuf[framewidth * y * 4 + x * 4 + 3] = 0xff;

			fx += screen_x_step;
		}

		fx = screen_min.vec[0];
		fy += screen_y_step;
	}
}
