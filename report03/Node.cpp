#include "Node.h"

Node::Node(const string& category) {
	this->category = category;
}
void Node::addTitle(const string& title) {
	this->titles += title;
	pageNum++;
}
const string Node::getCategory() const {
	return category;
}
const string Node::getTitles() const {
	return titles;
}
const int Node::getPageNum() const {
	return pageNum;
}
Node* const Node::getNext() const {
	return next;
}
void Node::setNext(Node* node) {
	next = node;
}
const bool Node::operator>(const Node& n) const { return this->pageNum > n.pageNum; }
const bool Node::operator<(const Node& n) const { return this->pageNum < n.pageNum; }
const bool Node::operator>=(const Node& n) const { return this->pageNum >= n.pageNum; }
const bool Node::operator<=(const Node& n) const { return this->pageNum <= n.pageNum; }