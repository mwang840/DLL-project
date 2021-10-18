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
		DNode *node = new DNode(t, a, m, s);
		if(first == NULL && last == NULL){
			first = node;
			last = node;
			numSongs++;
		}
		else{
			node->prev = last;
			last->next = node;
			last = node;
			numSongs++;
		}

	}

	//Prints out the list in each node
	void DLL::printList(){
		if(first == NULL && last == NULL){
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
		DNode *temp = first;
		while(temp != NULL){
			if(temp->song->title == t){
				if(temp->prev == NULL){ // then node is first
					first = temp; // TODO: Modify what happens in this condition
				}
				else if(temp->next == NULL){ // then node is last, pop is valid
					pop();
				}
				else{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				delete temp;
				numSongs--;
				break;
			}
			temp = temp->next;
			index++;
		}

		return index;
	}

void DLL::reInsert(string t, string a, int m, int s, int i){
	DNode *node = new DNode();
	if(first == NULL && last == NULL){
		first = node;
		last = node;
		numSongs++;
	}
	else{
		node->prev = last;
		last->next = node;
		last = node;
		numSongs++;


	}

}

	// TODO: may crash or return an invalid value, not 100% sure
	//Pops the last node off the list, will return the last object of the node
	Song *DLL::pop(){
		DNode *nonExist = last;
		Song *object = nonExist->song;
		last = last->prev;
		delete nonExist;
		last->next = NULL;
		numSongs--;
		return object;
	}

	//// moves song with title s up one in the playlist.
    //If it is at the beginning of the list,
    //it will be moved to the end of the list.
	// TODO: Format
	void DLL::moveUp(string t){
		DNode *current = first;
		// If list has zero nodes
		if(numSongs <= 1){
			return;
		}
		string title1 = first->song->title;

		if(first->song->title == t || last->song->title == t){
			if(title1 == t){
				DNode *temp = first;
				temp->next = NULL;
				last->prev = NULL;
				last = temp;
			}
			else{
				DNode *temp = last;
				last->prev = NULL;
				first = temp;
			}
		}
		//Condition 3 if there are three nodes, move each one up, the one that is being changed moves to the bottom
		else if(numSongs == 3 && current->next->song->title == t){
			//1) assign a variable to the middle
			//2) Reroute pointers, without doing any first = or last =, you can do first->next or last->next but do not
			// do first = or last = until the very last step
			//3) assign first to the moved up middle node, and do not reassign
			//4) Make sure there is no last = anywhere inside this else if statement
			DNode *temp = first->next;
			temp->next = first;
			temp->prev = NULL;
			first->prev = temp;
			first->next = last;
			last->prev = first;
			first = temp;
		}

		//Condition 4
		else if(numSongs == 4 && current->song->title == t){
			DNode *attempt = first->next;
			attempt->next->next = first;
			attempt->prev = NULL;
			first->prev = attempt->next;
			first->next = last;
			last->prev = first;
			first = attempt;

		}
		else{

			// When are you moving the node with the title you pass in?

			DNode *ltempt = first;
			while(ltempt != NULL && ltempt->song->title != t){ // iterating down to end
				ltempt = ltempt->next;
			}
			if(ltempt != NULL){
				cout << "title found" << endl; // you found the title
				DNode *ltPrev = ltempt->prev;
				DNode *ltNext = ltempt->next;
				DNode *ltPPrev = ltPrev->prev;
				if(ltPPrev != NULL){
					ltPPrev->next = ltempt;
				}
				ltNext->prev = ltPrev;
				ltPrev->prev = ltempt;
				ltPrev->next = ltNext;
				ltempt->prev = ltPPrev;
				ltempt->next = ltPrev;
			}
			return;
		}
	}

	//moves song with title s down one in the playlist.
	//If it is at the end of the list, it will move to
	//beginning of the list.
	// TODO: format similar to moveDown
	void DLL::moveDown(string t){
		DNode *current = first;

		// If list has zero nodes
		if(numSongs <= 1){
			return;
		}
		else if(first->song->title == t || last->song->title == t){
			string firstSong = first->song->title;
			if(firstSong == t){
				DNode *tmpNext = first->next;
				if(tmpNext->next == NULL){
					// 2 nodes
					tmpNext->next = first;
					first->prev = tmpNext;
					tmpNext->prev = NULL;
					first->next = NULL;
					first = tmpNext;
				}
				else{
					// > 2 nodes
					DNode *tmpNN = tmpNext->next;
					tmpNext->next = first; // tmpNext check
					first->next = tmpNN; // first check
					tmpNN->prev = first;
					first->prev = tmpNext;
					tmpNext->prev = NULL;
					first = tmpNext;

				}
			}
			else{
				Song *newSong = pop();
				string title = newSong->title;
				string artist = newSong->artist;
				DNode *newNode = new DNode(title,artist,newSong->min,newSong->sec);
				newNode->next = first;
				first->prev = newNode;
				first = newNode;
			}
		}
		else{
			DNode *curr = first;
			while(curr != NULL){
				if(curr->song->title == t){
					break;
				}
			}
			if(curr != NULL){
				// found the song
				bool newLast = false;
				DNode *currPrev = curr->prev;
				DNode *currNext = curr->next;
				if(currNext->next != NULL){
					// 2nd to last
					currNext->next->prev = curr;
					curr->next = currNext->next;
				}
				else{
					newLast = true;
					curr->next = NULL;
				}
				currNext->prev = currPrev;
				currNext->next = curr;
				currPrev->next = currNext;
				curr->prev = currNext;
				if(newLast){
					last = curr;
				}
			}
			return;
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

	}

	//Makes a random list for the songs
	void DLL::makeRandom(){

		DNode *current = first;

		while(current != NULL)
		{
			for(int i = 0; i < numSongs; ++i){
				int random = rand() % 2;
				if(random != 0){
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
	DLL::~DLL(){

		cout<<"Making a new playlist..."<<endl;
		DNode *current  = first;
		DNode *temp;
		Song *s = current->song;
		Song *holding;
		while(current != NULL){
			temp = current->next;
			holding = s;
			delete s;
			delete current;
			current = temp;
			s = holding;
			current = current->next;
		}
		cout<<"List is deleted"<<endl;
	}

