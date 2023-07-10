#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	width = 50;
	height = 50;
	//
	_messyMesh = false;
	_perlinMesh = false;
	_wireframe = true;
	//
	perlinRange = 1.0;
	perlinHeight = 5.0;
	//
	ofBackground(255);
	camera.setPosition(0, 0, 80);

	// Adding vertices 
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			terrain.addVertex(ofPoint(x - width/2, y - height / 2, 0));
			terrain.addColor(ofFloatColor(0, 0, 0));
		}
	}
	//Connecting vertices
	for (int y = 0; y < height-1; y++)
	{
		for (int x = 0; x < width-1; x++) {
			terrain.addIndex(x + y * height);
			terrain.addIndex((x + 1) + y * height);
			terrain.addIndex(x + (y + 1)*height);

			terrain.addIndex((x + 1) + y * height);
			terrain.addIndex((x + 1) + (y + 1)*height);
			terrain.addIndex(x + (y + 1)*height);
		}
	}

	//float old_x = 50;
	//float mapped_x = 0;

	//mapped_x = ofMap(old_x, 0, 100, 500, 100); //returns 300

	//std::cout << mapped_x;  //prints 300


	/*float amplitude = 250;
	float speed = 0.5;
	float noise = amplitude * ofNoise(ofGetElapsedTimef() * speed);*/
	//variables names are self-explanatory here


}

//--------------------------------------------------------------
void ofApp::update(){
	//updating z value for each vertex
	if (_messyMesh)
	{
		for (int i = 0; i < terrain.getNumVertices(); i++)
		{
			ofVec3f newPos = terrain.getVertex(i);//return x,y,z position of the current vertex
			newPos.z = ofRandom(-1.0, 1.0);
			
			terrain.setVertex(i, newPos); //updated position with z
		}
	}
	//perlin noise

	if (_perlinMesh)
	{
		int k = 0;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++ ) {
				ofVec3f newCoordinate = terrain.getVertex(k); //retrieve current coordinate
				newCoordinate.z = ofNoise(ofMap(i, 0, width, 0, perlinRange), ofMap(j, 0, height, 0, perlinRange))*perlinHeight; //update coordinate
				terrain.setVertex(k, newCoordinate); //set coordinates as new coordinate
				
				k++;

			}
		}
	}


	
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	if (_wireframe)
	{
		terrain.drawWireframe();
	}
	else
	{
		terrain.drawVertices();
	}
	camera.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'f':
		ofToggleFullscreen();
		break;
	
	case ' ':
		if (_perlinMesh)
		{
			_perlinMesh = !_perlinMesh;
		}
		_messyMesh = !_messyMesh;
		
		break;

	case 'w':
		_wireframe = !_wireframe;

	case 'p':
		if (_messyMesh)
		{
			_messyMesh = !_messyMesh;
		}
		_perlinMesh = !_perlinMesh;
		
		break;

	case OF_KEY_UP:
		perlinRange += 0.1;
		break;

	case OF_KEY_DOWN:
		if (perlinRange>0.1)
		{
			perlinRange -= 0.1;
		}
		break;

	case OF_KEY_RIGHT:
		perlinHeight += 0.1;
		break;
	
	case OF_KEY_LEFT:
		if (perlinHeight>0.1)
		{
			perlinHeight -= 0.1;
		}
		break;

	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
