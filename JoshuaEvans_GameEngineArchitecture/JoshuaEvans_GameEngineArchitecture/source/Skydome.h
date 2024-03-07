#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
namespace GE {
	class Skydome {
	public:
		Skydome();
		GLuint getVertices() { return vbo; }
		GLuint getIndices() { return ibo; }
		GLuint getIndexCount() { return indexCount; }
	private:
		GLuint vbo, ibo, indexCount;
	};
}

