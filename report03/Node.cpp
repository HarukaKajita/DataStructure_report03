#include "Node.h"

Node::Node(const string& category) {
	this->category = category;
}
void Node::addTitle(const string& title) {
	titles += title;
	pageNum++;
}
const string Node::getCategory() {
	return category;
}
const string Node::getTitles() {
	return titles;
}
const int Node::getPageNum() {
	return pageNum;
}
Node* Node::getNext() {
	return next;
}
void Node::setNext(Node* node) {
	next = node;
}
const bool Node::operator>(const Node& n) const { return this->pageNum > n.pageNum; }
const bool Node::operator<(const Node& n) const { return this->pageNum < n.pageNum; }
const bool Node::operator>=(const Node& n) const { return this->pageNum >= n.pageNum; }
const bool Node::operator<=(const Node& n) const { return this->pageNum <= n.pageNum; }