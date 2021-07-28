#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    int height;
    node* left;
    node* right;

    node(int val) {
        this->val = val;
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

node* avl_root = NULL;
node* find_successor(node*);
node* left_rotate(node*);
node* right_rotate(node*);

int height(node* nod) {
    if(nod == NULL) {
        return 0;
    }
    return nod->height;
}

node* right_rotate(node* nod) {
    node* tmp1 = nod->left;
    node* tmp2 = tmp1->right;

    // Rotation
    tmp1->right = nod;
    nod->left = tmp2;

    nod->height = max(height(nod->left), height(nod->right)) + 1;
    tmp1->height = max(height(tmp1->left), height(tmp1->right)) + 1;

    return tmp1;
}

node* balance(node* root, int val) {
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance_factor = height(root->left) - height(root->right);

    // Case 1 Left Left
    if(balance_factor > 1 && val < root->left->val) {
        return right_rotate(root);
    }

    // Case 2 Left Right
    if(balance_factor > 1 && val > root->left->val) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Case 3 Right Left
    if(balance_factor < -1 && val < root->right->val) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    // Case 4 Right Right
    if(balance_factor < -1 && val > root->right->val) {
        return left_rotate(root);
    }
    return root;
}

node* left_rotate(node* nod) {
    node* tmp1 = nod->right;
    node* tmp2 = tmp1->left;

    // Rotation
    tmp1->left = nod;
    nod->right = tmp2;

    nod->height = max(height(nod->left), height(nod->right)) + 1;
    tmp1->height = max(height(tmp1->left), height(tmp1->right)) + 1;

    return tmp1;
}

node* insert_avl(node* root, int val) {
    if(root == NULL) {
        root = new node(val);
        return root;
    }

    if(root->val > val) {
        root->left = insert_avl(root->left, val);
    }
    else if(root->val < val) {
        root->right = insert_avl(root->right, val);
    } else {
        return root;
    }

    return balance(root, val);
}

void print_avl() {
    if (avl_root == NULL) {
        return;
    }
    cout<<endl<<"AVL is"<<endl;
    queue<node*> q;
    q.push(avl_root);
    node* tmp;

    while(!q.empty()) {
        tmp = q.front();
        q.pop();

        cout<<tmp->val<<"("<<tmp->height<<")\t";
        if(tmp->left != NULL) {
            q.push(tmp->left);
        }
        if(tmp->right != NULL) {
            q.push(tmp->right);
        }
    }
    cout<<endl;
}

node* delete_from_avl(node* root, int val) {
    if (root == NULL) {
        return root;
    }
    if(root->val == val) {
        // node found , first find the successor
        node* successor = find_successor(root);
        return successor;
    }
    if(root->val < val) {
        root->right = delete_from_avl(root->right, val);
    }
    if(root->val > val) {
        root->left = delete_from_avl(root->left, val);
    }
    return balance(root, val);
}

node* find_successor(node* nod) {
    if(nod->left == NULL && nod->right == NULL) {
        return NULL;
    }
    if(nod->left != NULL && nod->right == NULL) {
        return nod->left;
    }
    if(nod->left == NULL && nod->right != NULL) {
        return nod->right;
    } else {
        // Both subtree present
        node* tmp = nod->right;
        while(tmp->left != NULL) {
            tmp = tmp->left;
        }
        // Before return  delete original
        nod->val = tmp->val;
        nod->right = delete_from_avl(nod->right, tmp->val);
        free(tmp);
        return nod;
    }
}

int main() {
    int arr[] = {9, 5, 10, 0, 6, 11, -1, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    for(int i=0; i<n; i++) {
        avl_root = insert_avl(avl_root, arr[i]);
    }

    print_avl();

    cout<<endl<<"Deleting node 10"<<endl;
    avl_root = delete_from_avl(avl_root, 10);
    print_avl();
    return 0;
}