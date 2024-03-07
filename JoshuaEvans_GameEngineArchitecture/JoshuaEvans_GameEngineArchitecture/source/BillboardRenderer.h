#pragma once
#include "Camera.h"
#include "Billboard.h"

namespace GE {
	class BillboardRenderer
	{
	public:
		BillboardRenderer();

		~BillboardRenderer() {
			glDeleteBuffers(1, &vboQuad);
		}

		void init();

		void draw(Billboard*, Camera*);

	private:

		GLuint programId;

		GLint vertexLocation;

		GLint vertexUVLocation;

		GLuint vboQuad;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
		GLuint samplerId;
	};
}