#include "Particle.h"

Particle::Particle(ofxBox2d& box2d, ofPoint point, float radius)
{
	this->circle = new ofxBox2dCircle();
	this->circle->setPhysics(1.0, 0.5, 1.0);
	this->circle->setup(box2d.getWorld(), point.x, point.y, radius);
	this->circle->setData(this);

	this->color.setHsb(ofRandom(255), 255, 230);
	this->life = 255;
}

Particle::~Particle()
{
	if (this->circle != nullptr) {

		this->circle->destroy();
		delete this->circle;
	}
}

void Particle::Update() {

	this->life -= 0.75;
}

void Particle::Draw() {

	ofSetColor(this->color, this->life > 64 ? 255 : ofMap(this->life, 0, 64, 0, 255));
	ofDrawCircle(this->circle->getPosition(), this->circle->getRadius());
}

// Setter 
void Particle::SetColor(ofColor color) { this->color = color; }

// Getter
ofColor Particle::GetColor() { return this->color; }
ofPoint Particle::GetVelocity() { return this->circle->getVelocity(); }
bool Particle::IsDead() { return this->life <= 0 ? true : false; }