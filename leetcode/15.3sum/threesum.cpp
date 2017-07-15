#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution{
public:
    vector<vector<int> > threeSum(vector<int> nums){
        sort(nums.begin(), nums.end());
        vector <vector<int> > vec_ret;

        for (int i = 0; i < (int)(nums.size() - 2); ++i){
            if (i != 0 && nums[i] == nums[i -1])
                continue;

            int pstart = i + 1;
            int pend = (int)(nums.size() - 1);
            int sum = 0 - nums[i];
            while (pstart < pend){
                if (nums[pstart] + nums[pend] == sum){
                    vector <int> r;
                    r.push_back(nums[i]);
                    r.push_back(nums[pstart]);
                    r.push_back(nums[pend]);
                    vec_ret.push_back(r);
                    
                    while (pstart < pend && nums[pstart] == nums[pstart+1]) pstart++;
                    while (pend > pstart && nums[pend] == nums[pend-1]) pend--;
                    pstart++; pend--;
                }
                else if (nums[pstart] + nums[pend] < sum)
                    pstart ++;
                else 
                    pend --;
            }
        }


        return vec_ret;
    }

    void print_vector(vector<int> vec){
        vector<int>::iterator iter = vec.begin();
        for(; iter != vec.end(); ++iter){
            cout << *iter << ",";
        }
        cout << endl;
    }

};


int main()
{
    int nums[] = {-1, 0, 1, 2, -1, -4, -1};
    //int nums[] = {1, 0, -1};
    vector<int> vec_num(nums, nums + sizeof (nums)/sizeof(int));

    Solution s;
    vector <vector<int> > ret;
    ret = s.threeSum(vec_num);
    
    for (int i = 0; i < ret.size(); ++i){
        s.print_vector(ret[i]);
    }

    return 0;
}
