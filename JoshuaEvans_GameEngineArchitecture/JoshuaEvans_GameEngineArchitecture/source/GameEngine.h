#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Billboard.h"
#include "BillboardRenderer.h"
#include "TriangleRenderer.h"
#include "TriangleRenderer2.h"
#include "Terrain.h"
#include "Camera.h"
#include "FPSCameraController.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "Texture.h"
#include "Skydome.h"
#include "SkyboxRenderer.h"

namespace GE {


	class GameEngine {
	public:
		GameEngine();			

		virtual ~GameEngine();	

		bool init();			
		bool keep_running();	
		//void processInput();
		void update();			
		void draw();			
		void shutdown();		
					

		void setwindowtitle(const char*);
		int w = 300;
		int h = 200;

	private:
		
		SDL_Window* window;

	
		SDL_GLContext glContext;

		//Camera stuff
		Camera* cam;
		FPSCameraController* fpsController;

		TriangleRenderer2* triangle;

		//Model Stuff
		//std::vector<Model*> models = {m, m2, m3, m4, m5};
		Model* m;
		Texture* tex;
		ModelRenderer* mr;
		Model* m2;
		Texture* tex2;
		ModelRenderer* mr2;
		Model* m3;
		Texture* tex3;
		ModelRenderer* mr3;
		Model* m4;
		Texture* tex4;
		ModelRenderer* mr4;
		Model* m5;
		Texture* tex5;
		ModelRenderer* mr5;
		

		//Terrain Stuff
		Terrain* terrain;
		Texture* terrainTexture;
		ModelRenderer* mrTerrain;


		//skybox stuff
		SkyboxRenderer* skybox;

		glm::vec3 dist;

		//Skydome stuff
		Skydome* skydome;
		Texture* skydomeTexture;
		ModelRenderer* mrSkydome;

		//Billboard Stuff
		Texture* bbTex;
		Billboard* bb;
		BillboardRenderer* bbr;

		//lod textures
		Texture* terrainTexLOD = nullptr;
	};

	void display_info_message(const char*);

}




