#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofSetColor(239);
	ofBackground(39);
	ofSetBackgroundAuto(false);
	ofSetLineWidth(3);

	string sound_path_list[] = { "sound/pianoC.mp3", "sound/pianoD.mp3", "sound/pianoE.mp3", "sound/pianoF.mp3", "sound/pianoG.mp3", "sound/pianoA.mp3", "sound/pianoB.mp3", "sound/pianoC2.mp3" };
	for (int i = 0; i < 8; i++) {

		ofSoundPlayer sound;
		sound.load(sound_path_list[i]);
		sound.setVolume(0.2);
		sound.setMultiPlay(true);

		this->sounds.push_back(sound);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(39, 64);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(239);

	for (int i = 1; i <= 6; i++) {

		float noise_value = ofNoise(i, ofGetFrameNum() * 0.005);
		ofPoint point = ofPoint(noise_value * ofGetWidth(), i * 102);
		ofFill();
		ofDrawCircle(point, 30);
		
		if (ofGetFrameNum() % (i * 15) == 0) {

			int index = noise_value * 8;
			this->sounds[index].play();

			ofNoFill();
			ofDrawCircle(point, 50);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}