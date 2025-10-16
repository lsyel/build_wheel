#include "bits/stdc++.h"
using namespace std;
struct Node{
    int val;
    Node* left;
    Node* right;
};
void mid_order(Node* root){
    stack<Node*> sta;
    Node* cur = root;
    while(cur || !sta.empty()){
        while(cur){
            sta.push(cur);
            cur = cur->left;
        }
        cur = sta.top();
        cout<<cur->val<<endl;
        sta.pop();
        cur = cur->right;
    }
}