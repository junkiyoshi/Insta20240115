#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 7);
	this->base_mesh = ico_sphere.getMesh();

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();

	for (auto v : this->base_mesh.getVertices()) {

		for (int i = 0; i < 4; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec2(v.x * 0.001, ofGetFrameNum() * 0.005)), 0, 1, -60, 60) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec2(v.y * 0.001, ofGetFrameNum() * 0.005)), 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec2(v.z * 0.001, ofGetFrameNum() * 0.005)), 0, 1, -60, 60) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
			auto radius = ofMap(ofNoise(glm::vec4(v * 0.004, ofGetFrameNum() * 0.02)), 0, 1, 150, 300);

			v = glm::normalize(v) * radius;
			v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
		
		}

		this->draw_mesh.addVertex(v);
		this->draw_mesh.addColor(ofColor(255, 64));
	}

	this->draw_mesh.addIndices(this->base_mesh.getIndices());
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2.88);

	this->draw_mesh.drawVertices();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}