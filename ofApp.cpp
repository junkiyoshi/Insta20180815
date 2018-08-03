#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float radius = 300;
	int small_radius = 80;
	int deg_span = 10;
	int small_deg_span = 10;

	for (int deg = 0; deg < 360; deg += deg_span) {

		ofColor color = deg % (deg_span * 2) == 0 ? ofColor(239, 39, 39) : ofColor(39, 39,239);

		int start_small_deg = ofGetFrameNum() * 3 + deg;
		for (int small_deg = start_small_deg; small_deg < start_small_deg + 360; small_deg += small_deg_span) {

			color.setHsb(ofMap(small_deg, start_small_deg, start_small_deg + 360, 0, 255), 230, 230);
			ofSetColor(color);

			ofBeginShape();

			ofVertex(this->make_point(radius, small_radius, deg, small_deg));
			ofVertex(this->make_point(radius, small_radius, deg + deg_span, small_deg));
			ofVertex(this->make_point(radius, small_radius, deg + deg_span, small_deg + small_deg_span));
			ofVertex(this->make_point(radius, small_radius, deg, small_deg + small_deg_span));

			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_point(float radius, float small_radius, float deg, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return ofPoint(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}