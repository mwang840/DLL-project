/*
 * DNode.cpp
 *
 *  Created on: Sep 29, 2021
 *      Author: kabut
 */
#include "DNode.hpp"

#include <iostream>
using namespace std;

//Default constructor for the DNode class
DNode::DNode(){
	song = NULL;
	prev = NULL;
	next = NULL;
	// some objects are complex, and the default delete won't quite get rid of the whole object, so for destructors,
	// you're kind of telling the computer how to delete the object
}

//Constructor for the DNode class
DNode::DNode(string s, string a, int lenmin, int lensec){
	song = new Song(s,a,lenmin,lensec);
	prev = NULL;
	next = NULL;
}




