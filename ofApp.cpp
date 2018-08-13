#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofSetLineWidth(3);
	ofSetCircleResolution(72);

	this->box2d.init();
	this->box2d.enableEvents();
	this->box2d.setGravity(0, 10);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

	for (int i = 0; i < 3; i++) {

		unique_ptr<Particle> particle(new Particle(this->box2d, ofPoint(i * 240 + 120, i % 2 == 1 ? ofGetHeight() * 0.4 : ofGetHeight() * 0.6), true));
		this->particles.push_back(std::move(particle));
	}

}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 45 == 0) {

		unique_ptr<Particle> particle(new Particle(this->box2d, ofPoint(ofRandom(ofGetWidth()), ofGetHeight() * 0.05)));
		this->particles.push_back(std::move(particle));
	}

	for (int i = this->particles.size() - 1; i >= 0; i--) {

		this->particles[i]->Update();

		if (this->particles[i]->IsDead()) {

			this->particles.erase(this->particles.begin() + i);
		}
	}

	for (int i = this->waves.size() - 1; i >= 0; i--) {

		if (get<WaveFileds::Life>(this->waves[i])++ > 120) {

			this->waves.erase(this->waves.begin() + i);
		}
	}

	this->box2d.update();
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofNoFill();
	for (int i = 0; i < this->waves.size(); i++) {

		ofSetColor(get<WaveFileds::Color>(this->waves[i]));
		ofDrawCircle(get<WaveFileds::Point>(this->waves[i]), get<WaveFileds::Life>(this->waves[i]));
	}

	for (int i = 0; i < this->particles.size(); i++) {

		this->particles[i]->Draw();
	}
}


//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		if (e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {

			Particle* p_a = (Particle*)e.a->GetBody()->GetUserData();
			Particle* p_b = (Particle*)e.b->GetBody()->GetUserData();
			if (p_a != nullptr && p_b != nullptr) {

				if (p_a->IsObstruct() && p_b->IsObstruct() == false) {

					p_a->SetColor(p_b->GetColor());
					p_b->PlaySound();

					tuple<ofPoint, ofColor, float> wave = make_tuple(p_a->GetPoint(), p_b->GetColor(), 80);
					this->waves.push_back(wave);
				}

				if (p_b->IsObstruct() && p_a->IsObstruct() == false) {

					p_b->SetColor(p_a->GetColor());
					p_a->PlaySound();

					tuple<ofPoint, ofColor, float> wave = make_tuple(p_b->GetPoint(), p_a->GetColor(), 80);
					this->waves.push_back(wave);
				}
			}

			return;
		}
	}
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {

	if (e.a != NULL && e.b != NULL) {

		// do nothing
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}