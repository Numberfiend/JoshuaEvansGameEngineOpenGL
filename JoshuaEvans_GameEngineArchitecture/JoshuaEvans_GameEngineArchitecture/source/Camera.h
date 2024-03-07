#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE {
	class Camera {
	public:
		Camera(glm::vec3 cam_pos, glm::vec3 cam_forwardDir, glm::vec3 cam_upDir, float fov, float ar, float near, float far) {

			pos = cam_pos;
			forwardDir = cam_forwardDir;
			up = cam_upDir;

			lookDir = forwardDir;

			pitch, yaw = 0.0f;
			fovy = fov;
			aspectR = ar;
			nearClip = near;
			farClip = far;

			updateCamMatrices();
		}

		~Camera() {

		}

		float getPosX() {return pos.x;}

		float getPosY() {
			return pos.y;
		}

		float getPosZ() {
			return pos.z;
		}

		glm::vec3 getPos() {
			return pos;
		}

		glm::vec3 getForwadDir() {
			return forwardDir;
		}


		glm::vec3 getUpDir() const {
			return up;
		}
		glm::vec3 getLookDir() {
			return lookDir;
		}


		glm::mat4 getViewMatrix() const {
			return viewMat;
		}

		glm::mat4 getProjectionMatrix() const {
			return projectionMat;
		}


	
		void setPos(glm::vec3 newPos) {
			pos = newPos;
			updateCamMatrices();
		}
		void setPosX(float newX) {
			pos = glm::vec3(newX, pos.y, pos.z);

			updateCamMatrices();
		}

		void setPosY(float newY) {
			pos = glm::vec3(pos.x, newY, pos.z);

			updateCamMatrices();
		}

		void setPosZ(float newZ) {
			pos = glm::vec3(pos.x, pos.y, newZ);

			updateCamMatrices();
		}

		void setPos(float newX, float newY, float newZ) {
			pos = glm::vec3(newX, newY, newZ);

			updateCamMatrices();
		}


		void setForwardDir(glm::vec3 newDir) {
			forwardDir = newDir;

			updateCamMatrices();
		}

		void setUpDir(glm::vec3 newUp) {
			up = newUp;

			updateCamMatrices();
		}

		void setFov(float newFov) {
			fovy = newFov;

			updateCamMatrices();
		}

		void setPitch(float newPitch) {
			pitch = newPitch;
			if (pitch > 70.0f) pitch = 70.0f;
			if (pitch < -70.0f) pitch = -70.0f;

			updateCamMatrices();
		}

		void setYaw(float newYaw) {
			yaw = newYaw;
			updateCamMatrices();
		}
		void setRoll(float newRoll) {
			roll = newRoll;
			updateCamMatrices();
		}
		float getPitch() {
			return pitch;
		}
		float getYaw() {
			return yaw;
		}
		float getRoll() {
			return roll;
		}

		void setAspectRatio(float newAR) {
			aspectR = newAR;

			updateCamMatrices();
		}

		void setNearClip(float newNearClip) {
			nearClip = newNearClip;

			updateCamMatrices();
		}

		void setFarClip(float newFarClip) {
			farClip = newFarClip;

			updateCamMatrices();
		}

	private:
		void updateCamMatrices() {
			glm::mat4 rollpitchyawmat = glm::mat4(1.0f);

			rollpitchyawmat = glm::rotate(rollpitchyawmat, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			rollpitchyawmat = glm::rotate(rollpitchyawmat, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
			lookDir = rollpitchyawmat * glm::vec4(forwardDir, 0.0f);

			viewMat = glm::lookAt(pos, pos + lookDir, up);
			projectionMat = glm::perspective(glm::radians(fovy), aspectR, nearClip, farClip);
		}

	private:
	
		glm::vec3 pos;
		glm::vec3 forwardDir;
		glm::vec3 up;
		glm::vec3 lookDir;

		float fovy;
		float aspectR;
		float nearClip;
		float farClip;
		float pitch, yaw, roll;

		glm::mat4 viewMat;
		glm::mat4 projectionMat;
	};

}
