#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSimpleSerial.h"

#include "Player.h"


// -------------------------------------------------

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
    
    //gyro - serial methods
    void onNewMessage(string & message);
    void initSerial();
	
    
    
    
    // game variables
	ofxBox2d						box2d;			  //	the box2d world
	vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	vector		<ofxBox2dRect>		boxes;			  //	defalut box2d rects
    
    ofxBox2dCircle                  ball;
    ofxBox2dRect                    wall;
    
    int                             pointsP1,pointsP2,pointsToWin;
    
    vector<Player*> player;
    
    
    //emulator variables
    int player1y;
    
    
    //gyro - serial
    ofxSimpleSerial _serial;
    int accXraw,accYraw,accZraw;
    float accX,accY,accZ;
    int gyroX,gyroY,gyroZ;
    int centerGyroX,centerGyroY,centerGyroZ;
    int centerAccX,centerAccY,centerAccZ;
    int pressure, pressureRaw;
    
    int accX_,accY_,accZ_;
    int pressure_;
    int gyroZ_;
    
    
	
};

