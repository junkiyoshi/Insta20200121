#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	int radius = 60;
	int len = 40;
	int deg_span = 8;
	int x_span = 256;
	int y_span = 240;
	bool flg = true;
	for (int x = x_span * 0.5; x < ofGetWidth(); x += x_span) {

		for (int y = y_span * 0.5; y < ofGetHeight(); y += y_span) {

			for (int deg = 0; deg < 360; deg += deg_span) {

				int index = this->face.getNumVertices();
				auto noise_param = glm::vec2(x + cos((deg + deg_span * 0.5) * DEG_TO_RAD), y + sin((deg + deg_span * 0.5) * DEG_TO_RAD));
				auto noise_value = ofNoise(noise_param.x, noise_param.y, ofGetFrameNum() * 0.01);

				auto tmp_radius = radius;
				if (noise_value > 0.75) { tmp_radius += ofMap(noise_value, 0.75, 1, 0, 40); }
				if (noise_value < 0.25) { tmp_radius -= ofMap(noise_value, 0.25, 0, 0, 40); }

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(x, y, 0) + glm::vec3((tmp_radius + len * 0.5) * cos(deg * DEG_TO_RAD), (tmp_radius + len * 0.5) * sin(deg * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3(x, y, 0) + glm::vec3((tmp_radius + len * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (tmp_radius + len * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3(x, y, 0) + glm::vec3((tmp_radius - len * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (tmp_radius - len * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3(x, y, 0) + glm::vec3((tmp_radius - len * 0.5) * cos(deg * DEG_TO_RAD), (tmp_radius - len * 0.5) * sin(deg * DEG_TO_RAD), 0));

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
				this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
				this->frame.addIndex(index + 3); this->frame.addIndex(index + 0);

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(flg ? ofColor(39) : ofColor(239));
					this->frame.addColor(flg ? ofColor(239) : ofColor(39));
				}
			}

			flg = !flg;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->face.draw();
	this->frame.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}