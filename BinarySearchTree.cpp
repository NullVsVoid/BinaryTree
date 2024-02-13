//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 12, 2024.
//

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor initializes a node with given data and null child pointers.
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
   private:
    Node* root;

    /**
     * Inserts a node with the given data into the binary search tree.
     *
     * @param node The node of the binary search tree.
     * @param data The data of the node to insert.
     * @return The new node of the binary search tree.
     */
    Node* insert(Node* node, int data) {
        // If the current node is null, we've found the insertion point.
        if (node == nullptr) {
            return new Node(data);
        }

        // Recursively iterate the data in the left or right subtree.
        if (data < node->data) {
            node->left = insert(node->left, data);  // Insert in left subtree.
        } else if (data > node->data) {
            node->right =
                insert(node->right, data);  // Insert in right subtree.
        }

        // Return the node pointer.
        return node;
    }

    /**
     * Removes a node with the given data from the binary search tree.
     *
     * @param node The node of the binary search tree.
     * @param data The data of the node to remove.
     * @return The new node of the binary search tree.
     */
    Node* remove(Node* node, int data) {
        if (node == nullptr) {
            return nullptr;  // Base case: data not found.
        }

        // Recursively search for the node to remove.
        if (data < node->data) {
            node->left = remove(node->left, data);  // Search in left subtree.
        } else if (data > node->data) {
            node->right =
                remove(node->right, data);  // Search in right subtree.
        } else {
            // Node with matching data found, handle deletion.

            // Node with only one child or no children.
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children, get the smallest in the right subtree.
            Node* temp = min_value_node(node->right);

            // Copy the smallest value in the right subtree to the current node.
            node->data = temp->data;

            // Remove the smallest value in the right subtree.
            node->right = remove(node->right, temp->data);
        }

        // Return the (potentially updated) node pointer.
        return node;
    }

    /**
     * Gets the node with the minimum value in the binary search tree.
     *
     * @param node The node of the binary search tree.
     * @return The node with the minimum value in the binary search tree.
     */
    Node* min_value_node(Node* node) {
        Node* current = node;

        // Loop down to find the leftmost leaf.
        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;  // The leftmost node is the smallest.
    }

    /**
     * Searches for a node with the given data in the binary search tree.
     *
     * @param node The node of the binary search tree.
     * @param data The data of the node to search for.
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
     * Prints the binary search tree in order.
     *
     * @param node The node of the binary search tree.
     */
    void print_in_order(Node* node) {
        if (node != nullptr) {
            print_in_order(node->left);      // Visit left subtree.
            std::cout << node->data << " ";  // Visit the node.
            print_in_order(node->right);     // Visit right subtree.
        }
    }

    /**
     * Prints the binary search tree in pre-order.
     *
     * @param node The node of the binary search tree.
     */
    void print_pre_order(Node* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";  // Visit the node.
            print_pre_order(node->left);     // Visit left subtree.
            print_pre_order(node->right);    // Visit right subtree.
        }
    }

    /**
     * Prints the binary search tree in post-order.
     *
     * @param node The node of the binary search tree.
     */
    void print_post_order(Node* node) {
        if (node != nullptr) {
            print_post_order(node->left);    // Visit left subtree.
            print_post_order(node->right);   // Visit right subtree.
            std::cout << node->data << " ";  // Visit the node.
        }
    }

   public:
    // Constructor initializes an empty BST.
    BinarySearchTree() : root(nullptr) {}

    // Overloaded constructor for creating a BST with an initial node.
    BinarySearchTree(int data) : root(new Node(data)) {}

    // Destructor deallocates memory used by the BST.
    ~BinarySearchTree() { delete this->root; }

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
 * Example usage of the BinarySearchTree class.
 */
int main() {
    BinarySearchTree binarySearchTree;

    // Insert nodes into the BST.
    binarySearchTree.insert(50);
    binarySearchTree.insert(30);
    binarySearchTree.insert(20);
    binarySearchTree.insert(40);
    binarySearchTree.insert(70);
    binarySearchTree.insert(60);
    binarySearchTree.insert(80);

    // Display the BST in various traversal orders.

    // In order: 20 30 40 50 60 70 80
    std::cout << "In order: ";
    binarySearchTree.print_in_order();
    std::cout << std::endl;

    // Pre order: 50 30 20 40 70 60 80
    std::cout << "Pre order: ";
    binarySearchTree.print_pre_order();
    std::cout << std::endl;

    // Post order: 20 40 30 60 80 70 50
    std::cout << "Post order: ";
    binarySearchTree.print_post_order();
    std::cout << std::endl;

    // Search for nodes in the BST.
    std::cout << "Search for 20: " << binarySearchTree.search(20) << std::endl;
    std::cout << "Search for 10: " << binarySearchTree.search(10) << std::endl;

    Node* searchResult = binarySearchTree.search(20);

    if (searchResult != nullptr) {
        std::cout << "Searching for 20... " << searchResult->data << std::endl;
    } else {
        std::cout << "Searching for 20... Not found" << std::endl;
    }

    // Remove nodes from the BST.
    binarySearchTree.remove(20);
    binarySearchTree.remove(30);
    binarySearchTree.remove(50);

    // Display the BST in order after removing nodes.
    std::cout << "In order: ";
    binarySearchTree.print_in_order();
    std::cout << std::endl;

    return 0;
}