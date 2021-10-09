
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
	int remove(string t){
		int removed = 0;
		Song *title = new Song();
		Song *next = new Song();
		if(title->title !=NULL){
			removed = -1;
		}
		while(title->title != NULL){
			removed++;
			title = title->*next;
		}
		return removed;
	}

	//Pops the last node off the list, will return the last object of the node
	Song *pop(){
		Song *head = new Song();
		Song *next = new Song();
		if(head->next == NULL){
			return NULL;
		}
		else{
			Song *temp = head;
			while(temp->next->next != NULL){
				temp = temp->next;
			}
			Song *last = temp->next;
			temp->next = NULL;
			delete last;
		}
		return *head;
	}


