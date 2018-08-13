#include "Particle.h"

Particle::Particle(ofxBox2d& box2d, ofPoint point, bool is_obstruct) {

	string sound_path_list[] = { "sound/pianoC.mp3", "sound/pianoD.mp3", "sound/pianoE.mp3", "sound/pianoF.mp3", "sound/pianoG.mp3", "sound/pianoA.mp3", "sound/pianoB.mp3", "sound/pianoC2.mp3" };

	this->circle = new ofxBox2dCircle();
	if (is_obstruct) {

		this->circle->setPhysics(0.0, 1.0, 1.0);
		this->circle->setup(box2d.getWorld(), point.x, point.y, 80);
		this->circle->setData(this);

		this->sound_type = -1;
		this->color = ofColor(39);
	}
	else {

		this->circle = new ofxBox2dCircle();
		this->circle->setPhysics(1.0, 0.3, 1.0);
		this->circle->setup(box2d.getWorld(), point.x, point.y, 15);
		this->circle->setData(this);

		this->sound_type = ofRandom(8);
		this->sound.load(sound_path_list[sound_type]);
		this->sound.setMultiPlay(true);
		this->sound.setVolume(0.5);

		this->color.setHsb(ofMap(this->sound_type, 0, 7, 0, 255), 255, 255);
	}

	this->life = 255.f;
	this->is_obstruct = is_obstruct;
}

Particle::~Particle(){

	if (this->circle != nullptr) {

		this->circle->destroy();
		delete this->circle;
	}
}

void Particle::Update() {

	if (this->is_obstruct == false) {

		this->life -= 1.0;
	}
}

void Particle::Draw() {

	ofFill();
	ofSetColor(this->color, this->life > 64 ? 255 : ofMap(this->life, 0, 64, 0, 255));
	ofDrawCircle(this->circle->getPosition(), this->circle->getRadius());

	if (this->is_obstruct == false) {

		ofNoFill();
		ofSetColor(this->color);
		ofDrawCircle(this->circle->getPosition(), this->circle->getRadius());
	}
}

void Particle::PlaySound() {

	if (this->is_obstruct) {

		return;
	}

	this->sound.play();
}

void Particle::SetColor(ofColor color) { this->color = color; }
ofColor Particle::GetColor() { return this->color; }
ofPoint Particle::GetPoint() { return this->circle->getPosition(); }
bool Particle::IsObstruct() { return this->is_obstruct; }
bool Particle::IsDead() { return this->life < 0 ? true : false; }