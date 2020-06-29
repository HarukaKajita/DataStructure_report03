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
	//cout << "init HashManager" << sizeof(table) / sizeof(Node*) << endl;
}
int HashManager::getHash(const string& key, const int& size)
{
	unsigned int v = 0;
	for (int i = 0; i < key.length(); i++) v += key[i] * pow(2, i);
	return v % size;
}
Node* HashManager::searchNode(const string& category) {
	int hashValue = getHash(category, size);
	Node* node = table[hashValue];
	//リストを走査しカテゴリを探す
	while (node != NULL && node->getCategory() != category) node = node->getNext();
	//なければNULLを返す
	return node;
}

void HashManager::addData(const string& category, const string& title) {
	const int hashValue = getHash(category, size);
	Node* node = table[hashValue];
	if (node == NULL) {
		//cout << "NULLだよ！" << endl;
		table[hashValue] = new Node(category);
		node = table[hashValue];
	}
	else {
		//cout << node->getTitles() << "：" << node->getCategory() << "だよ！" << endl;;
		//リストを走査しカテゴリを探す
		while (node != NULL) {
			string nodeCategory = node->getCategory();
			bool isNotExist = nodeCategory != category;
			if (!isNotExist) break;

			Node* next = node->getNext();
			//カテゴリがなければ追加する
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

string HashManager::getTitles(const string& category) {
	int hashValue = getHash(category, size);
	Node* node = searchNode(category);
	if (node == NULL) return "";
	return node->getTitles();
}

const int HashManager::getPageNum(const string& category) {
	int hashValue = getHash(category, size);
	Node* node = searchNode(category);
	if (node == NULL) return 0;
	return node->getPageNum();
}

const int HashManager::getTableSize() {
	return size;
}
Node* HashManager::getListAt(const int& index) {
	return table[index];
}