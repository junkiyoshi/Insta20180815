#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofSetColor(239);
	ofSetLineWidth(2);

	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(30);
	this->box2d.registerGrabbing();

	for (int i = 0; i < 128; i++) {

		float radius = 15;
		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(1.0, 0.63, 1.0);
		circle->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() / 2), ofRandom(ofGetHeight() / 2), radius);

		this->circles.push_back(circle);

		deque<ofPoint> log;
		this->circles_log.push_back(log);
	}

	this->force_fields.push_back(ofPoint(ofGetWidth() / 4, ofGetHeight() / 4));
	this->force_fields.push_back(ofPoint(ofGetWidth() / 4 * 3, ofGetHeight() / 4));
	this->force_fields.push_back(ofPoint(ofGetWidth() / 4 * 3, ofGetHeight() / 4 * 3));
	this->force_fields.push_back(ofPoint(ofGetWidth() / 4, ofGetHeight() / 4 * 3));

	this->force_field_radius = 300;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < this->circles.size(); i++) {

		shared_ptr<ofxBox2dCircle> circle = this->circles[i];
		ofPoint point = circle->getPosition();

		for (int field_index = 0; field_index < this->force_fields.size(); field_index++) {

			float distance = point.distance(this->force_fields[field_index]);
			if (distance < this->force_field_radius) {

				ofPoint p = ofPoint(this->force_field_radius * cos((field_index * 90 + 10) * DEG_TO_RAD), this->force_field_radius * sin((field_index * 90 + 10) * DEG_TO_RAD));
				circle->addForce(p, ofMap(distance, 0, this->force_field_radius, 0.1, 0.01));
			}
		}
	}

	this->box2d.update();

	for (int i = 0; i < this->circles.size(); i++) {

		this->circles_log[i].push_front(this->circles[i]->getPosition());
		while (this->circles_log[i].size() > 10) {

			this->circles_log[i].pop_back();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->circles.size(); i++) {

		float radius = this->circles[i]->getRadius();
		ofPoint point = this->circles[i]->getPosition();
		ofPoint velocity = this->circles[i]->getVelocity();

		ofPushMatrix();
		ofTranslate(point);

		float velocity_deg = atan2f(velocity.y, velocity.x) * RAD_TO_DEG;
		ofFill();
		ofBeginShape();
		for (int deg = velocity_deg; deg < velocity_deg + 270; deg += 120) {

			ofVertex(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		}
		ofEndShape(true);

		ofPopMatrix();

		ofNoFill();
		ofBeginShape();
		for (int log_index = 0; log_index < this->circles_log[i].size(); log_index++) {

			ofVertex(this->circles_log[i][log_index]);
		}
		ofEndShape(false);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}