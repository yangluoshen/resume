# Longest Substring Without Repeating Characters

## Solution1

* Solution1利用hash_set使得检查重复字符的速度变快(O(1)),但是整体复杂度还是O(n2)。

## Solution2

* Solution2的优势在于，将之前比较过的子串利用起来，减少重复检查。但是检查字符串重复的开销比较大（取决于string.find()的实现）。

## Comparison

* time of Solution1 : 389ms in 983 testcase, beats 8% cpp submission on leetcode.
* time of Solution2 : 28ms in 983 testcase, beats 65.09% cpp submission on leetcode.


