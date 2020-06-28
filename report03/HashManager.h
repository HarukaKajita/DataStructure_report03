#pragma once

#include <vector>
#include <map>
#include <string>
using namespace std;

class HashManager
{
	//key:category value:head
	map<string, vector<string>*> headsDictionary;

public:
	void addCategory(const string& category);
	void addNode(const string& category, const string& title);
	vector<string>* searchTitles(const string& category);
};

