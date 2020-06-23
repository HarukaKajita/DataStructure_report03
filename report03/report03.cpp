#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// 機能：引数として渡されたカテゴリが割り当てられているページのタイトルを検索する
// 引数：カテゴリ名
// 戻値：検索結果　タイトル１,タイトル2,...のような , で区切られた文字列

string search_page(string query)
{
    ifstream f_data("data.txt");

    string result = "";
    string line;

    // data.txtから１行ずつ読み込み
    while (f_data >> line)
    {
        // 記事タイトルとカテゴリ（category1,category2,...）のデータに分割
        int index = line.find(",");
        string title = line.substr(0, index);
        string c_str = line.substr(index + 1);

        // カテゴリ列のデータからカテゴリを１つずつ取り出し（split）
        int n = 0;
        for (int i = 0; i <= c_str.length(); i = n + 1)
        {
            n = c_str.find_first_of(",", i);
            if (n == string::npos)
            {
                n = c_str.length();
            }

            string cw = c_str.substr(i, n - i);

            if (query == cw)
            {
                result += title + ",";
            }
        }
    }
    f_data.close();

    return result;
}

int main(int argc, char* argv[])
{
    ifstream fc_data("category.list");

    if (!fc_data) {
        cerr << "failed to open category.list" << endl;
        return EXIT_FAILURE;
    }

    string result;
    string line;

    // data.txtから１行ずつ読み込み
    while (fc_data >> line)
    {
        cout << line << " -> ";

        string result = search_page(line);

        if (result != "")
        {
            cout << result << endl;
        }

        cout << endl;
    }
    fc_data.close();

    return 0;
}



