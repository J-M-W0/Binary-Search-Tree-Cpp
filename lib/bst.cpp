#include "../header/bst.hpp"
#include <cmath>
#include <optional>
#include <queue>
#include <string>
#include <iostream>

#define RADIUS 25

extern const int XDISTANCE;
extern const int YDISTANCE;

extern Util util;

static Point * distance_array(const int maxdep, const int x, const int y) {
    int cnt = std::pow(2, maxdep + 1) - 1;
    Point * arr = new Point[cnt];
    assertf(arr != nullptr, "");

    int depth = maxdep;
    int nodes = std::pow(2, depth);
    double deviation = 0.5;
    int factor  = 1;
    int factor2 = 1;
    while (depth >= 0) {
        int beginX;
        if (depth == maxdep) {
            beginX = x;
        }
        else {
            beginX = x - XDISTANCE * deviation;
        }

        for (int i = nodes; i > 0; i--) {
            cnt--;
            arr[cnt] = {
                beginX - XDISTANCE * factor2 * (nodes - i),
                y - YDISTANCE * (maxdep - depth)
            };
        }

        
        if (depth == maxdep) {
            depth--;
            nodes = std::pow(2, depth);
            factor2 *= 2;
            continue;
        }

        depth--;
        nodes = std::pow(2, depth);
        factor2 *= 2;
        deviation += factor;
        factor *= 2;
    }
    return arr;
}

static TreeNode * NodeFindMin(TreeNode * node) {
    assertf(node!=nullptr, "");
    while (node->left) {
        node = node->left;
    }
    return node;
}

TreeNode::TreeNode(int v) : val(v), left(nullptr), right(nullptr)
{}
TreeNode::TreeNode(int v, TreeNode * l, TreeNode * r) : val(v), left(l), right(r)
{}
TreeNode::~TreeNode() {
    if (this->left) {
        delete this->left;
    }
    if (this->right) {
        delete this->right;
    }
}
void TreeNode::render(const int x, const int y) {
    util.draw_circle(x, y, 25);
    util.write(std::to_string(this->val).c_str(), x - 10, y - 10);
}
bool TreeNode::is_leaf(void) {
    return this->left == nullptr && this->right == nullptr;
}

Tree::Tree() : root(nullptr)
{}
Tree::~Tree() {
    if (root) {
        delete root;
    }
}

TreeNode * Tree::insert(TreeNode * node, int val) {
    if (!node) {
        return new TreeNode(val);
    }
    if (val < node->val) {
        node->left = insert(node->left, val);
    }
    else if (val > node->val) {
        node->right = insert(node->right, val);
    }
    else {
    }
    return node;
}
bool Tree::search(TreeNode * node, int val) const {
    if (!node) {
        return false;
    }
    if (val < node->val) {
        return search(node->left, val);
    }
    else if (val > node->val) {
        return search(node->right, val);
    }
    else {
        return true;
    }
}
TreeNode * Tree::remove(TreeNode * node, int val) {
    if (!node) {
        return nullptr;
    }
    if (val < node->val) {
        node->left = remove(node->left, val);
    }
    else if (val > node->val) {
        node->right = remove(node->right, val);
    }
    else {
        // val == node->val
        if (node->is_leaf()) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            TreeNode * temp = node;
            node = node->right;
            temp->right = nullptr;
            delete temp;
        }
        else if (node->right == nullptr) {
            TreeNode * temp = node;
            node = node->left;
            temp->left = nullptr;
            delete temp;
        }
        else {
            TreeNode * temp = NodeFindMin(node->right);
            node->val = temp->val;
            node->right = remove(node->right, temp->val);
        }
    }
    return node;
}
int Tree::depth(TreeNode * node) const {
    if (node->is_leaf()) {
        return 0;
    }
    if (node->left == nullptr) {
        return depth(node->right) + 1;
    }
    if (node->right == nullptr) {
        return depth(node->left) + 1;
    }
    return std::max(depth(node->left), depth(node->right)) + 1;
}
void Tree::in_order_traversal(TreeNode * node) const {
    if (!node) {
        return;
    }
    in_order_traversal(node->left);
    std::cout << node->val << "\n";
    in_order_traversal(node->right);
}
void Tree::breadth_first_traversal(TreeNode * node, const int x, const int y) const {
    int dep = depth(node);
    if (dep == 0) {
        node->render(x, y);
        return;
    }

    Point * arr = distance_array(dep, x, y);

    std::queue<TreeNode *> q;
    q.push(node);
    int cnt = std::pow(2, dep + 1) - 1;
    
    std::optional<int> vals[cnt];

    for (int i = 0; i < cnt; i++) {
        TreeNode * temp = q.front();
        q.pop();
        if (!temp) {
            q.push(nullptr); // left  is      nullptr
            q.push(nullptr); // right is also nullptr
            vals[i] = std::nullopt;
        }
        else {
            if (temp->left) {
                q.push(temp->left);
            }
            else {
                q.push(nullptr);
            }
            
            if (temp->right) {
                q.push(temp->right);
            }
            else {
                q.push(nullptr);
            }

            vals[i] = temp->val;
        }
    }

    for (int i = 0; i < cnt; i++) {
        if (!vals[i]) {
            continue;
        }
        util.draw_circle(arr[i].x, arr[i].y, RADIUS);
        util.write(std::to_string(vals[i].value()).c_str(), arr[i].x - 10, arr[i].y - 10);
        int idxleft  = i * 2 + 1;
        int idxright = i * 2 + 2;
        if (idxleft < cnt && vals[idxleft].has_value()) {
            util.draw_line(arr[i].x, arr[i].y, arr[idxleft].x, arr[idxleft].y);
        }
        if (idxright < cnt && vals[idxright].has_value()) {
            util.draw_line(arr[i].x, arr[i].y, arr[idxright].x, arr[idxright].y);
        }
    }

    delete [] arr;
}

void Tree::insert(int val) {
    root = insert(root, val);
}
void Tree::remove(int val) {
    root = remove(root, val);
}
bool Tree::search(int val) const {
    return search(root, val);
}
int Tree::depth(void) const {
    return depth(root);
}
void Tree::in_order_traversal() const {
    in_order_traversal(root);
}
void Tree::breadth_first_traversal(const int x, const int y) const {
    if (!root) {
        return;
    }
    breadth_first_traversal(root, x, y);
}


