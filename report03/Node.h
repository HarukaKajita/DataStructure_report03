#pragma once
#include <string>
#include <iostream>
using namespace std;
class Node
{
	string category = "";
	string titles = "";
	int pageNum = 0;
	Node* next = NULL;
public:
	Node(const string& category);
	void addTitle(const string& title);
	const string getCategory() const;
	const string getTitles() const;
	const int getPageNum() const;
	Node* const getNext() const;
	void setNext(Node* node);
	const bool operator>(const Node& n) const;
	const bool operator<(const Node& n) const;
	const bool operator>=(const Node& n) const;
	const bool operator<=(const Node& n) const;
};

