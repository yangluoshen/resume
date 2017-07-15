#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Solution{
public :
    vector <int> twoSum(vector<int>& nums, int target){
        int i, j;
        vector <int> ret;
        for (i = 0; i < nums.size() - 1; ++i){
            for (j = i + 1; j < nums.size(); ++j){
                if (nums[i] + nums[j] == target){
                    ret.push_back(i);
                    ret.push_back(j);
                    return ret;
                }

            }
        }
        return ret;
    }

};


int main(int argc, char** argv)
{
    if (argc < 4){
        cout << "Error: at least 3 parameters needed" << endl;
        return 1;
    }

    vector <int> nums;
    for (int i = 1; i < argc - 1; ++i){
        int n = atoi(argv[i]);
        nums.push_back(n);
    }

    int target = atoi(argv[argc - 1]);

    Solution s;
    nums = s.twoSum(nums, target);
    
    for (int i = 0; i < nums.size(); ++i){
        cout << nums[i] << endl;
    }


    return 0;

}

