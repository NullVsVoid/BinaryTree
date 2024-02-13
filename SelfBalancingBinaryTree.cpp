//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 12, 2024.
//

#include <algorithm>
#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;  // Height of the node for balancing.

    // Constructor initializes a node with given data and null child pointers.
    // Height will be 1 as it is a new node.
    Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

class SelfBalancingBinaryTree {
   private:
    Node* root;

    /**
     * Gets the height of the node.
     *
     * @param node The node to get the height of.
     * @return The height of the node.
     */
    int height(Node* node) {
        if (node == nullptr) return 0;

        return node->height;
    }

    /**
     * Gets the balance factor of the node.
     *
     * @param node The node to get the balance factor of.
     * @return The balance factor of the node.
     */
    int balance_factor(Node* node) {
        if (node == nullptr) return 0;

        return height(node->left) - height(node->right);
    }

    /**
     * Updates the height of the node.
     *
     * @param node The node to update the height of.
     */
    void update_height(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    /**
     * Rotates the subtree rooted with the given node to the right.
     *
     * @param node The node to rotate.
     * @return The new root of the subtree.
     */
    Node* rotate_right(Node* node) {
        Node* new_root = node->left;
        Node* new_root_right = new_root->right;

        // Perform rotation.
        new_root->right = node;
        node->left = new_root_right;

        // Update heights.
        update_height(node);
        update_height(new_root);

        return new_root;
    }

    /**
     * Rotates the subtree rooted with the given node to the left.
     *
     * @param node The node to rotate.
     * @return The new root of the subtree.
     */
    Node* rotate_left(Node* node) {
        Node* new_root = node->right;
        Node* new_root_left = new_root->left;

        // Perform rotation.
        new_root->left = node;
        node->right = new_root_left;

        // Update heights.
        update_height(node);
        update_height(new_root);

        return new_root;
    }

    /**
     * Inserts a node with the given data into the binary search tree.
     *
     * @param node The node to insert the data into.
     * @param data The data to insert into the binary search tree.
     * @return The new root of the subtree.
     */
    Node* insert(Node* node, int data) {
        // Perform the normal binarySearchTree insertion.
        if (node == nullptr) return new Node(data);

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node;  // Duplicate data not allowed.
        }

        // Update height of this ancestor node.
        update_height(node);

        // Get the balance factor of this ancestor node to check whether this
        // node became unbalanced.
        int balance = balance_factor(node);

        // If the node becomes unbalanced, there are four cases.

        // Left Left Case.
        if (balance > 1 && data < node->left->data) {
            return rotate_right(node);
        }

        // Right Right Case.
        if (balance < -1 && data > node->right->data) {
            return rotate_left(node);
        }

        // Left Right Case.
        if (balance > 1 && data > node->left->data) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        // Right Left Case.
        if (balance < -1 && data < node->right->data) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        // Return the (unchanged) node pointer.
        return node;
    }

    /**
     * Removes a node with the given data from the binary search tree.
     *
     * @param node The node to remove the data from.
     * @param data The data to remove from the binary search tree.
     * @return The new root of the subtree.
     */
    Node* remove(Node* node, int data) {
        // Perform the normal binarySearchTree deletion.
        if (node == nullptr) return node;

        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            // Node with only one child or no child.
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                // No child case.
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;  // Copy the contents of the non-empty child.
                }

                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest
                // in the right subtree).
                Node* temp = node->right;

                while (temp->left != nullptr) {
                    temp = temp->left;
                }

                // Copy the inorder successor's data to this node.
                node->data = temp->data;

                // Delete the inorder successor.
                node->right = remove(node->right, temp->data);
            }
        }

        // If the tree had only one node then return.
        if (node == nullptr) return node;

        // Update height of this ancestor node.
        update_height(node);

        // Get the balance factor of this ancestor node to check whether this
        // node became unbalanced.
        int balance = balance_factor(node);

        // If the node becomes unbalanced, there are four cases.

        // Left Left Case.
        if (balance > 1 && balance_factor(node->left) >= 0) {
            return rotate_right(node);
        }

        // Left Right Case.
        if (balance > 1 && balance_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        // Right Right Case.
        if (balance < -1 && balance_factor(node->right) <= 0) {
            return rotate_left(node);
        }

        // Right Left Case.
        if (balance < -1 && balance_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        // Return the (unchanged) node pointer.
        return node;
    }

    /**
     * Searches for a node with the given data in the binary search tree.
     *
     * @param node The node to search for the data in.
     * @param data The data to search for in the binary search tree.
     * @return The node with the given data if found, nullptr otherwise.
     */
    Node* search(Node* node, int data) {
        // Base cases: root is null or data is present at root.
        if (node == nullptr || node->data == data) {
            return node;
        }

        // Value is greater than root's data.
        if (data < node->data) {
            return search(node->left, data);  // Search in the left subtree.
        } else {
            return search(node->right, data);  // Search in the right subtree.
        }
    }

    /**
     * Inorder traversal of the binary search tree.
     *
     * @param node The node to start the inorder traversal from.
     */
    void print_in_order(Node* node) {
        if (node == nullptr) return;

        print_in_order(node->left);
        std::cout << node->data << " ";
        print_in_order(node->right);
    }

    /**
     * Preorder traversal of the binary search tree.
     *
     * @param node The node to start the preorder traversal from.
     */
    void print_pre_order(Node* node) {
        if (node == nullptr) return;

        std::cout << node->data << " ";
        print_pre_order(node->left);
        print_pre_order(node->right);
    }

    /**
     * Postorder traversal of the binary search tree.
     *
     * @param node The node to start the postorder traversal from.
     */
    void print_post_order(Node* node) {
        if (node == nullptr) return;

        print_post_order(node->left);
        print_post_order(node->right);
        std::cout << node->data << " ";
    }

   public:
    // Constructor initializes an empty binarySearchTree.
    SelfBalancingBinaryTree() : root(nullptr) {}

    // Overloaded constructor for creating a binarySearchTree with an initial
    // node.
    SelfBalancingBinaryTree(int data) : root(new Node(data)) {}

    // Destructor deallocates memory used by the binarySearchTree.
    ~SelfBalancingBinaryTree() { delete this->root; }

    /**
     * Inserts a node with the given data into the binary search tree.
     *
     * @param data The data of the node to insert.
     */
    void insert(int data) { this->root = insert(this->root, data); }

    /**
     * Removes a node with the given data from the binary search tree.
     *
     * @param data The data of the node to remove.
     */
    void remove(int data) { this->root = remove(this->root, data); }

    /**
     * Searches for a node with the given data in the binary search tree.
     *
     * @param data The data of the node to search for.
     * @return The node with the given data if found, nullptr otherwise.
     */
    Node* search(int data) { return search(this->root, data); }

    /**
     * Prints the binary search tree in order.
     */
    void print_in_order() { print_in_order(this->root); }

    /**
     * Prints the binary search tree in pre-order.
     */
    void print_pre_order() { print_pre_order(this->root); }

    /**
     * Prints the binary search tree in post-order.
     */
    void print_post_order() { print_post_order(this->root); }
};

/**
 * Example usage of the SelfBalancingBinaryTree class.
 */
int main() {
    SelfBalancingBinaryTree binarySearchTree;

    // Insert elements to create an initially balanced tree
    std::cout << "Inserting elements to form the tree...\n";
    binarySearchTree.insert(30);
    binarySearchTree.insert(20);
    binarySearchTree.insert(40);
    binarySearchTree.insert(10);
    binarySearchTree.insert(25);
    binarySearchTree.insert(35);
    binarySearchTree.insert(50);

    // Display the tree in order to show initial balanced state
    std::cout << "Initial tree (In order): ";
    binarySearchTree.print_in_order();
    std::cout << "\n";

    // Insert elements that would typically cause imbalance
    std::cout << "\nInserting 5 to cause left imbalance.\n";
    binarySearchTree.insert(5);

    // Display the tree to show re-balanced state
    std::cout << "Tree after inserting 5 (In order): ";
    binarySearchTree.print_in_order();
    std::cout << "\n";

    std::cout << "\nInserting 55 and 60 to cause right imbalance.\n";
    binarySearchTree.insert(55);
    binarySearchTree.insert(60);

    // Display the tree to show re-balanced state
    std::cout << "Tree after inserting 55 and 60 (In order): ";
    binarySearchTree.print_in_order();
    std::cout << "\n";

    // Demonstrate deletion maintaining balance
    std::cout << "\nRemoving 20 (a node with a single child).\n";
    binarySearchTree.remove(20);

    // Display the tree to show re-balanced state
    std::cout << "Tree after removing 20 (In order): ";
    binarySearchTree.print_in_order();
    std::cout << "\n";

    std::cout << "\nRemoving 30 (a node with two children).\n";
    binarySearchTree.remove(30);

    // Display the tree to show it remains balanced after removals
    std::cout << "Tree after removing 30 (In order): ";
    binarySearchTree.print_in_order();
    std::cout << "\n";

    return 0;
}