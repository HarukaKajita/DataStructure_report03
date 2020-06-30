#include "HashManager.h"

HashManager::HashManager(const int& size) {
	this->size = size;
	table = new Node * [size];
	for (int i = 0; i < size; i++)table[i] = NULL;
	//cout << "init HashManager" << sizeof(table) / sizeof(Node*) << endl;
}
HashManager::HashManager() {
	this->size = 1000;
	table = new Node * [size];
	for (int i = 0; i < size; i++)table[i] = NULL;
}
int HashManager::getHash(const string& key) const
{
	unsigned int v = 0;
	for (int i = 0; i < key.length(); i++) v += key[i] * pow(2, i);
	return v % size;
}
Node* HashManager::searchNode(const string& category) const {
	int hashValue = getHash(category);
	Node* node = table[hashValue];
	//ƒŠƒXƒg‚ð‘–¸‚µƒJƒeƒSƒŠ‚ð’T‚·
	while (node != NULL && node->getCategory() != category) node = node->getNext();
	//‚È‚¯‚ê‚ÎNULL‚ð•Ô‚·
	return node;
}

void HashManager::addData(const string& category, const string& title) {
	const int hashValue = getHash(category);
	Node* node = table[hashValue];
	if (node == NULL) {
		table[hashValue] = new Node(category);
		node = table[hashValue];
	}
	else {
		//ƒŠƒXƒg‚ð‘–¸‚µƒJƒeƒSƒŠ‚ð’T‚·
		while (node != NULL) {
			string nodeCategory = node->getCategory();
			bool isNotExist = nodeCategory != category;
			if (!isNotExist) break;

			Node* next = node->getNext();
			//ƒJƒeƒSƒŠ‚ª‚È‚¯‚ê‚Î’Ç‰Á‚·‚é
			if (next == NULL) {
				Node* newNode = new Node(category);
				node->setNext(newNode);
				node = newNode;
				break;
			}
			node = next;

		}
	}
	node->addTitle(title);
}

string HashManager::getTitles(const string& category) const {
	int hashValue = getHash(category);
	Node* node = searchNode(category);
	if (node == NULL) return "";
	return node->getTitles();
}

const int HashManager::getPageNum(const string& category) const {
	int hashValue = getHash(category);
	Node* node = searchNode(category);
	if (node == NULL) return 0;
	return node->getPageNum();
}

const int HashManager::getTableSize() const {
	return size;
}
const Node* HashManager::getListAt(const int& index) const {
	return table[index];
}