#pragma once
#include <iostream>
#include <string.h>
using namespace std;

struct Category
{
private:
	string category = "";
	int pageNum = 0;

public:
	Category(const string category, const int pageNum);
	const string getCategory();
	const int getPageNum();
	const bool operator>(const Category& c) const;
	const bool operator<(const Category& c) const;
	const bool operator>=(const Category& c) const;
	const bool operator<=(const Category& c) const;
};

