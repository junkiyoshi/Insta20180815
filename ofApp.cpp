#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);

	this->box2d.init();
	this->box2d.enableEvents();
	this->box2d.setGravity(0, 10);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 1 == 0) {

		ofPoint point(ofRandom(ofGetWidth()), ofRandom(ofGetHeight() * 0.1));
		float radius = ofRandom(10, 15);
		unique_ptr<Particle> p(new Particle(this->box2d, point, radius));

		this->particles.push_back(std::move(p));
	}

	for (int i = this->particles.size() - 1; i >= 0; i--) {

		this->particles[i]->Update();
		if (this->particles[i]->IsDead()) {

			this->particles.erase(this->particles.begin() + i);
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->particles.size(); i++) {

		this->particles[i]->Draw();
	}
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		Particle* p_a = (Particle*)e.a->GetBody()->GetUserData();
		Particle* p_b = (Particle*)e.b->GetBody()->GetUserData();
		if (p_a != nullptr && p_b != nullptr) {

			ofPoint p_a_velocity = p_a->GetVelocity();
			ofPoint p_b_velocity = p_b->GetVelocity();
			if (p_a_velocity.length() < p_b_velocity.length()) {

				p_a->SetColor(p_b->GetColor());
			}
			else {

				p_b->SetColor(p_a->GetColor());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		// do nothing
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}