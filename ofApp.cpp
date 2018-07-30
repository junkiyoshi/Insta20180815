#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<ofPoint> points;
	vector<int> sizes;
	for (int i = 0; i < 192; i++) {

		ofPoint point(ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetHeight()));
		points.push_back(point);
		sizes.push_back(1);
	}

	for (int out_index = 0; out_index < points.size(); out_index++) {

		for (int in_index = out_index + 1; in_index < points.size(); in_index++) {

			if (points[out_index].distance(points[in_index]) < 50) {

				ofDrawLine(points[out_index], points[in_index]);
				sizes[out_index]++;
				sizes[in_index]++;
			}
		}
	}

	for (int i = 0; i < points.size(); i++) {

		ofDrawCircle(points[i], sizes[i]);
	}

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}