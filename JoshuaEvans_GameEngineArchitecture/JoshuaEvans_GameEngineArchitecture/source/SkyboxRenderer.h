#pragma once
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <vector>
#include <string>
#include "Camera.h"

namespace GE {
	class SkyboxRenderer {
	public:
		SkyboxRenderer(std::string front_file, std::string back_file, std::string right_file, std::string left_file, std::string top_file, std::string bottom_file) {
			std::vector<std::string> filenames;

			filenames.push_back(right_file);
			filenames.push_back(left_file);
			filenames.push_back(top_file);
			filenames.push_back(bottom_file);
			filenames.push_back(front_file);
			filenames.push_back(back_file);

			createCubemap(filenames);
			createCubeVBO();
			createSkyboxProgram();
		}

		~SkyboxRenderer() {}
		void draw(Camera* cam);
		void destroy();
	private:
		void createCubemap(std::vector<std::string> filenames);
		void createCubeVBO();
		void createSkyboxProgram();

		GLuint skyboxCubeMapName;
		GLuint skyboxProgramId;
		GLuint vertexlocation;
		GLuint vboSkybox;
		GLuint viewUniformId;
		GLuint projectionUniformId;
		GLuint samplerId;
	};
}

