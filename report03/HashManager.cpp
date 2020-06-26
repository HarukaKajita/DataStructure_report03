#include "HashManager.h"

void HashManager::addCategory(string category) {

	if (!headsDictionary.count(category)) {
		//add categoryHead if not exits
		vector<string>* newList = new vector<string>();
		headsDictionary.emplace(category, newList);
	}
}

void HashManager::addNode(string category, string title) {
	
	if (headsDictionary.count(category)) {
		//add node to categoryList
		headsDictionary.at(category)->push_back(title);
	}
	else {
		//add categoryHead if not exits
		vector<string>* newList = new vector<string>();
		newList->push_back(title);
		headsDictionary.emplace(category, newList);
	}
}

vector<string>* HashManager::searchTitles(string category) {
	if (headsDictionary.count(category)) {
		return headsDictionary.at(category);
	}
	else return NULL;
}