#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief 检查一个单词是否可以由给定的方块拼出。
 *
 * @param word 要检查的单词。
 * @param blocks 包含4个方块字母的向量。
 * @return 如果可以拼出则返回 true，否则返回 false。
 */
bool can_spell(const string &word, const vector<string> &blocks)
{
    // 初始化一个表示方块索引的向量 {0, 1, 2, 3}
    vector<int> p = {0, 1, 2, 3};
    int k = word.length();

    // 使用 do-while 和 next_permutation 遍历所有方块的排列
    do
    {
        bool possible = true;
        // 检查当前排列 p 是否能拼出单词
        for (int i = 0; i < k; ++i)
        {
            // word[i] -> 单词的第i个字母
            // p[i] -> 当前排列中第i个位置的方块索引
            // blocks[p[i]] -> 对应的方块字符串
            if (blocks[p[i]].find(word[i]) == string::npos)
            {
                // 如果在方块上找不到对应的字母，则此排列无效
                possible = false;
                break;
            }
        }
        // 如果循环正常结束（没有break），说明找到了一个有效的排列
        if (possible)
        {
            return true;
        }
    } while (next_permutation(p.begin(), p.end()));

    // 如果遍历完所有排列都没有找到，则无法拼出
    return false;
}

int main()
{
    // 提高C++流的输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // 读取4个方块的字母
    vector<string> blocks(4);
    for (int i = 0; i < 4; ++i)
    {
        cin >> blocks[i];
    }

    // 循环处理N个单词
    for (int i = 0; i < n; ++i)
    {
        string word;
        cin >> word;
        if (can_spell(word, blocks))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}