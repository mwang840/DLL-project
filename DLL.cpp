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
	void DLL::push(string t, string a, int m, int s){
		DNode* node = new DNode(t, a, m, s);
		node->prev = last;
		last = node;
		node->next = NULL;
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

	//Pops the last node off the list, will return the last object of the node
	Song *DLL::pop(){
		Song *next = new Song();
		Song *object = last->song;

		if(first == NULL){
			return NULL;
		}

		else if(first->next == NULL){
			return NULL;
		}
		else{
			last = last->next;
			delete last;
			return object;
		}

	}

	//// moves song with title s up one in the playlist.
    //If it is at the beginning of the list,
    //it will be moved to the end of the list.
	void DLL::moveUp(string t){
		DNode *current = new DNode();
		current = first;
		if(first->song->title == t){
			last = first;
		}
		while(current != NULL){
			current = current->next;
		}

		printList();
	}

	//moves song with title s down one in the playlist.
	//If it is at the end of the list, it will move to
	//beginning of the list.
	void DLL::moveDown(string t){
		DNode *current = new DNode();
		current = last;
		if(last->song->title == t){
			first = last;
		}
		while(current != NULL){
			current = current->next;
		}
	}

	// gets the total list duration in minutes (passed in as pointers)
	// and seconds (again, passed in as pointers)
	void DLL::listDuration(int *tm, int *ts){

	}

	//
	void DLL::makeRandom(){

	}

	//Destructor for dll
	DLL::~DLL(){
		cout<<"deleting pointers..."<<endl;
		DNode *current  = first;
		DNode *temp;
		while(current != NULL){
			temp = current->next;
			delete current;
			current = temp;
		}
		cout<<"List is deleted"<<endl;
	}

