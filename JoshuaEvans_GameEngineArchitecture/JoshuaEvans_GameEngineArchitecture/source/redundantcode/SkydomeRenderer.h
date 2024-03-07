#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Skydome.h"

namespace GE {
	class SkydomeRenderer {
	public:
		SkydomeRenderer();
		virtual ~SkydomeRenderer();
		void init();
		void update();
		void draw(Camera* cam, Skydome* skydome);
		void destroy();

		float getPosX() {
			return pos_x;
		}
		float getPosY() {
			return pos_x;
		}
		float getPosZ() {
			return pos_z;
		}
		float getRotX() {
			return rot_x;
		}
		float getRotY() {
			return rot_y;
		}
		float getRotZ() {
			return rot_z;
		}
		float getScaleX() {
			return scale_x;
		}
		float getScaleY() {
			return scale_y;
		}
		float getScaleZ() {
			return scale_z;
		}
		void setPos(float x, float y, float z) {
			pos_x = x;
			pos_y = y;
			pos_z = z;
		}
		void setRotation(float rx, float ry, float rz) {
			rot_x = rx;
			rot_y = ry;
			rot_z = rz;
		}
		void setScale(float sx, float sy, float sz) {
			scale_x = sx;
			scale_y = sy;
			scale_z = sz;
		}
		void setTexture(Texture* _tex) {
			tex = _tex;
		}

	private:
		GLuint programId;
		GLint vertexLocation;
		GLint vertexUVLocation;

		float pos_x, pos_y, pos_z;
		float rot_x, rot_y, rot_z;
		float scale_x, scale_y, scale_z;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
		GLuint samplerId;

		Texture* tex;
	};
}



