#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class HashManager
{
	//key:category value:head
	//map<string, vector<string>*> headsDictionary;
	int size;
	Node** table;
	int getHash(const string& key, const int& size);
	Node* searchNode(const string& category);
public:
	HashManager(const int& size);
	HashManager();
	void addData(const string& category, const string& title);
	string getTitles(const string& category);
	const int getPageNum(const string& category);
	const int getTableSize();
	Node* getListAt(const int& index);
};