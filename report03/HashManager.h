#pragma once

#include <vector>
#include <map>
#include <string>
using namespace std;

class HashManager
{
	//key:category value:head
	std::map<string, vector<string>*> headsDictionary;

public:
	void addCategory(string category);
	void addNode(string category, string title);
	vector<string>* searchTitles(string category);
};

