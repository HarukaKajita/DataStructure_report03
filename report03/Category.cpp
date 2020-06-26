#include "Category.h"

Category::Category(const string category = "", const int pageNum = 0) {
	this->category = category;
	this->pageNum = pageNum;
}
string Category::getCategory() {
	return category;
}
int Category::getPageNum() {
	return pageNum;
}