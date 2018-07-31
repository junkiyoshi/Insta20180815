#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofSetLineWidth(3);

	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	this->radius = 12;
	this->range = 50;
	this->font_size = this->radius;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);

	for (int i = 0; i < 192; i++) {

		this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
		this->circles.back().get()->setPhysics(1.5, 0.5, 0.1);
		this->circles.back().get()->setup(this->box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), this->radius);

		this->near_count.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->near_count.size(); i++) {

		this->near_count[i] = 0;
	}

	for (int i = 0; i < this->circles.size(); i++) {

		for (int j = i + 1; j < this->circles.size(); j++) {

			float distance = this->circles[i]->getPosition().distance(this->circles[j]->getPosition());
			if (distance < this->range) {

				this->circles[i]->addForce(this->circles[i]->getPosition() - this->circles[j]->getPosition(), ofMap(distance, 0, this->range, 1.2, 0.1));
				this->circles[j]->addForce(this->circles[j]->getPosition() - this->circles[i]->getPosition(), ofMap(distance, 0, this->range, 1.2, 0.1));

				this->near_count[i]++;
				this->near_count[j]++;
			}
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->circles.size(); i++) {
		
		ofSetColor(39);
		ofDrawCircle(this->circles[i].get()->getPosition(), this->radius);

		for (int j = i + 1; j < this->circles.size(); j++) {

			float distance = this->circles[i]->getPosition().distance(this->circles[j]->getPosition());
			if (distance < this->range) {

				ofDrawLine(this->circles[i]->getPosition(), this->circles[j]->getPosition());
			}
		}

		ofSetColor(239);
		this->font.drawString(std::to_string(this->near_count[i]), this->circles[i].get()->getPosition().x - this->font_size * 0.5 , this->circles[i].get()->getPosition().y + this->font_size * 0.5);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}