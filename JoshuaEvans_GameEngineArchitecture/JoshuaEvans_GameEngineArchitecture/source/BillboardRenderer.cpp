#include <glm/glm.hpp>
#include <iostream>
#include "BillboardRenderer.h"
#include "ShaderUtils.h"
#include "Model.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GE {

	
	Vertex billboard[] = {
		Vertex(0.5f, 1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(-0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.5f, 0.0f, 0.0f, 0.0f, 0.0f),

		Vertex(-0.5f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(0.5f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, 1.0f, 0.0f, 1.0f, 1.0f)
	};

	BillboardRenderer::BillboardRenderer()
	{

	}

	void BillboardRenderer::init()
	{
		
		std::string v_shader_source = loadShaderSourceCode("billboard.vert");
		std::string f_shader_source = loadShaderSourceCode("billboard.frag");
		const GLchar* v_source_array[] = { v_shader_source.c_str() };
		const GLchar* f_source_array[] = { f_shader_source.c_str() };

		
		if (!compileProgram(v_source_array, f_source_array, &programId)) {
			std::cerr << "Problem building billboard program.  Check console log for more information." << std::endl;
		}

		
		vertexLocation = glGetAttribLocation(programId, "vertexPos3D");

	
		if (vertexLocation == -1) {
			std::cerr << "Problem getting vertex3DPos" << std::endl;
		}

		
		vertexUVLocation = glGetAttribLocation(programId, "vUV");

		if (vertexUVLocation == -1) {
			std::cerr << "Problem getting vUV" << std::endl;
		}

		
		transformUniformId = glGetUniformLocation(programId, "transform");
		viewUniformId = glGetUniformLocation(programId, "view");
		projectionUniformId = glGetUniformLocation(programId, "projection");
		samplerId = glGetUniformLocation(programId, "sampler");

		
		glGenBuffers(1, &vboQuad);
		glBindBuffer(GL_ARRAY_BUFFER, vboQuad);

		glBufferData(GL_ARRAY_BUFFER, sizeof(billboard), billboard, GL_STATIC_DRAW);

		
	}

	void BillboardRenderer::draw(Billboard* b, Camera* cam)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		glm::mat4 transformationMat = glm::mat4(1.0f);

		
		transformationMat = glm::translate(transformationMat, glm::vec3(b->getX(), b->getY(), b->getZ()));
		glm::vec3 fleem = (cam->getPos() - b->getPos());
		float angle = atan2(fleem.x,fleem.z);
		transformationMat = glm::rotate(transformationMat, angle, glm::vec3(0.0f, 1.0f, 0.0f));

		transformationMat = glm::scale(transformationMat, glm::vec3(b->getScaleX(), b->getScaleY(), 0.0f));
		



		glm::mat4 viewMat = cam->getViewMatrix();
		glm::mat4 projectionMat = cam->getProjectionMatrix();

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformId, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformId, 1, GL_FALSE, glm::value_ptr(projectionMat));

		
		glEnableVertexAttribArray(vertexLocation);
	
		glBindBuffer(GL_ARRAY_BUFFER, vboQuad);

		
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		
		glEnableVertexAttribArray(vertexUVLocation);
		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerId, 0);
		glBindTexture(GL_TEXTURE_2D, b->getTexture()->getTextureName());

		
		glDrawArrays(GL_TRIANGLES, 0, 6);

	
		glDisableVertexAttribArray(vertexLocation);
		glDisableVertexAttribArray(vertexUVLocation);

		glUseProgram(0);

		glDisable(GL_BLEND);
	}

}