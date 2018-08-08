#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Particle
{
public:

	Particle(ofxBox2d& box2d, ofPoint point, float radius);
	~Particle();

	void Update();
	void Draw();

	void SetColor(ofColor color);
	ofColor GetColor();
	ofPoint GetVelocity();
	bool IsDead();
private:

	ofxBox2dCircle* circle = nullptr;
	ofColor color;
	float life;
};

