/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void print (ListNode* l);
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l3 = new ListNode(0);
        if (!l3) return NULL;
        
        int promot = 0;
        ListNode* node3 = l3;
        while (l1 || l2){
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            int v3 = v1 + v2 + promot;

            promot = v3 / 10;
            ListNode* tmpnode = new ListNode(v3 % 10);
            if (!tmpnode) exit(1);

            node3->next = tmpnode;
            node3 = node3->next;
            l1 = l1 ? l1->next : NULL;
            l2 = l2 ? l2->next : NULL;
        }

        if (promot){
            ListNode* tmpnode = new ListNode(promot);
            if (!tmpnode) exit(1);
            node3->next = tmpnode;
        }

        ListNode* head = l3;
        l3 = l3->next;
        delete head;

        return l3;
    }

};


void print (ListNode* l)
{
    while (l){
        cout << l->val << ","; 
        l = l->next;
    }
    cout << endl;
}

ListNode* gen_list_node(int* a, int n)
{
    ListNode* l = new ListNode(0);
    ListNode* node = l;
    for (int i = 0; i < n; ++i){
        ListNode* tmp = new ListNode(a[i]);
        node->next = tmp;
        node = node->next;
    }

    ListNode* head = l;
    l = l->next;
    delete head;

    return l;
}

int main()
{
    int a1[3] = {2,4,3};
    int a2[4] = {5,6,6,9};
    ListNode* l1 = gen_list_node(a1, sizeof(a1)/sizeof(int));
    ListNode* l2 = gen_list_node(a2, sizeof(a2)/sizeof(int));
    print(l1);
    print(l2);

    Solution s;
    ListNode* l3 = s.addTwoNumbers(l1, l2);

    print(l3);
    return 0;
}
