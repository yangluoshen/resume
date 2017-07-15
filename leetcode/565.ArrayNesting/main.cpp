/*
Problem:
	A zero-indexed array A consisting of N different integers is given. The array contains all integers in the range [0, N - 1].
	Sets S[K] for 0 <= K < N are defined as follows:
	S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.
	Sets S[K] are finite for each K and should NOT contain duplicates.
	Write a function that given an array A consisting of N integers, return the size of the largest set S[K] for this array.

Example:
	Input: A = [5,4,0,3,1,6,2]
	Output: 4
	Explanation: 
	A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

	One of the longest S[K]:
	S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}

Note:
	1. N is an integer within the range [1, 20,000].
	2. The elements of A are all distinct.
	3. Each element of array A is an integer within the range [0, N-1].
*/

/*
Solution:
    此题只需要求"the size of the largest set", 因此可以用联机算法来解决。
    假设A[i]为S[K]中的元素, 很容发现，S[A[i]] = S[A[i+1]] = ...
    若把S[K]看成一个闭包(closuer),也就是说对同一个闭包中的元素只需要计算一次就可以了。
    用marks来标志哪个元素还未计算S[K]。 0 代表还未计算，1代表已计算。
    属于同一闭包的元素只需计算一次。

*/

#include <vector>
#include <iostream>
#include <string.h>
#include <malloc.h>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        if (nums.empty()) return 0;

        int* marks = (int*) malloc(sizeof(int) * nums.size());
        if (!marks) return 0;

        memset(marks, 0, nums.size() * sizeof(int));
        
        int max_marks = 0;
        for (int i = 0; i < nums.size(); ++i){
            if (marks[i]) continue;

            int count = 1;
            for (int j = nums[i]; j != i; ++count, j = nums[j]){
                marks[j] = 1;
            }

            if (count > max_marks){
                max_marks = count;
            }
        }

        free(marks);
        return max_marks;
    }
};

int main()
{
    int src[] = {5,4,0,3,1,6,2};
    vector<int> vec(src, src + sizeof(src)/sizeof(*src));

    Solution s;
    cout << s.arrayNesting(vec) << endl;

    return 0;
}
