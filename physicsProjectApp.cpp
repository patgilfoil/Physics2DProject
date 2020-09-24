#include "physicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Plane.h"
#include <Gizmos.h>

physicsProjectApp::physicsProjectApp() {

}

physicsProjectApp::~physicsProjectApp() {

}

bool physicsProjectApp::startup() {
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	glm::vec2 gravity = glm::vec2(0.0f, 0.0f);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(gravity);
	m_physicsScene->setTimeStep(0.01f);

	Plane* bottomExtent = new Plane(glm::normalize(glm::vec2(0.0f, 1.0f)), -30.0f);
	Plane* topExtent = new Plane(glm::normalize(glm::vec2(0.0f, 1.0f)), 30.0f);
	Plane* leftExtent = new Plane(glm::normalize(glm::vec2(-80.0f, 0.0f)), 60.0f);
	Plane* rightExtent = new Plane(glm::normalize(glm::vec2(80.0f, 0.0f)), 60.0f);
	m_physicsScene->addActor(bottomExtent);
	m_physicsScene->addActor(topExtent);
	m_physicsScene->addActor(leftExtent);
	m_physicsScene->addActor(rightExtent);

	Sphere* ball = new Sphere(glm::vec2(0.0f, 0.0f), glm::vec2(80.0f, 30.0f), 4.0f, 4.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->addActor(ball);

	return true;
}

void physicsProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void physicsProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void physicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(
		-100.0f, 100.0f,
		-100.0f / aspectRatio, 100.0f / aspectRatio,
		-1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}