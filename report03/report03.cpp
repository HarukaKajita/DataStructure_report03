#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <windows.h>
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
void sortCategories(vector<Category>& categories, const int left, const int right)
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
    HashManager hashManager;
    
    //ハッシュの構築
    cout << "ハッシュ構築開始" << endl;
    while (categoryData >> category) hashManager.addCategory(category);
    setPages(hashManager);
    cout << "ハッシュ構築完了" << endl;
    
    categoryData.clear();
    categoryData.seekg(0, ios_base::beg);
    //１カテゴリ->タイトル検索
    while (categoryData >> category)
    {
        cout << category << " -> ";

        vector<string>* titles = hashManager.searchTitles(category);
        string result = "";
        if (titles != NULL) {
            for(string n : *titles) result += n;
        }
        
        if (result != "") cout << result << endl;
        cout << endl;
    }

    //２頻度ソート
    cout << "カテゴリリスト構築開始" << endl;
    categoryData.clear();
    categoryData.seekg(0, ios_base::beg);
    vector<Category> categories;
    while (categoryData >> category)
    {
        vector<string>* titles = hashManager.searchTitles(category);
        int pageNum = titles->size();
        categories.push_back(Category(category, pageNum));
    }
    categoryData.close();

    cout << "カテゴリリスト構築終了" << endl;
    cout << "カテゴリリストソート開始" << endl;
    // QueryPerformanceCounter関数の1秒当たりのカウント数を取得する
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER start, end;

    QueryPerformanceCounter(&start);
    sortCategories(categories, 0, categories.size()-1);
    //sort(categories.begin(), categories.end());
    QueryPerformanceCounter(&end);

    double time = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("time %lf[ms]\n", time);
    cout << "カテゴリリストソート終了" << endl;

    for(int i = 0; i < 10; i++)
    cout << categories.at(i).getCategory() << "：" << categories.at(i).getPageNum() << endl;
    
    
    return 0;
}



