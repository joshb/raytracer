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

#ifndef __DROME_MATH_H__
#define __DROME_MATH_H__

#include <cmath>

#define PI_DIVBY_180 0.017453
#define DEG2RAD(a) ((float)(a) * PI_DIVBY_180)
#define RAD2DEG(a) (((float)(a) / M_PI) * 180.0f)

enum {
	X = 0,
	Y = 1,
	Z = 2,
	W = 3
};

class Vector;

float dot_product(const float v1[3], const float v2[3]);
void cross_product(const float v1[3], const float v2[3], float out[3]);
void normalize(float v[3]);

class Vector {
	public:
		float vec[3];

		Vector() { }
		Vector(float f1, float f2, float f3) { vec[0] = f1; vec[1] = f2; vec[2] = f3; }
		void Clear();
		void Set(const float v[3]);
		void Scale(float f);
		void Normalize();
		void Add(const Vector *v);
		void Subtract(const Vector *v);

		Vector operator + (float f) const;
		Vector operator + (Vector v) const;
		Vector operator - (float f) const;
		Vector operator - (Vector v) const;
		Vector operator * (float f) const;
		Vector operator * (Vector v) const;
		Vector operator / (float f) const;
		Vector operator / (Vector v) const;
		Vector operator += (float f);
		Vector operator += (Vector v);
		Vector operator -= (float f);
		Vector operator -= (Vector v);
		Vector operator *= (float f);
		Vector operator *= (Vector v);
		Vector operator /= (float f);
		Vector operator /= (Vector v);
};

#endif /* __DROME_MATH_H__ */
