#include "Skydome.h"
#include "Model.h"
#include <vector>
#include <cmath>

namespace GE {
	Skydome::Skydome() {
		
		const float PIDIV2 = M_PI / 2.0f;

		int horizResolution = 16;
		int vertResolution = 16;

		// Radius for sphere
		int radius = 10;

		// Store the generated vertices
		std::vector<Vertex> vertices;

		
		float azimuthStep = 2.0f * M_PI / horizResolution;

	
		float texturePercentage = 2.0f;

		
		float spherePercentage = 2.0f;

		
		float elevation = PIDIV2;

		
		float elevationStep = spherePercentage * PIDIV2 / vertResolution;

		
		float uStep = 1.0f / horizResolution;
		float vStep = 1.0f / vertResolution;

		
		float v = 0.0f;

		
		for (int vert = 0; vert < vertResolution + 1; vert++) {
			float length = radius * cos(elevation);
			float y = radius * sin(elevation);
			float u = 0.0f;
			float angle = 0;
			for (int horiz = 0; horiz < horizResolution + 1; horiz++) {
				float x = length * sin(angle);
				float z = length * cos(angle);
				vertices.push_back(Vertex(x, y, z, u, v * texturePercentage));
				angle += azimuthStep;
				u += uStep;
			}
			elevation -= elevationStep;
			v += vStep;
		}
		std::vector<int>indices;
		for (int vert = 0; vert < vertResolution; vert++) {
			int offset = vert * (horizResolution + 1);
			for (int horiz = 0; horiz < horizResolution; horiz++) {
				indices.push_back(offset + horiz);
				indices.push_back(offset + horiz +1 );
				indices.push_back(offset + (horizResolution+1) +(horiz+1));

				indices.push_back(offset + (horizResolution + 1) + (horiz + 1));
				indices.push_back(offset + horizResolution + (horiz + 1));
				indices.push_back(offset + horiz);
			}
		}

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ARRAY_BUFFER, ibo);
		glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		indexCount = indices.size();

	}


}

