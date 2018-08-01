#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofSetLineWidth(3);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	this->radius = 12;
	this->range = 1000; // I made mistake of value. But I like it.

	for (int i = 0; i < 128; i++) {

		this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
		this->circles.back().get()->setPhysics(0.5, 0.5, 0.1);
		this->circles.back().get()->setup(this->box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), this->radius);

		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);
		this->circles_color.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->circles.size(); i++) {

		for (int j = i + 1; j < this->circles.size(); j++) {

			float distance = this->circles[i]->getPosition().distance(this->circles[j]->getPosition());
			if (distance < this->range) {

				this->circles[i]->addForce(this->circles[i]->getPosition() - this->circles[j]->getPosition(), ofMap(distance, 0, this->range, 1.2, 0.1));
				this->circles[j]->addForce(this->circles[j]->getPosition() - this->circles[i]->getPosition(), ofMap(distance, 0, this->range, 1.2, 0.1));
			}
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->circles.size(); i++) {
		
		for (int j = i + 1; j < this->circles.size(); j++) {

			float distance = this->circles[i]->getPosition().distance(this->circles[j]->getPosition());
			if (distance < this->range) {

				ofSetColor(this->circles_color[i], 10);
				ofDrawLine(this->circles[i]->getPosition(), this->circles[j]->getPosition());

				ofSetColor(this->circles_color[j], 10);
				ofDrawLine(this->circles[i]->getPosition(), this->circles[j]->getPosition());
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}