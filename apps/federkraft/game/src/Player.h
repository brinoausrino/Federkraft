/*
 *  Player.h
 *  Simple Example
 *
 *  Created by Brian Eschrich on 24.01.13
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Player
#define _Player

#include "ofMain.h"
#include "ofxBox2d.h"


//data class
class Data {
public:
    string name;
    int		id;
    bool isActive;
};


class Player : public ofxBox2dCircle{
	
  public:
	
	Player(){};
	
	void setupTheCustomData();
	void draw();
	
};

#endif
