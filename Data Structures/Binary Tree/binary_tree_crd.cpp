#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node *left;
    node *right;

    node(int val) {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};

enum direction {
    LEFT, RIGHT
};

void inorder_traversal(node *root) {
    if(root == NULL) {
        return;
    }
    inorder_traversal(root->left);
    cout<< root->val << ' ';
    inorder_traversal(root->right);
}

node* delete_node(node* root, int val) {
    if(root == NULL) {
        return root;
    }
    if (root->left == NULL && root->right == NULL) {
        if(root->val == val) {
            return NULL;
        } else {
            return root;
        }
    }

    queue<node*> q;
    node* last_node_parent;
    direction last_node_direction;
    node* last_node;
    node* matched_node;
    q.push(root);

    while(!q.empty()) {
        last_node = q.front();
        q.pop();

        if(last_node->val == val) {
            matched_node = last_node;
        }

        if(last_node->left != NULL || last_node->right != NULL) {
            last_node_parent = last_node;
            if(last_node->left != NULL) {
                q.push(last_node->left);
                last_node_direction = LEFT;
            }

            if(last_node->right != NULL) {
                q.push(last_node->right);
                last_node_direction = RIGHT;
            }
        }
    }

    if(matched_node != NULL) {
        int last_val = last_node->val;
        if (last_node_direction == LEFT) {
            last_node_parent->left = NULL;
        } else {
            last_node_parent->right = NULL;
        }
        delete(last_node);
        matched_node->val = last_val;
    }
    return root;
}

void insert(node *root, int val) {
    queue<node*> q;
    if(root == NULL) {
        root = new node(val);
        return;
    }
    q.push(root);
    while(!q.empty()) {
        node *tmp = q.front();
        q.pop();
        if(tmp->left == NULL) {
            tmp->left = new node(val);
            return;
        } else {
            q.push(tmp->left);
        }

        if(tmp->right == NULL) {
            tmp->right = new node(val);
            return;
        } else {
            q.push(tmp->right);
        }
    }
}

void print_left_view(node* root, int level, int* last_level) {
    if(root == NULL) {
        return;
    }

    if(*last_level < level) {
        cout<<root->val<< " ";
        *last_level = level;
    }
    print_left_view(root->left, level+1, last_level);
    print_left_view(root->right, level+1, last_level);

}

int main() {

    // Creating a tree
    node *root = new node(10);
    root->left = new node(11);
    root->left->left = new node(7);
    root->right = new node(9);
    root->right->left = new node(15);
    root->right->right = new node(8);

    inorder_traversal(root);

    // insert 12 on inorder availability
    insert(root, 12);

    cout<<endl;
    inorder_traversal(root);

    cout<<endl;
    delete_node(root, 11);
    cout<<endl<<"Traversal after deletion of 11\n";
    inorder_traversal(root);
    
    int last_level = 0;
    cout<<endl<<"Left View";
    print_left_view(root, 1, &last_level);

    return 0;
}