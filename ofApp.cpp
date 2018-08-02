#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(2);

	this->font_size = 130;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<char> characters = { 'A', 'B', 'C', 'D', 'E',
								'V', 'W', 'X', 'Y', 'Z'};
	for (int character_index = 0; character_index < characters.size(); character_index++) {

		ofPoint location = character_index < 5 ? ofPoint(ofGetWidth() * 0.25, this->font_size * 0.7 + (this->font_size + 3) * character_index) : ofPoint(ofGetWidth() * 0.75, this->font_size * 0.7 + (this->font_size + 3) * (character_index - 5));
		ofPushMatrix();
		ofTranslate(location);

		ofPath path = this->font.getCharacterAsPoints(characters[character_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		ofBeginShape();
		for (int outline_index = 0; outline_index < (int)outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(180);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < (int)vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x + this->font_size * -0.5, vertices[vertices_index].y + this->font_size * 0.5, vertices[vertices_index].z);
				float noise_value = ofMap(ofNoise(character_index, ofGetFrameNum() * 0.008), 0, 1, this->font_size * -0.5, this->font_size * 0.5);

				if (noise_value < 0) {

					point.x += point.x < noise_value ? -80 : 80;
				}
				else {

					point.x += point.x > noise_value ? 80 : -80;
				}

				ofVertex(point);
			}
		}

		ofEndShape();
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}