// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../game/FighterUtils.h"
#include "../components/Transform.h"
#include "../game/PausedState.h"
#include "../game/NewGameState.h"
#include "../game/NewRoundState.h"
#include "../game/RunningState.h"
#include "../game/GameOverState.h"

using ecs::Entity;
using ecs::EntityManager;

Game::Game() :
		_mngr(nullptr) {
}

Game::~Game() {
	delete _mngr;

	delete _paused_state;
	delete _runing_state;
	delete _newgame_state;
	delete _newround_state;
	delete _gameover_state;


	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Asteroids", 800, 600,
			"resources/config/asteroid.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;
	}

	return true;
}

void
Game::initGame() {
	// Create the manager
	_mngr = new EntityManager();

	// create the game info entity
	auto ginfo = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::GAMEINFO, ginfo);
	ginfo->addComponent<GameCtrl>();

	_fighterUtils = new FighterUtils();
	_fighterUtils->create_fighter();

	_paused_state = new PausedState();
	_runing_state = new RunningState();
	_newgame_state = new NewGameState();
	_newround_state = new NewRoundState();
	_gameover_state = new GameOverState();

	_state = _newgame_state;

}

void Game::start() {
	bool exit = false; // exit boolean
	
	auto& ihdlr = ih(); // input handler
	
	auto& vt = sdlutils().virtualTimer(); // virutal timer to be able to pause the timer in PausedState	
	
	vt.resetTime(); // start counting from this instance
	
	while (!exit) {
		Uint32 startTime = vt.regCurrTime(); // register current time so all objects use the same time
		ihdlr.refresh(); // refresh input
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) { // if escape key, exit game
			exit = true;
			continue;
		}
		_state->update(); // update current state
		Uint32 frameTime = sdlutils().currRealTime() - startTime; // how much time since beginning of this "frame" 
		if (frameTime < 10) SDL_Delay(10 - frameTime); // delay 
	}
}

void Game::checkCollisions() {

	// the PacMan's Transform
	//
	auto pTR = _mngr->getHandler(ecs::hdlr::FIGHTER)->getComponent<Transform>();

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &stars = _mngr->getEntities(ecs::grp::STARS);
	auto n = stars.size();
	for (auto i = 0u; i < n; i++) {
		auto e = stars[i];
		if (e->isAlive()) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = e->getComponent<Transform>();

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(pTR->getPos(), pTR->getWidth(),
					pTR->getHeight(), //
					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
				e->setAlive(false);
			}
		}
	}
}
