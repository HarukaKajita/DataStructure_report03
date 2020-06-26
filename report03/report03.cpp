#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "HashManager.h"
#include "Category.h"

using namespace std;

void exitFailedToOpen(string fileName) {
    cerr << "failed to open " << fileName << endl;
    exit(EXIT_FAILURE);
}

void setPages(HashManager& hashMAnager) {
    string wikiFileName = "data.txt";
    ifstream wikiData(wikiFileName);
    if (!wikiData) exitFailedToOpen(wikiFileName);

    string line;

    while (wikiData >> line)
    {
        int commaIndex = line.find(",");
        string title = line.substr(0, commaIndex);
        string categories = line.substr(commaIndex + 1);

        int n = 0;
        for (int i = 0; i <= categories.length(); i = n + 1)
        {
            n = categories.find_first_of(",", i);
            if (n == string::npos)
            {
                n = categories.length();
            }

            string category = categories.substr(i, n - i);
            hashMAnager.addNode(category, title);
        }
    }
    wikiData.close();
}

void exchangeCategories(Category* a, Category* b)
{
    Category tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortCategories(vector<Category> categories, int left, int right)
{
    int index1 = left;
    int index2 = right;
    int x = categories[left].getPageNum();

    do
    {
        while (categories[index1].getPageNum() < x)
        {
            index1++;
        }

        while (categories[index2].getPageNum() > x)
        {
            index2--;
        }

        if (index1 <= index2)
        {
            exchangeCategories(&categories[index1], &categories[index2]);
            index1++;
            index2--;
        }
    } while (index1 < index2);

    if (left < index2) {
        sortCategories(categories, left, index2);
    }

    if (index1 < right) {
        sortCategories(categories, index1, right);
    }
}


int main(int argc, char* argv[])
{
    //open file
    string categoryFileName = "category.list";
    ifstream categoryData(categoryFileName);
    if (!categoryData) exitFailedToOpen(categoryFileName);
    auto begin = categoryData.tellg();
    string category;
    HashManager hashManager;

    //ハッシュの構築
    cout << "ハッシュ構築開始" << endl;
    while (categoryData >> category) hashManager.addCategory(category);
    setPages(hashManager);
    cout << "ハッシュ構築完了" << endl;
    
    categoryData.clear();
    categoryData.seekg(0, ios_base::beg);
    //１カテゴリ->タイトル検索
    /*while (categoryData >> category)
    {
        cout << category << " -> ";

        vector<string>* titles = hashManager.searchTitles(category);
        string result = "";
        if (nodes != NULL) {
            for(string n : *titles) titles += n;
        }
        
        if (result != "") cout << result << endl;
        cout << endl;
    }*/

    //２頻度ソート
    cout << "カテゴリリスト構築開始" << endl;
    vector<Category> categories;
    while (categoryData >> category)
    {
        vector<string>* titles = hashManager.searchTitles(category);
        int pageNum = titles->size();
        categories.push_back(Category(category, pageNum));
    }
    cout << "カテゴリリスト構築終了" << endl;
    cout << "カテゴリリストソート開始" << endl;
    sortCategories(categories, 0, categories.size());
    cout << "カテゴリリストソート終了" << endl;
    categoryData.close();

    return 0;
}



