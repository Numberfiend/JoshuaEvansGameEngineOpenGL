#pragma once
#include <SDL.h>
#include <iostream>
#include "Camera.h"

namespace GE
{

	class FPSCameraController
	{
	public:

		FPSCameraController(Camera* cam) {

			theCam = cam;


			oldTicks = SDL_GetTicks();

			SDL_Window* window = SDL_GL_GetCurrentWindow();
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
		
			SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), w / 2, h / 2);
		}

		virtual ~FPSCameraController() {}


		void update() {

			const float mouseSens = 0.1f;		
			const float moveDist = 100.0f;

	
			Uint32 newTicks = SDL_GetTicks();

	
			Uint32 diffTicks = newTicks - oldTicks;

	
			SDL_Window* window = SDL_GL_GetCurrentWindow();
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
	
			int mouse_x, mouse_y;
			SDL_GetMouseState(&mouse_x, &mouse_y);

			int diffx = mouse_x - (w / 2);
			int diffy = (h / 2) - mouse_y;

			theCam->setYaw(theCam->getYaw() + diffx * mouseSens);
			theCam->setPitch(theCam->getPitch() + diffy * mouseSens);

			const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);


			if (keyboardState[SDL_SCANCODE_UP]) {
				theCam->setPos(theCam->getPos() + theCam->getLookDir() * (moveDist * diffTicks / 1000.0f));
			}
			if (keyboardState[SDL_SCANCODE_DOWN]) {
				theCam->setPos(theCam->getPos() - theCam->getLookDir() * (moveDist * diffTicks / 1000.0f));
			}
			if (keyboardState[SDL_SCANCODE_LEFT]) {
				theCam->setPos(theCam->getPos() - glm::normalize(glm::cross(theCam->getLookDir(), theCam->getUpDir())) * (moveDist * diffTicks / 1000.0f));
			}
			if (keyboardState[SDL_SCANCODE_RIGHT]) {
				theCam->setPos(theCam->getPos() + glm::normalize(glm::cross(theCam->getLookDir(), theCam->getUpDir())) * (moveDist * diffTicks / 1000.0f));
			}
			
		
			SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), w / 2, h / 2);
			oldTicks = newTicks;


		}


	private:
		
		Camera* theCam;
		Uint32 oldTicks;
	};


}