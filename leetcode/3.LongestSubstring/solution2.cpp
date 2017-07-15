#include <iostream>
using namespace std;

class Solution {

private:
    bool is_exist(string& s, char c,  size_t start, size_t end)
    {
        size_t pos = s.find(c, start);
        if (string::npos == pos) return false;
        else if (pos >= end) return false;
        else return true;
    }

public:
    int lengthOfLongestSubstring(string s) {

        int max_count = 0;
        int further_index = 0;
        for (int i = 0; i < s.size(); ++i){
            for (int k = i; k < further_index; ++k){
                if (s[k] == s[further_index]) break;
            }

            for (int j = further_index; j < s.size(); ++j){
                if (is_exist(s, s[j], i, j)){
                    break;
                }
                further_index = j + 1;
            }

            if (further_index - i > max_count){
                max_count = further_index - i;
            }
        }

        return  max_count;
    }
};

int main()
{
    Solution s;
    cout <<"3->" << s.lengthOfLongestSubstring("abcabcbb") <<endl;
    cout <<"1->" << s.lengthOfLongestSubstring("a") <<endl;
    cout <<"1->" << s.lengthOfLongestSubstring("bb") <<endl;
    cout <<"7->" << s.lengthOfLongestSubstring("abcdefg") <<endl;
    cout <<"2->" << s.lengthOfLongestSubstring("aab") <<endl;
    cout <<"5->" << s.lengthOfLongestSubstring("abcadbec") <<endl;
    cout <<"3->" << s.lengthOfLongestSubstring("pwwkew") <<endl;

    return 0;
}
