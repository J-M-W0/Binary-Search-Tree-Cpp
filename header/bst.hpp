#pragma once
#include "utils.hpp"

class TreeNode {
public:
    int val;
    TreeNode * left;
    TreeNode * right;
    TreeNode(int v); 
    TreeNode(int v, TreeNode * l, TreeNode * r);
    ~TreeNode();

    bool is_leaf(void);
    void render(const int x, const int y);
};

class Tree {
private:
    TreeNode * root;
    TreeNode * insert(TreeNode * node, int val);
    bool search(TreeNode * node, int val) const;
    int depth(TreeNode * node) const;
    TreeNode * remove(TreeNode * node, int val);
    void in_order_traversal(TreeNode * node) const;
    void breadth_first_traversal(TreeNode * node, const int x, const int y) const;
public:
    Tree();
    ~Tree();

    void insert(int val);
    bool search(int val) const;
    void remove(int val);
    int depth(void) const;
    void in_order_traversal() const;
    void breadth_first_traversal(const int x, const int y) const;
};



