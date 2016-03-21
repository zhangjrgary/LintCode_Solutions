Source

leetcode: Anagrams | LeetCode OJ * lintcode: (171) Anagrams
Given an array of strings, return all groups of strings that are anagrams.

Example
Given ["lint", "intl", "inlt", "code"], return ["lint", "inlt", "intl"].

Given ["ab", "ba", "cd", "dc", "e"], return ["ab", "ba", "cd", "dc"].
Note
All inputs will be in lower-case
题解1 - 双重for循环(TLE) __

题 Two Strings Are Anagrams | Data Structure and Algorithm 的升级版，容易想到的方法为使用双重for循环两两判断字符串数组是否互为变位字符串。但显然此法的时间复杂度较高。还需要 O(n) 的数组来记录字符串是否被加入到最终结果中。

C++

class Solution {
public:
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    vector anagrams(vector &strs) {
        if (strs.size() < 2) {
            return strs;
        }

        vector result;
        vector visited(strs.size(), false);
        for (int s1 = 0; s1 != strs.size(); ++s1) {
            bool has_anagrams = false;
            for (int s2 = s1 + 1; s2 < strs.size(); ++s2) {
                if ((!visited[s2]) && isAnagrams(strs[s1], strs[s2])) {
                    result.push_back(strs[s2]);
                    visited[s2] = true;
                    has_anagrams = true;
                }
            }
            if ((!visited[s1]) && has_anagrams) result.push_back(strs[s1]);
        }

        return result;
    }

private:
    bool isAnagrams(string &s, string &t) {
        if (s.size() != t.size()) {
            return false;
        }

        const int AlphabetNum = 26;
        int letterCount[AlphabetNum] = {0};
        for (int i = 0; i != s.size(); ++i) {
            ++letterCount[s[i] - 'a'];
            --letterCount[t[i] - 'a'];
        }
        for (int i = 0; i != t.size(); ++i) {
            if (letterCount[t[i] - 'a'] < 0) {
                return false;
            }
        }

        return true;
    }
};
源码分析

strs 长度小于等于1时直接返回。
使用与 strs 等长的布尔数组表示其中的字符串是否被添加到最终的返回结果中。
双重循环遍历字符串数组，注意去重即可。
私有方法isAnagrams用于判断两个字符串是否互为变位词。
复杂度分析

私有方法isAnagrams最坏的时间复杂度为 O(2L), 其中 L 为字符串长度。双重for循环时间复杂度近似为 ​2​​1​​O(n​2​​), n 为给定字符串数组数目。总的时间复杂度近似为 O(n​2​​L).

题解2 - 排序 + hashmap

在题 Two Strings Are Anagrams | Data Structure and Algorithm 中曾介绍过使用排序和 hashmap 两种方法判断变位词。这里我们将这两种方法同时引入！只不过此时的 hashmap 的 key 为字符串，value 为该字符串在 vector 中出现的次数。两次遍历字符串数组，第一次遍历求得排序后的字符串数量，第二次遍历将排序后相同的字符串取出放入最终结果中。

C++

class Solution {
public:
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    vector anagrams(vector &strs) {
        unordered_map hash;

        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(), str.end());
            ++hash[str];
        }

        vector result;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(), str.end());
            if (hash[str] > 1) {
                result.push_back(strs[i]);
            }
        }

        return result;
    }
};
源码分析

建立 key 为字符串，value 为相应计数器的hashmap, unordered_map为 C++ 11中引入的哈希表数据结构unordered_map, 这种新的数据结构和之前的 map 有所区别，详见map-unordered_map。

第一次遍历字符串数组获得排序后的字符串计数器信息，第二次遍历字符串数组将哈希表中计数器值大于1的字符串取出。

复杂度分析

遍历一次字符串数组，复杂度为 O(n), 对单个字符串排序复杂度近似为 O(LlogL). 两次遍历字符串数组，故总的时间复杂度近似为 O(nLlogL). 使用了哈希表，空间复杂度为 O(K), 其中 K 为排序后不同的字符串个数。
