#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void exitFailedToOpen(string fileName) {
    cerr << "failed to open " << fileName << endl;
    exit(EXIT_FAILURE);
}

// 機能：引数として渡されたカテゴリが割り当てられているページのタイトルを検索する
// 引数：カテゴリ名
// 戻値：検索結果　タイトル１,タイトル2,...のような , で区切られた文字列

string search_page(string query)
{
    //open file
    string wikiFileName = "data.txt";
    ifstream wikiData(wikiFileName);
    if (!wikiData) exitFailedToOpen(wikiFileName);

    string titles = "";
    string line;

    // data.txtから１行ずつ読み込み
    while (wikiData >> line)
    {
        // 記事タイトルとカテゴリ（category1,category2,...）のデータに分割
        int commaIndex = line.find(",");
        string title = line.substr(0, commaIndex);
        string categories = line.substr(commaIndex + 1);

        // カテゴリ列のデータからカテゴリを１つずつ取り出し（split）
        int n = 0;
        for (int i = 0; i <= categories.length(); i = n + 1)
        {
            n = categories.find_first_of(",", i);
            if (n == string::npos)
            {
                n = categories.length();
            }

            string cw = categories.substr(i, n - i);

            if (query == cw)
            {
                titles += title + ",";
            }
        }
    }
    wikiData.close();

    return titles;
}

int main(int argc, char* argv[])
{
    //open file
    string categoryFileName = "category.list";
    ifstream categoryData(categoryFileName);
    if (!categoryData) exitFailedToOpen(categoryFileName);

    string result;
    string category;

    // data.txtから１行ずつ読み込み
    while (categoryData >> category)
    {
        cout << category << " -> ";

        string titles = search_page(category);

        if (titles != "")
        {
            cout << titles << endl;
        }

        cout << endl;
    }
    categoryData.close();

    return 0;
}



