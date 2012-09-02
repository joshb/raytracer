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

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <vector>
#include "my_math.h"
#include "ray.h"

class Object {
	protected:
		Vector origin;
		float color[4];
		float reflectance;

	public:
		Object() { origin.Clear(); color[0] = color[1] = color[2] = color[3] = 1.0f; reflectance = 0.0f; }
		virtual ~Object() { }
		virtual Vector NormalAtSurfacePoint(const Vector &p) = 0;
		virtual bool Intersection(const Ray &ray, float *t_arg) = 0;
		virtual void Sample(std::vector <Object *> &objects, const Ray &ray, float t_arg, float color_arg[4], int level = 0);

		inline void SetOrigin(const Vector &v) { origin = v; }
		inline const Vector &GetOrigin() const { return origin; }

		inline void SetColor(const float color_arg[4]) { for(int i = 0; i < 4; i++) color[i] = color_arg[i]; }
		inline void SetColor(float r, float g, float b, float a = 1.0f) { color[0] = r; color[1] = g; color[2] = b; color[3] = a; }
		inline const float *GetColor() const { return color; }

		inline void SetReflectance(float reflectance_arg) { reflectance = reflectance_arg; }
};

class Sphere : public Object {
	protected:
		float radius;

	public:
		Sphere(float radius_arg) { radius = radius_arg; }

		virtual Vector NormalAtSurfacePoint(const Vector &p);
		virtual bool Intersection(const Ray &ray, float *t_arg);

		inline void SetRadius(float radius_arg) { radius = radius_arg; }
		inline float GetRadius() const { return radius; }
};

#endif /* __OBJECTS_H__ */
