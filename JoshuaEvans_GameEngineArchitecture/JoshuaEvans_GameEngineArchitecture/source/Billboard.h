#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
namespace GE {
	class Billboard
	{
	public:
		Billboard(Texture* t) {
			billTex = t;
			x = y = z = 0.0f;
			scaleX = scaleY = scaleZ = 1.0f;
		}
		~Billboard(){}
		float getX() { return x; }
		float getY() { return y; }
		float getZ() { return z; }
		glm::vec3 getPos() { return glm::vec3(getX(), getY(), getZ()); }
		
		void setX(float newX) { x = newX; }
		void setY(float newY) { y = newY; }
		void setZ(float newZ) { z = newZ; }

		Texture* getTexture() {
			return billTex;
		}

		float getScaleX() { return scaleX; }
		float getScaleY() { return scaleY; }
	
		void setScaleX(float newX) { scaleX = newX; }
		void setScaleY(float newY) { scaleY = newY; }
	private:
		float x, y, z, scaleX, scaleY, scaleZ;
		Texture* billTex;
	};
}

