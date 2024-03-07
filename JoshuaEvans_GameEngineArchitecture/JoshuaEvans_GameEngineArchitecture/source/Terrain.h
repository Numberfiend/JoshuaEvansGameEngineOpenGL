#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
namespace GE {
	class Terrain
	{
	public:
		Terrain();

		GLuint getVertices() { return vbo; }
		GLuint getIndicies() { return ibo; }
		GLuint getIndexCount() { return indexCount; }

	private:
		GLuint vbo, ibo, indexCount;
	};
}

