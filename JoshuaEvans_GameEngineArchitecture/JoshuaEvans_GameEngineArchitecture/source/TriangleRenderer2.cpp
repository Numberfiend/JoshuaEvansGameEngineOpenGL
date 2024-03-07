#include "TriangleRenderer2.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
namespace GE {

	struct Vertex {
		float x, y, z;
		float r, g, b, a;

		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a) {
			x = _x;
			y = _y;
			z = _z;

			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		Vertex() {
			x = y = z = 0.0f;
			r = g = b = a = 0.0f;
		}

	};

	Vertex vertexData[] = {
		Vertex(- 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f)
	};
	TriangleRenderer2::TriangleRenderer2() {
		pos_x = pos_y = pos_z = 0.0f;
		rot_x = rot_y = rot_z = 0.0f;
		scale_x = scale_y = scale_z = 1.0f;
	}
	TriangleRenderer2::~TriangleRenderer2() {

	}
	
	void TriangleRenderer2::init()
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec3 vertexPos3D;\n"
			"in vec4 vColour;\n"
			"out vec4 fColour;\n"
			"uniform mat4 transform;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"vec4 v = vec4(vertexPos3D.xyz, 1);\n"
			"v = projection * view * transform * v;\n" 
			"gl_Position = v;\n"
			"fColour = vColour;\n"
			"}\n" };
		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);
		glCompileShader(vertexShader);
		GLint isShaderCompliedOK = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompliedOK);
		if (isShaderCompliedOK != GL_TRUE) {
			std::cerr << "Unable to compile vertex shader" << std::endl;
			displayShaderCompilerError(vertexShader);
			return;
		}
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* F_ShaderCode[] = {
		"#version 140\n"
		"in vec4 fColour;\n"
		"out vec4 fragmentColour;\n"
		"void main()\n"
		"{\n"
		"fragmentColour = fColour;\n"
		"}\n"
		};
		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);
		glCompileShader(fragmentShader);
		isShaderCompliedOK = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompliedOK);
		if (isShaderCompliedOK != GL_TRUE) {
			std::cerr << "Unable to compile fragment shader" << std::endl;
			displayShaderCompilerError(fragmentShader);
			return;
		}
		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);
		GLint isProgramLinked = GL_FALSE;
		glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			std::cerr << "Failed to link program" << std::endl;
		}

		vertexPos3DLocation = glGetAttribLocation(programId, "vertexPos3D");
		if (vertexPos3DLocation == -1) {
			std::cerr << "problem getting vertex3Dpos" << std::endl;
		}

		vertexColourLocation = glGetAttribLocation(programId, "vColour");
		if (vertexColourLocation == -1) {
			std::cerr << "Problem getting vColour" << std::endl;
		}

		viewUniformId = glGetUniformLocation(programId, "view");
		projectionUniformId = glGetUniformLocation(programId, "projection");
		transformUniformId = glGetUniformLocation(programId, "transform");

		glGenBuffers(1, &vboTriangle);
		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void TriangleRenderer2::update() {

	}
	void TriangleRenderer2::draw(Camera* cam) {

		glm::mat4 transformationMat = glm::mat4(1.0f);
		transformationMat = glm::translate(transformationMat, glm::vec3(pos_x, pos_y, pos_z));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::scale(transformationMat, glm::vec3(scale_x, scale_y, scale_z));

		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformId, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformId, 1, GL_FALSE, glm::value_ptr(projectionMat));

		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
		glEnableVertexAttribArray(vertexPos3DLocation);
		glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, x));
		
		glEnableVertexAttribArray(vertexColourLocation);
		glVertexAttribPointer(vertexColourLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertexData) / sizeof(Vertex));
		glDisableVertexAttribArray(vertexPos3DLocation);
		glDisableVertexAttribArray(vertexColourLocation);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	void TriangleRenderer2::destroy() {
		glDeleteProgram(programId);
		glDeleteBuffers(1, &vboTriangle);
	}
}