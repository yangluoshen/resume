#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int max_count = 0;
        unordered_set<char> curr_set;
        for (int i = 0; i < s.size(); ++i){

            for (int j = i; j < s.size(); ++j){
                if (curr_set.end() != curr_set.find(s[j])){
                    break;
                }

                curr_set.insert(s[j]);
            }

            if (curr_set.size() > max_count){
                max_count = curr_set.size();
            }

            curr_set.clear();
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
