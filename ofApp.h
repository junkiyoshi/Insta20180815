#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Particle.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

	ofxBox2d box2d;
	vector<unique_ptr<Particle>> particles;
	vector<tuple<ofPoint, ofColor, float>> waves;
};

enum WaveFileds{ Point, Color, Life };