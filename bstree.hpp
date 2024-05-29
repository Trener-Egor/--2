#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>

class BSTree {
private:
    struct Node {
        int   data;
        Node* left;
        Node* right;

        Node(int value) 
			: data(value)
			, left(nullptr)
			, right(nullptr)
		{}
    };

    Node* root;

    void add_element(Node*& node, int value, bool& inserted) 
	{
        if (node == nullptr) {
            node = new Node(value);
			inserted = true;
        } 
		else if (value < node->data) {
            add_element(node->left, value, inserted);
        } 
		else if (value > node->data) {
            add_element(node->right, value, inserted);
        }
    }

    Node* delete_element(Node* node, int value, bool& deleted) 
	{
        if (node == nullptr) {
			return node;
		}
        if (value < node->data) {
            node->left = delete_element(node->left, value, deleted);
        } 
		else if (value > node->data) {
            node->right = delete_element(node->right, value, deleted);
        } 
		else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
				deleted = true;
                return temp;
            } 
			else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
				deleted = true;
                return temp;
            } 
			else {
                Node* temp = find_min(node->right);
                node->data = temp->data;
                node->right = delete_element(node->right, temp->data, deleted);
            }
        }
        return node;
    }

    Node* find_min(Node* node) const
	{
        while (node->left != nullptr) 
		{
			node = node->left;
		}
        return node;
    }

    bool find_element(Node* node, int value) const
	{
        if (node == nullptr) {
			return false;
		}
        if (value < node->data) {
			return find_element(node->left, value);
		}
        else if (value > node->data) {
			return find_element(node->right, value);
		}
        else {
			return true;
		}
    }

    void print(Node* node) const
	{
        if (node == nullptr) {
			return;
		}
        print(node->left);

		std::cout << node->data << " ";

        print(node->right);
    }

    void save_to_file(Node* node, std::ofstream& out) const
	{
        if (node == nullptr) {
			return;
		}
        out << node->data << " ";

        save_to_file(node->left, out);
        save_to_file(node->right, out);
    }

    void load_from_file(Node*& node, Node* parent, std::ifstream& in) 
	{
        int value;
		bool inserted = false;
        while (in >> value) 
		{
            add_element(node, value, inserted);
        }
    }

    void destroy_tree(Node* node)
	{
        if (node == nullptr) {
			return;
		}
        destroy_tree(node->left);
        destroy_tree(node->right);

        delete node;
    }

public:
    BSTree() : root(nullptr) {}

    BSTree(std::initializer_list<int> list) : root(nullptr)
	{
        for (int value : list)
		{
            add_element(value);
        }
    }

    bool add_element(int value) 
	{
		bool inserted = false;
        add_element(root, value, inserted);
        return inserted;
    }

    bool delete_element(int value) 
	{
		bool deleted = false;
        root = delete_element(root, value, deleted);
        return deleted;
    }

    bool find_element(int value) const
	{
        return find_element(root, value);
    }

    void print() const
	{
        print(root);
		std::cout << '\n';
    }

    bool save_to_file(const std::string& path) const
	{
		std::ofstream out(path);

        if (!out.is_open()) {
			return false;
		}
        save_to_file(root, out);
        out.close();

        return true;
    }

    bool load_from_file(const std::string& path) 
	{
		std::ifstream in(path);

        if (!in.is_open()) {
			return false;
		}
        destroy_tree(root);
        root = nullptr;

        load_from_file(root, nullptr, in);

        in.close();

        return true;
    }

    ~BSTree() 
	{
        destroy_tree(root);
    }
};


#endif // BSTREE_HPP
