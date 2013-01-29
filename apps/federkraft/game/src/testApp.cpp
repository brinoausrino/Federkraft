#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    
    //init serial
    initSerial();
    
	
    //init points
  
    pointsP1 = 0;
    pointsP2 = 0;
    pointsToWin = 10;
    
    
    // init physics

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
    player.push_back(new Player());
    player[0]->setup(box2d.getWorld(),400,400,50);
	player[0]->setPhysics(1.0, 0.5, 0.3);
	player[0]->setupTheCustomData();
    player[0]->setPosition(200, 100);
    
    player.push_back(new Player());
    player[1]->setup(box2d.getWorld(),400,400,50);
	player[1]->setPhysics(1.0, 0.5, 0.3);
	player[1]->setupTheCustomData();
    player[1]->setPosition(700, 200);
    player1y = 200;

    wall.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()-100, 10, 100);
	wall.setPhysics(1.0, 0.5, 0.3);
    
    
     ball.setPhysics(3.0, 0.53, 0.1);
     ball.setup(box2d.getWorld(), 300, 35, 20);
     circles.push_back(ball);

}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	
    
    //update player
    player[1]->setPosition(mouseX, ofGetHeight()- player1y);
    
    
    ofPoint pos = player[0]->getPosition();
    pos.x += accX; 
    //cout << player1.getPosition() << " " <<accX << " " << pos.x << endl;
    
    player[0]->setPosition(pos.x, ofGetHeight()-80 + accY + pressure);
    
    //update forces
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	float minDis = 200;
    
    float dis = mouse.distance(ball.getPosition());
	
	Data* theData = (Data*)player[0]->getData();
    
	if( ofGetMousePressed() && minDis > dis)
    {
        ball.addAttractionPoint(mouse, 4.0);
    }
    else if (minDis > dis)
    {
        ball.addRepulsionForce(mouse, 9);
    }
	
}


//--------------------------------------------------------------
void testApp::draw() {
	
    player[0]->draw();
    player[1]->draw();
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].draw();
	}

    wall.draw();
    
	// draw the ground
	box2d.drawGround();
	
	
	
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    info += "accX: "+ofToString(accX, 2)+"\n";
    info += "accY: "+ofToString(accY_, 2)+"\n";
    info += "accZ: "+ofToString(accZ_, 2)+"\n";
    info += "gyroX: "+ofToString(gyroX, 2)+"\n";
    info += "gyroY: "+ofToString(gyroY, 2)+"\n";
    info += "gyroZ: "+ofToString(gyroZ, 2)+"\n";
    info += "pressure_: "+ofToString(pressure_, 2)+"\n";
    info += "speed: "+ofToString(player[0]->getVelocity(), 2)+"\n";
    
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	
    if(key == 'c') {
		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), mouseX, mouseY, r);
		circles.push_back(circle);
	}
	
	else if(key == 'b') {
		float w = ofRandom(4, 20);	
		float h = ofRandom(4, 20);	
		ofxBox2dRect rect;
		rect.setPhysics(3.0, 0.53, 0.1);
		rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		boxes.push_back(rect);
	}
    
    else if(key == 'v') {
        
        //ofxBox2dCircle ball;
		ball.setPhysics(3.0, 0.53, 0.1);
		ball.setup(box2d.getWorld(), 300, 35, 20);
        circles.push_back(ball);
	}
    
	
	else if(key == 't') ofToggleFullscreen();
    
    else if(key == 'r')
    {
        ball.setPosition(700,50);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	player1y = 150;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    player1y = 200;
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

void testApp::initSerial()
{
    _serial.setup("tty.usbmodemfa131", 9600);
    //_serial.setup("tty.usbserial-A600K2BH", 9600);
    _serial.startContinuesRead();
    ofAddListener(_serial.NEW_MESSAGE,this,&testApp::onNewMessage);
	_serial.sendRequest();
    
	accXraw=0;
	accYraw=0;
	accZraw=0;
	gyroX=0;
	gyroY=0;
	gyroZ=0;
	pressure=0;
    
    
	accX_=0;
	accY_=0;
    accZ_=0;
	pressure_=10;
	gyroZ_=90;
    
    centerAccX = 223;
    centerAccY = 150;
}

void testApp::onNewMessage(string & message)
{
  //  cout << message << endl;
    int count = 0;
    for (int i=0; i<message.size(); ++i) {
        if (message[i] == '|') {
            ++count;
        }
    }
    
    if (message.length() > 2) {
        
        if (message[0] == 'a' && count == 3){
            int l = message.length();
            string v = "";
            for (int i=1; i<l; ++i) {
                v+=message[i];
            }
			accXraw=ofToInt(ofSplitString(v, "|")[0]);
            accYraw=ofToInt(ofSplitString(v, "|")[1]);
			accZraw=ofToInt(ofSplitString(v, "|")[2]);
            pressureRaw = ofToInt(ofSplitString(v, "|")[3]);
        }
        else if (message[0] == 'g' && count == 2){
            int l = message.length();
            string v = "";
            for (int i=1; i<l; ++i) {
                v+=message[i];
            }
			gyroX=ofToInt(ofSplitString(v, "|")[0]);
            gyroY=ofToInt(ofSplitString(v, "|")[1]);
			gyroZ=ofToInt(ofSplitString(v, "|")[2]);
        }
        
		else if (message[0] == 'p') {
            int l = message.length();
            string v = "";
            for (int i=1; i<l; ++i) {
                v+=message[i];
            }
            pressureRaw = ofToInt(v);
        }
    }    
    /*
	accX_=accX_*0.8+0.2*accXraw;
	accY_=accY_*0.8+0.2*accYraw;
    accZ_=accZ_*0.8+0.2*accZraw;
    */
    
    accX_=accXraw;
	accY_=accYraw;
    accZ_=accZraw;
    
    //map acc on scale
    accX = ofMap(accX_, centerAccX-1000, centerAccX+1000, -10, 10);
    accY = ofMap(accY_, centerAccY-1000, centerAccY + 1000, -20, 20);
    
    
	gyroZ_+=gyroZ;
    
    
    
	pressure_=pressure_*0.8+0.2*pressureRaw;
	
    //map pressure
    pressure = ofMap(pressure_, 20, 50, 0, 40);
    
    /*
    //acc
	squirrelModel.setRotation(0, accX_/12+180, 1, 0, 0);
	
	squirrelModel.setRotation(1, accY_/-12, 0, 0, 1);
	//gyro
	squirrelModel.setRotation(2, gyroZ_/400, 0, 1, 0);
    
    
	squirrelModel.setScale((40/(float)pressure_), (40/(float)pressure_), (40/(float)pressure_));*/
}
