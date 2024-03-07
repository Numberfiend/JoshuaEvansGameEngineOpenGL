#include "GameEngine.h"
#include <iostream>

namespace GE {

	GameEngine::GameEngine() {
	}

	GameEngine::~GameEngine()
	{
	}

	bool GameEngine::init() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "unable to intiliaise SDL! SDL error: " << SDL_GetError() << std::endl;

			return false;
		}
	
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow("SDL OpenGL", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		
		if (window == nullptr) {
			std::cerr << "Unable to create window! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}


		glContext = SDL_GL_CreateContext(window);

		if (glContext == nullptr) {
			std::cerr << "SDL could not create GL conext! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

	
		GLenum status = glewInit();

	
		if (status != GLEW_OK) {
			std::cerr << "Error intiliasing GLEW! Error: " << glewGetErrorString(status) << std::endl;
			return false;
		}

		//VSync
		int h = 0;
		if (h == 0) {
			if (SDL_GL_SetSwapInterval(1) != 0) {
			std::cerr << "Warning: unable to set VSync! Error: " << SDL_GetError() << std::endl;
			return false;
		    }

		}
		
		dist = glm::vec3(0.0f, 0.0f, -100.0f);
		cam = new Camera(glm::vec3(0.0f,50.0f,150.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
		fpsController = new FPSCameraController(cam);

		
		m = new Model();
		bool result = m->loadFromFile("assets/pirate.obj");
		tex = new Texture("assets/14051_Pirate_Captain_body_diff.jpg");
		mr = new ModelRenderer();
		mr->init();
		mr->setPos(-20.0f, 10.0f, 0.0f);
		mr->setScale(0.05f, 0.05f, 0.05f);
		mr->setTexture(tex);

		m2 = new Model();
		bool result2 = m2->loadFromFile("assets/pirate_ship.obj");
		tex2 = new Texture("assets/pirate_ship.png");
		mr2 = new ModelRenderer();
		mr2->init();
		mr2->setPos(0.0f, -0.1f, -60.0f);
		mr2->setScale(0.1f, 0.1f, 0.1f);
		mr2->setTexture(tex2);

		m3 = new Model();
		bool result3 = m3->loadFromFile("assets/chest.obj");
		tex3 = new Texture("assets/TexturesCom_Wood_SidingOutdoor6_2x2_1K_alb.jpg");
		mr3 = new ModelRenderer();
		mr3->init();
		mr3->setPos(0.0f, 10.0f, 0.0f);
		mr3->setScale(1.0f, 1.0f, 1.0f);
		mr3->setTexture(tex3);

		m4 = new Model();
		bool result4 = m4->loadFromFile("assets/Barrel.obj");
		tex4 = new Texture("assets/barrel_albedo.png");
		mr4 = new ModelRenderer();
		mr4->init();
		mr4->setPos(20.0f, 11.5f, 0.0f);
		mr4->setScale(1.0f, 1.0f, 1.0f);
		mr4->setTexture(tex4);

		m5 = new Model();
		bool result5 = m5->loadFromFile("assets/whale.obj");
		tex5 = new Texture("assets/Laboon.png");
		mr5 = new ModelRenderer();
		mr5->init();
		mr5->setPos(0.0f, -0.1f, 60.0f);
		mr5->setScale(0.1f, 0.1f, 0.1f);
		mr5->setTexture(tex5);


		terrain = new Terrain();
		terrainTexture = new Texture("assets/Combine.png");
		mrTerrain = new ModelRenderer();
		mrTerrain->init();
		mrTerrain->setTexture(terrainTexture);
		mrTerrain->setPos(-50.0f, 0.0f, -50.0f);

		/*skybox = new SkyboxRenderer("assets/front.png", "assets/back.png",
			                        "assets/right.png", "assets/left.png",
			                        "assets/top.png", "assets/bottom.png");*/

		bbTex = new Texture("assets/cloud.png");
		bb = new Billboard(bbTex);
		bb->setScaleX(10.0f);
		bb->setScaleY(10.0f);
		bb->setZ(-10.0f);
		bb->setY(50.0f);
		bbr = new BillboardRenderer();
		bbr->init();

		terrainTexLOD = new Texture("assets/terrain_texture_LOD.png");

		skydome = new Skydome();
		skydomeTexture = new Texture("assets/skydome2.jpg");
		mrSkydome = new ModelRenderer();
		mrSkydome->init();
		mrSkydome->setTexture(skydomeTexture);

		return true;
	}


	bool GameEngine::keep_running() {
	
		SDL_PumpEvents();

		SDL_Event evt;

		// Check for quit event
		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			return false;
		}

		return true;
	}

	
	void GameEngine::update() {
		mr->setRotation(0.0f, mr->getRotY() + 2.5f, 0.0f);

		if (mrTerrain->getPosX() - cam->getPosX() > 20.0f || mrTerrain->getPosZ() - cam->getPosZ() > 20.0f)
		{
			mrTerrain->setTexture(terrainTexLOD);
		}
		else
		{
			mrTerrain->setTexture(terrainTexture);
		
		}

		fpsController->update();

	}

	
	void GameEngine::draw() {
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*skybox->draw(cam);*/
		mrSkydome->draw(cam, m, terrain, skydome, "skydome");
		mr->draw(cam, m, terrain,skydome, "model");
		mr2->draw(cam, m2, terrain, skydome, "model");
		mr3->draw(cam, m3, terrain, skydome, "model");
		mr4->draw(cam, m4, terrain, skydome, "model");
		mr5->draw(cam, m5, terrain, skydome, "model");
		mrTerrain->draw(cam, m, terrain, skydome, "terrain");
		bbr->draw(bb, cam);
		
		SDL_GL_SwapWindow(window);
	}

	
	void GameEngine::shutdown() {
		
		/*skybox->destroy();*/
		delete mr;
		delete m;
		delete cam;

		delete bbr;
		delete bb;
		delete bbTex;
		SDL_DestroyWindow(window);

		window = nullptr;

		SDL_Quit();
	}

	
	void GameEngine::setwindowtitle(const char* new_title) {
		SDL_SetWindowTitle(window, new_title);
	}

	void display_info_message(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Basic Game Engine", msg, nullptr);
	}

}