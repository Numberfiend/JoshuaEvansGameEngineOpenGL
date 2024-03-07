#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "Camera.h"
namespace GE {

	class TriangleRenderer2
	{
	public:
		TriangleRenderer2();
		~TriangleRenderer2();
		void init();
		void update();
		void draw(Camera* cam);
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
		void displayShaderCompilerError(GLuint shaderID) {
			GLint MsgLen = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &MsgLen);
			if (MsgLen > 1) {
				GLchar* Msg = new GLchar[MsgLen + 1];
				glGetShaderInfoLog(shaderID, MsgLen, NULL, Msg);
				std::cerr << "Error compliling shader" << Msg << std::endl;
				delete[] Msg;
			}
		}
	private:
		GLuint programId;
		GLint vertexPos3DLocation;
		GLint vertexColourLocation;
		GLuint vboTriangle;

		float pos_x, pos_y, pos_z;
		float rot_x, rot_y, rot_z;
		float scale_x, scale_y, scale_z;

		GLuint transformUniformId;
		GLuint viewUniformId;
		GLuint projectionUniformId;
	};

}

