#pragma once
#include <iostream>
#include <string.h>
using namespace std;

struct Category
{
	string category = "";
	int pageNum = 0;

public:
	Category(const string category, const int pageNum);
	string getCategory();
	int getPageNum();
};

