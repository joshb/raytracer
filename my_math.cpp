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

// math.cpp - Useful math functions and classes

#include "my_math.h"

float
dot_product(const float v1[3], const float v2[3])
{
	return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

void
cross_product(const float v1[3], const float v2[3], float out[3])
{
	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void
normalize(float v[3])
{
	float f;

	f = 1.0f / sqrtf(dot_product(v, v));
	v[0] *= f;
	v[1] *= f;
	v[2] *= f;
}

// inline because this will normally just be called by Vector::Scale()
inline void
scale_vec(float v[3], float f)
{
	v[0] *= f;
	v[1] *= f;
	v[2] *= f;
}

/*
 * Vector class
 */
void
Vector::Clear()
{
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
}

void
Vector::Set(const float v[3])
{
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
}

void
Vector::Scale(float f)
{
	scale_vec(vec, f);
}

void
Vector::Normalize()
{
	normalize(vec);
}

void
Vector::Add(const Vector *v)
{
	vec[0] += v->vec[0];
	vec[1] += v->vec[1];
	vec[2] += v->vec[2];
}

void
Vector::Subtract(const Vector *v)
{
	vec[0] -= v->vec[0];
	vec[1] -= v->vec[1];
	vec[2] -= v->vec[2];
}

Vector
Vector::operator + (float f) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.vec[0] += f;
	tmp.vec[1] += f;
	tmp.vec[2] += f;

	return tmp;
}

Vector
Vector::operator + (Vector v) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.Add(&v);

	return tmp;
}

Vector
Vector::operator - (float f) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.vec[0] -= f;
	tmp.vec[1] -= f;
	tmp.vec[2] -= f;

	return tmp;
}

Vector
Vector::operator - (Vector v) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.Subtract(&v);

	return tmp;
}

Vector
Vector::operator * (float f) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.Scale(f);

	return tmp;
}

Vector
Vector::operator * (Vector v) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.vec[0] *= v.vec[0];
	tmp.vec[1] *= v.vec[1];
	tmp.vec[2] *= v.vec[2];

	return tmp;
}

Vector
Vector::operator / (float f) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.vec[0] /= f;
	tmp.vec[1] /= f;
	tmp.vec[2] /= f;

	return tmp;
}

Vector
Vector::operator / (Vector v) const
{
	Vector tmp;

	tmp.Set(vec);
	tmp.vec[0] /= v.vec[0];
	tmp.vec[1] /= v.vec[1];
	tmp.vec[2] /= v.vec[2];

	return tmp;
}

Vector
Vector::operator += (float f)
{
	vec[0] += f;
	vec[1] += f;
	vec[2] += f;

	return *this;
}

Vector
Vector::operator += (Vector v)
{
	Add(&v);

	return *this;
}

Vector
Vector::operator -= (float f)
{
	vec[0] -= f;
	vec[1] -= f;
	vec[2] -= f;

	return *this;
}

Vector
Vector::operator -= (Vector v)
{
	Subtract(&v);

	return *this;
}

Vector
Vector::operator *= (float f)
{
	Scale(f);

	return *this;
}

Vector
Vector::operator *= (Vector v)
{
	vec[0] *= v.vec[0];
	vec[1] *= v.vec[1];
	vec[2] *= v.vec[2];

	return *this;
}

Vector
Vector::operator /= (float f)
{
	vec[0] /= f;
	vec[1] /= f;
	vec[2] /= f;

	return *this;
}

Vector
Vector::operator /= (Vector v)
{
	vec[0] /= v.vec[0];
	vec[1] /= v.vec[1];
	vec[2] /= v.vec[2];

	return *this;
}
