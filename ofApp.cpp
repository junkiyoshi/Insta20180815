#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(3);

	string sound_path_list[] = { "sound/pianoC2.mp3", "sound/pianoB.mp3", "sound/pianoA.mp3", "sound/pianoG.mp3", "sound/pianoF.mp3", "sound/pianoE.mp3", "sound/pianoD.mp3","sound/pianoC.mp3" };
	for (int i = 0; i < 8; i++) {

		ofSoundPlayer sound;
		sound.load(sound_path_list[i]);
		sound.setVolume(0.2);
		sound.setMultiPlay(true);
		this->sounds.push_back(sound);

		ofColor color;
		color.setHsb(i * 35, 255, 230);
		this->sound_color.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 144;
	for (int x = 0; x < ofGetWidth(); x += span) {

		int noise_value = ofMap(ofNoise(x * 0.0005 + ofGetFrameNum() * 0.008), 0, 1, 0, this->sounds.size());
		int next_noise_value = ofMap(ofNoise(x * 0.0005 + (ofGetFrameNum() + 1) * 0.008), 0, 1, 0, this->sounds.size());

		ofFill();
		ofSetColor(this->sound_color[next_noise_value]);
		ofDrawRectangle(x, 0, x + span, ofGetHeight());

		ofNoFill();
		ofSetColor(239);
		ofDrawRectangle(x, 0, x + span, ofGetHeight());

		if (noise_value != next_noise_value) {

			this->sounds[next_noise_value].play();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}