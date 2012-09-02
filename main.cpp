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
#include <cstdlib>
#include <SDL/SDL.h>
#include "objects.h"
#include "raytracer.h"

#define WINWIDTH 640
#define WINHEIGHT 480
#define FULLSCREEN 0

static void
handle_key_event(SDL_Event *event)
{
	switch(event->key.keysym.sym) {
		default:
			break;
		case SDLK_ESCAPE:
			SDL_Quit();
			exit(0);
			break;
	}
}

static void
handle_event(SDL_Event *event)
{
	switch(event->type) {
		default:
			break;
		case SDL_KEYDOWN:
			handle_key_event(event);
			break;
	}
}

int
main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;

	SDL_Surface *screen = SDL_SetVideoMode(WINWIDTH, WINHEIGHT, 32, SDL_HWSURFACE | (FULLSCREEN ? SDL_FULLSCREEN : 0));
	if(!screen) {
		SDL_Quit();
		return 1;
	}

	// create framebuf for RayTracer
	unsigned char *framebuf = new unsigned char[WINWIDTH * WINHEIGHT * 4];
	for(unsigned int i = 0; i < WINWIDTH*WINHEIGHT*4; i++)
		framebuf[i] = 0xff;

	RayTracer raytracer;

	printf("Drawing scene...\n");
	raytracer.Draw(framebuf, WINWIDTH, WINHEIGHT);
	printf("Done.\n");

	SDL_LockSurface(screen);
	const unsigned int *buf = (unsigned int *)framebuf;
	unsigned int max = WINWIDTH * WINHEIGHT;
	unsigned int *pixels = (unsigned int *)screen->pixels;
	for(unsigned int i = 0; i < max; i++) {
		unsigned int p;

		p = (buf[i] >> 24) & 0xff;
		p <<= 8;
		p |= (buf[i] >> 0) & 0xff;
		p <<= 8;
		p |= (buf[i] >> 8) & 0xff;
		p <<= 8;
		p |= (buf[i] >> 16) & 0xff;

		pixels[i] = p;
	}
	SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	delete [] framebuf;

	for(;;) {
		SDL_Event event;

		while(SDL_PollEvent(&event))
			handle_event(&event);
	}

	return 0;
}
