#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <windows.h>
#include "HashManager.h"
#include "Category.h"

using namespace std;

void exitFailedToOpen(const string& fileName) {
    cerr << "failed to open " << fileName << endl;
    exit(EXIT_FAILURE);
}

void setPages(HashManager& hashManager) {
    string wikiFileName = "data.txt";
    ifstream wikiData(wikiFileName);
    if (!wikiData) exitFailedToOpen(wikiFileName);

    string line;
    while (wikiData >> line)
    {
        int commaIndex = line.find(",");
        string title = line.substr(1, commaIndex-2);
        string categories = line.substr(commaIndex + 1);

        int n = 0;
        for (int i = 0; i <= categories.length(); i = n + 1)
        {
            n = categories.find_first_of(",", i);
            if (n == string::npos) n = categories.length();
            
            string category = categories.substr(i, n - i);
            hashManager.addData(category, title + ",");
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
void sortCategories(vector<Category>& categories, const int& left, const int& right)
{
    int index1 = left;
    int index2 = right;
    Category x = categories[left];
    do
    {
        while (categories.at(index1) > x) index1++;
        while (categories.at(index2) < x) index2--;
        if (index1 <= index2)
        {
            exchangeCategories(&categories[index1], &categories[index2]);
            index1++;
            index2--;
        }
    } while (index1 < index2);

    if (left < index2) exchangeCategories(&categories[left], &categories[index2]);
    if (left < index2) sortCategories(categories, left, index2);
    if (index1 < right) sortCategories(categories, index1, right);
}

int main(int argc, char* argv[])
{
    //open file
    string categoryFileName = "category.list";
    ifstream categoryData(categoryFileName);
    if (!categoryData) exitFailedToOpen(categoryFileName);
    string category;
    HashManager hashManager = HashManager(10000);
    
    //ハッシュの構築
    cout << "ハッシュ構築開始" << endl;
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER start, end;

    QueryPerformanceCounter(&start);
    setPages(hashManager);
    QueryPerformanceCounter(&end);
    double time = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("time %lf[ms]\n", time);
    cout << "ハッシュ構築完了" << endl;
    //１カテゴリ->タイトル検索
    
    //先頭末尾5件表示
    /*
    vector<string> buffer;
    while (categoryData >> category)
    {
        string line = "";
        line += category + " -> ";
        line += hashManager.getTitles(category);
        buffer.push_back(line);
    }
    for (size_t i = 0; i < 5; i++)cout << buffer.at(i) << endl;
    cout << endl;
    for (size_t i = 0; i < 5; i++)cout << buffer.at(buffer.size()+i-5) << endl;
    cout << endl;
    */

    //全件表示
    while (categoryData >> category)
    {
        cout << category << " -> ";
        string titles = hashManager.getTitles(category);
        cout << titles << endl;
        cout << endl;
    }

    //２頻度ソート
    cout << "カテゴリリスト構築開始" << endl;
    vector<Category> categories;
    const int tableSize = hashManager.getTableSize();
    for (size_t i = 0; i < tableSize; i++)
    {
        const Node* node = hashManager.getListAt(i);
        while (node != NULL) {
            const string category = node->getCategory();
            const int pageNum = node->getPageNum();
            categories.push_back(Category(category, pageNum));
            node = node->getNext();
        }
    }
    cout << "カテゴリリスト構築終了" << endl;

    cout << "カテゴリリストソート開始" << endl;
    // 時間計測
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    sortCategories(categories, 0, categories.size()-1);
    QueryPerformanceCounter(&end);
    time = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("time %lf[ms]\n", time);
    cout << "カテゴリリストソート終了" << endl;

    //全件表示
    for (int i = 0; i < categories.size(); i++)
        cout << categories.at(i).getCategory() << "：" << categories.at(i).getPageNum() << endl;

    //上位10件表示
    //for (int i = 0; i < 10; i++)
    //  cout << categories.at(i).getCategory() << "：" << categories.at(i).getPageNum() << endl;
    
    
    return 0;
}



