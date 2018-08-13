#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Particle
{
public:
	Particle(ofxBox2d& box2d, ofPoint point, bool is_obstruct = false);
	~Particle();

	void Update();
	void Draw();
	void PlaySound();

	void SetColor(ofColor color);
	ofColor GetColor();
	ofPoint GetPoint();
	bool IsObstruct();
	bool IsDead();
private:

	ofxBox2dCircle* circle = nullptr;
	int sound_type; // 0 - 7
	ofSoundPlayer sound;
	ofColor color;
	float life;
	bool is_obstruct;
};

