/*
 *  Player.cpp
 *  Simple Example
 *
 *  Created by Brian Eschrich on 24.01.13
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Player.h"




void Player::setupTheCustomData() {
    
    static int colors[] = {0xcae72b, 0xe63b8f, 0x2bb0e7};
    static string abc   = "abcdefghijklmnopqrstuvwxyz";
    
    // we are using a Data pointer because 
    // box2d needs to have a pointer not 
    // a referance
    setData(new Data());
    Data * theData = (Data*)getData();
    
    theData->name = "player";
    theData->id = ofRandom(0, 100);
    theData->isActive = false;
   /* theData->name += abc[(int)ofRandom(0, abc.size())];
    theData->color.setHex(colors[(int)ofRandom(0, 3)]);*/
    
    printf("setting the custom data!\n");
    
}

void Player::draw() {
    Data* theData = (Data*)getData();
    if(theData) {
        
        // Evan though we know the data object lets just 
        // see how we can get the data out from box2d
        // you would use this when using a contact listener
        // or tapping into box2d's solver.
        
        float radius = getRadius();
        ofPushMatrix();
        ofTranslate(getPosition());
        ofRotateZ(getRotation());
       // ofSetColor(theData->color);
        ofSetColor(128,255,0);
        ofFill();
        ofCircle(0, 0, radius);	
        
        ofSetColor(255);
        //ofDrawBitmapString(theData->name, -5, 5);
        ofPopMatrix();
    }
}