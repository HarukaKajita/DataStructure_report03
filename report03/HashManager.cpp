#include "HashManager.h"

void HashManager::addCategory(const string& category) {

	if (!headsDictionary.count(category)) {
		//add categoryHead if not exits
		vector<string>* newList = new vector<string>();
		headsDictionary.emplace(category, newList);
	}
}

void HashManager::addNode(const string& category, const string& title) {
	
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

vector<string>* HashManager::searchTitles(const string& category) {
	if (headsDictionary.count(category)) {
		return headsDictionary.at(category);
	}
	else return NULL;
}