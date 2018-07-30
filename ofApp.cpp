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
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->circles.size() - 1; i > -1; i--) {

		this->circles_life[i] -= 3;
		if (this->circles_life[i] < 0) {

			this->circles[i].get()->destroy();
			this->circles.erase(this->circles.begin() + i);
			this->circles_life.erase(this->circles_life.begin() + i);
		}
	}
	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->circles.size(); i++) {

		ofSetColor(39, this->circles_life[i]);
		ofDrawCircle(this->circles[i].get()->getPosition(), 4);
		for (int j = i + 1; j < this->circles.size(); j++) {

			float distance = this->circles[i].get()->getPosition().distance(this->circles[j].get()->getPosition());
			if (distance < 50) {

				ofDrawLine(this->circles[i].get()->getPosition(), this->circles[j].get()->getPosition());
				ofSetColor(39, this->circles_life[j]);
				ofDrawLine(this->circles[i].get()->getPosition(), this->circles[j].get()->getPosition());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	int color_base = ofRandom(256);
	float radius = 10;
	for (int i = 0; i < 3; i++) {

		int color_value = (color_base + i * 20) % 255;
		for (int deg = 0; deg < 360; deg += 10) {

			float tmp_x = radius * cos(deg * DEG_TO_RAD);
			float tmp_y = radius * sin(deg * DEG_TO_RAD);

			this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
			this->circles.back().get()->setPhysics(3.0, 0.5, 0.1);
			this->circles.back().get()->setup(this->box2d.getWorld(), ofGetWidth() * 0.5 + tmp_x, ofGetHeight() * 0.5 + tmp_y, 4);
			this->circles.back().get()->addForce(ofVec2f(tmp_x, tmp_y), 8.0);

			this->circles_life.push_back(255);
		}

		radius += 3;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}