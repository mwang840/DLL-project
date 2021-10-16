#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numSongs = 0;
	}
	DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,l,m,s);
		first = n;
		last = n;
		numSongs=1;
	}

	//Pushing the node to the end of the list
	// TODO: Format else statement, last's prev property is currently pointing to itself, make sure you account for all pointers that are involved
	void DLL::push(string t, string a, int m, int s){
		DNode *node = new DNode(t, a, m, s);
		if(first == NULL){
			first = node;
			last = node;
		}
		else{
			last->prev = last;
			last->next = node;
			node->next = NULL;
			last = node;
		}

	}

	//Prints out the list in each node
	void DLL::printList(){
		if(first == NULL){
			cout<<"Empty List"<<endl;
		}
		else{
			DNode *tmpFirst = first;
			cout<<"The elements of the list are: " << endl;
			while(tmpFirst != NULL){
				tmpFirst->song->printSong(); // DNode.printSong   DNode.song.printSong
				tmpFirst= tmpFirst->next;
			}
		}
	}

	//Removes the song title from the list if any exist
	//Returns the index of the title being removed
	// TODO: Modify the first if, make sure you're returning the right index and removing it properly, make sure you can remove nodes besides the first and last
	int DLL::remove(string t){
		int index = 0;
		Song *s = new Song();
		DNode *current = new DNode();
		Song *next = new Song();
		DNode *temp = new DNode();
		current = first;
		if(first->song->title == t){
			temp = first;
			first = first->next;
			cout<<"Removing";
			first->song->printSong();
			delete first;
			numSongs--;
			index = 0;
		}
		while(current->next != NULL){
			if(current->song->title == t && (current == last)){
				pop();
			}
			index++;
			current = current->next;
		}
		return index;
	}

	// TODO: may crash or return an invalid value, not 100% sure
	//Pops the last node off the list, will return the last object of the node
	Song *DLL::pop(){
		Song *object = last->song;

		if(first == NULL){
			return NULL;
		}

		else if(first->next == NULL){
			delete first;
			delete last;
			return object;
		}
		else{
			delete last;
			return object;
		}

	}

	//// moves song with title s up one in the playlist.
    //If it is at the beginning of the list,
    //it will be moved to the end of the list.
	// TODO: Format 
	void DLL::moveUp(string t){
		DNode *current = new DNode();
		current = first;
		if(first == NULL){
			cout<<"List is empty";
		}

		if(first->song->title == t){
			last = first;
			first = first->prev;
		}
		//Check if the last node is the node if is trying moving
		if((last->song->title == t)){
			last->prev = first->next;

			last->next = last->prev;
			// this isnt quite working properly
		}
		//Condition 1 if list is only one nodes, list is unchanged
		if(numSongs == 1){
			last = first;
		}

		//Condition 2 if there are two nodes, swap the two, the list could have more then 2
		if(numSongs >= 2){
			DNode *temp = last;
			last = first;
			first = temp;
		}

		//Condition 3 if there are three nodes, move each one up, the one that is being changed moves to the bottom
		if(numSongs == 3){
			DNode *temp = last;
			//shift other two nodes up
			first->next = first;
			last->prev = first->next;
			first = temp;
		}

		//Condition 4
		if(numSongs == 4){
			DNode *temp = last;
		}
		while(last != NULL){
			last = last->prev;
			// two added functionalities in this list
			/*
			 * 1)
			 *
			 */
		}
		last->next = current;
		while(current != NULL){
			current = current->next;
		}
	}

	//moves song with title s down one in the playlist.
	//If it is at the end of the list, it will move to
	//beginning of the list.
	// TODO: format similar to moveDown
	void DLL::moveDown(string t){
		DNode *current = new DNode();
		current = last;
		if(first == NULL){
			cout<<"List is empty";
		}
		if(last->song->title == t){
			first = last;
		}
		first->next = current;
		while(current != NULL){
			current = current->next;
		}
	}

	// gets the total list duration in minutes (passed in as pointers)
	// and seconds (again, passed in as pointers)
	void DLL::listDuration(int *tm, int *ts){
		DNode *current = first;
		int duration, altduration;
		duration = 0;
		altduration = 0;
		while(current != NULL){
			duration += current->song->min;
			altduration += current->song->sec;
			current = current->next;
		}
		if(altduration >= 60){
			altduration = altduration / 60;
			duration += altduration % 60;
		}
		*tm = duration;
		*ts = altduration;
		cout<<"Duration: "<<duration<< ":" << altduration <<endl;

	}

	//Makes a random list for the songs
	void DLL::makeRandom(){

		DNode *current = new DNode();

		while(current != NULL)
		{
			for(int i = 0; i < numSongs; ++i){
				int random = rand() % 2;
				if(random == 0){
					moveUp(current->song->title);
				}
				else{
					moveDown(current->song->title);
				}
			}
			current = current ->next;

		}

	}

	//Destructor for dll
	// TODO: you (maybe) will have to delete the song inside the pointer too (double check this)
	DLL::~DLL(){
		// TODO: Pay attention to types (make sure they match)
		cout<<"deleting pointers..."<<endl;
		DNode *current  = first;
		DNode *temp;
		Song *s;
		while(current != NULL){
			temp = current->next->song;
			delete current;
			current = temp;
		}
		cout<<"List is deleted"<<endl;
	}

