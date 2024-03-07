#include "TerrainRenderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


namespace GE {

	TerrainRenderer::TerrainRenderer()
	{
		pos_x = pos_y = pos_z = 0.0f;
		rot_x = rot_y = rot_z = 0.0f;
		scale_x = scale_y = scale_z = 1.0f;

		programId = 0;

		vertexLocation = 0;
		vertexUVLocation = 0;
		transformUniformId = 0;
		viewUniformId = 0;
		projectionUniformId = 0;
	}
	TerrainRenderer::~TerrainRenderer()
	{
	}

	void TerrainRenderer::init() {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec3 vertexPos3D;\n"
			"in vec2 vUV;\n"
			"out vec2 uv;\n"
			"uniform mat4 viewMat;\n"
			"uniform mat4 projMat;\n"
			"uniform mat4 transformMat;\n"
			"void main() {\n"
			"gl_Position = projMat * viewMat * transformMat * vec4(vertexPos3D.xyz, 1);\n"
			"uv = vUV;\n"
			"}\n" };
		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);
		glCompileShader(vertexShader);
		GLint isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);
		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile vertex shader" << std::endl;
			//displayShaderCompilerError(vertexShader);
			return;
		}
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"in vec2 uv;\n"
			"uniform sampler2D sampler;\n"
			"out vec4 fragmentColour;\n"
			"void main()\n"
			"{\n"
			"fragmentColour = texture(sampler, uv).rgba;\n"
			"}\n"
		};
		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);
		glCompileShader(fragmentShader);

		isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile fragment shader" << std::endl;
			//displayShaderCompilerError(fragmentShader);
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

		vertexLocation = glGetAttribLocation(programId, "vertexPos3D");

		if (vertexLocation == -1) {
			std::cerr << "Problem getting vertex3DPos" << std::endl;
		}

		vertexUVLocation = glGetAttribLocation(programId, "vUV");
		if (vertexUVLocation == -1) {
			std::cerr << "Problem getting vUV" << std::endl;
		}

		viewUniformId = glGetUniformLocation(programId, "viewMat");
		projectionUniformId = glGetUniformLocation(programId, "projMat");
		transformUniformId = glGetUniformLocation(programId, "transformMat");
		samplerId = glGetUniformLocation(programId, "sampler");

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void TerrainRenderer::update() {

	}
	void TerrainRenderer::draw(Camera* cam, Terrain* terrain)
	{
		glEnable(GL_CULL_FACE);

		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::translate(transformationMat, glm::vec3(pos_x, pos_y, pos_z));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::scale(transformationMat, glm::vec3(scale_x, scale_y, scale_z));

		glUseProgram(programId);

		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUniformMatrix4fv(transformUniformId, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformId, 1, GL_FALSE, glm::value_ptr(projectionMat));

		glBindBuffer(GL_ARRAY_BUFFER, terrain->getVertices());
		glEnableVertexAttribArray(vertexLocation);
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

		glEnableVertexAttribArray(vertexUVLocation);
		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		//selecting the texture
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerId, 0);
		glBindTexture(GL_TEXTURE_2D, tex->getTextureName());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain->getIndicies());
		glDrawElements(GL_TRIANGLES, terrain->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexLocation);
		glDisableVertexAttribArray(vertexUVLocation);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

		glDisable(GL_CULL_FACE);
	}
	void TerrainRenderer::destroy() {
		glDeleteProgram(programId);
		//glDeleteBuffers(1, &vboTriangle);
	}
}