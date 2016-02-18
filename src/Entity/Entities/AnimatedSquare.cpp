#include "AnimatedSquare.hpp"
#include <iostream>
#include "../../constants.hpp"
#include "../../Animation/Animator.hpp"

AnimatedSquare::AnimatedSquare(b2World const* world, b2Body* body) : WorldEntity(world, body), 
													 numFootContacts(0), 
													 contactLeft(false), 
													 contactRight(false), 
													 contactBottomRight(false),
													 contactBottomLeft(false)
{
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(29.f/PPM, 40.f/PPM);
		
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0.f,10.f/PPM);
	circleShape.m_radius = 30.f/PPM;

	fixtureDef.shape = &circleShape;
	//circle = body->CreateFixture(&fixtureDef);

	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	fixtureDef.isSensor = true;

	polygonShape.SetAsBox(28.f/PPM, 2.f/PPM, b2Vec2(0.f, 39.f/PPM), 0);

	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"FootSensor");

	fixtureDef.isSensor = false;
	fixtureDef.friction = 300.f;
	polygonShape.SetAsBox(1.f/PPM, 38.f/PPM, b2Vec2(-28.f/PPM, 0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"LeftAnimatedSquareSide");

	polygonShape.SetAsBox(1.f/PPM, 38.f/PPM, b2Vec2(28.f/PPM,0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"RightAnimatedSquareSide");

	body->SetTransform(b2Vec2(100.f/PPM, 100.f/PPM), 0);

	polygonShape.SetAsBox(1.f/PPM,4.5f/PPM,b2Vec2(28.f/PPM,35.f/PPM), 0);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef)->SetUserData((void*)"BottomRightAnimatedSquareCorner");

	polygonShape.SetAsBox(1.f/PPM,4.5f/PPM,b2Vec2(-28.f/PPM,35.f/PPM),0);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef)->SetUserData((void*)"BottomLeftAnimatedSquareCorner");

	/*sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(60.f,80.f));
	s->setFillColor(sf::Color::Black);
	s->setOrigin(30.f,40.f);

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);*/

	squareTexture = sf::Texture();
	squareTexture.loadFromFile("img/spritesheet.png");
	sf::Sprite* s = new sf::Sprite(squareTexture);
	
	s->setScale(60.f/23.f,80.f/47.f);
	s->setOrigin(23.f/2, 47.f/2);
	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);
	this->body->SetUserData((void*)this);

	// animation test : remplissage de textureSubRects
	AnimationsRects textureSubRects = AnimationsRects();
	textureSubRects.push_back(std::vector<sf::IntRect>());
	std::vector<sf::IntRect>& animation1 = textureSubRects.at(0);
	animation1.push_back(sf::IntRect(40,139,23,47));
	animation1.push_back(sf::IntRect(73,140,96-73,187-140));
	animation1.push_back(sf::IntRect(40,139,63-40,186-139));
	animation1.push_back(sf::IntRect(137,140,160-137,186-140));

	animator = Animator(0.1f);
	animator.setSubRects(textureSubRects);
}

b2BodyDef AnimatedSquare::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	return bodyDef;
}

void AnimatedSquare::tick(void) {

	// keyboard movement
	if(numFootContacts > 0) { // on ground

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			!contactLeft)
			body->SetLinearVelocity(b2Vec2(-600.f/PPM, body->GetLinearVelocity().y));
			
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
				!contactRight)
			body->SetLinearVelocity(b2Vec2(600.f/PPM, body->GetLinearVelocity().y));
		else {
			body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));
		}
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && contactBottomRight) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && contactBottomLeft))
			body->ApplyLinearImpulse(b2Vec2(0.f,-10.f*body->GetMass()),body->GetWorldCenter(),true);
		else
			body->ApplyForceToCenter(b2Vec2(0.f,100.f*body->GetMass()),true);
	}

	else { // jumping or falling

		if(contactLeft || contactRight)
			body->ApplyForceToCenter(b2Vec2((contactLeft ? -2.f : 2.f)*body->GetMass(),-60.f*body->GetMass()), true);

		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x*0.98f, body->GetLinearVelocity().y));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !contactLeft)
			body->ApplyForceToCenter(b2Vec2(-80.f*body->GetMass(), 0), true);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !contactRight)
			body->ApplyForceToCenter(b2Vec2(80.f*body->GetMass(), 0), true);
	}

	// animation test
	sf::Sprite* s = reinterpret_cast<sf::Sprite*>(this->graphicalElement);
	
	animator.onTick();
	s->setTextureRect(animator.getCurrentTextureRect());

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);
	this->matchGraphicsToPhysics();
}

void AnimatedSquare::onBeginContact(b2Contact* contact) {

	// TODO see if this can be done in a cleaner way

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			numFootContacts++;
		else if(userData == "LeftAnimatedSquareSide")
			contactLeft = true;
		else if(userData == "RightAnimatedSquareSide")
			contactRight = true;
		else if(userData == "BottomRightAnimatedSquareCorner")
			contactBottomRight = true;
		else if(userData == "BottomLeftAnimatedSquareCorner")
			contactBottomLeft = true;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			numFootContacts++;
		else if(userData == "LeftAnimatedSquareSide")
			contactLeft = true;
		else if(userData == "RightAnimatedSquareSide")
			contactRight = true;
		else if(userData == "BottomRightAnimatedSquareCorner")
			contactBottomRight = true;
		else if(userData == "BottomLeftAnimatedSquareCorner")
			contactBottomLeft = true;
	}
}

void AnimatedSquare::onEndContact(b2Contact* contact) {

	// TODO see if this can be done in a cleaner way

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			numFootContacts--;
		else if(userData == "LeftAnimatedSquareSide")
			contactLeft = false;
		else if(userData == "RightAnimatedSquareSide")
			contactRight = false;
		else if(userData == "BottomRightAnimatedSquareCorner")
			contactBottomRight = false;
		else if(userData == "BottomLeftAnimatedSquareCorner")
			contactBottomLeft = false;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			numFootContacts--;
		else if(userData == "LeftAnimatedSquareSide")
			contactLeft = false;
		else if(userData == "RightAnimatedSquareSide")
			contactRight = false;
		else if(userData == "BottomRightAnimatedSquareCorner")
			contactBottomRight = false;
		else if(userData == "BottomLeftAnimatedSquareCorner")
			contactBottomLeft = false;
	}
}

void AnimatedSquare::jump(void) {

	if(numFootContacts > 0)
		body->ApplyLinearImpulse(b2Vec2(0.f, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactLeft)
		body->ApplyLinearImpulse(b2Vec2(body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactRight)
		body->ApplyLinearImpulse(b2Vec2(-body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);
}

void AnimatedSquare::impulseDown(void) {

	body->ApplyLinearImpulse(b2Vec2(0.f,500.f),body->GetWorldCenter(),true);
}

std::string AnimatedSquare::getInfo(void) const {

	std::string ret("grounded : ");
	ret += numFootContacts > 0 ? "TRUE" : "";
	ret += "\nleftContact : ";
	ret += contactLeft ? "TRUE" : "";
	ret += "\nrightContact : ";
	ret += contactRight ? "TRUE" : "";
	ret += "\nbottomLeftContact : ";
	ret += contactBottomLeft ? "TRUE" : "";
	ret += "\nbottomRightContact : ";
	ret += contactBottomRight ? "TRUE" : "";
	return ret;
}