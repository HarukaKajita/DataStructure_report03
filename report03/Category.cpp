#include "Category.h"

Category::Category(const string category = "", const int pageNum = 0) {
	this->category = category;
	this->pageNum = pageNum;
}
const string Category::getCategory() {
	return category;
}
const int Category::getPageNum() {
	return pageNum;
}

const bool Category::operator>(const Category& c) const { return this->pageNum > c.pageNum; }
const bool Category::operator<(const Category& c) const { return this->pageNum < c.pageNum; }
const bool Category::operator>=(const Category& c) const { return this->pageNum >= c.pageNum; }
const bool Category::operator<=(const Category& c) const { return this->pageNum <= c.pageNum; }