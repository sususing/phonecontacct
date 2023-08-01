#include <iostream>
#include <string>

struct Node {
    // ... (same as the previous implementation)
    Node* links[26] = { nullptr };
    bool flag = false;
    std::string str = "";

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd(std::string& s) {
        flag = true;
        str = s;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node;
    }

    void insert(std::string word, std::string contact) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node);
            }
            node = node->get(word[i]);
        }
        node->setEnd(contact);
    }

    Node* startsWith(std::string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (!node->containsKey(prefix[i]))
                return nullptr;
            node = node->get(prefix[i]);
        }
        return node;
    }

    void displayContact(Node* node, std::string& s, std::ostream& out) {
        if (node->isEnd()) {
            out << s << " " << node->str << std::endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != nullptr) {
                char cha = 'a' + i;
                std::string st = s + cha;
                displayContact(node->links[i], st, out);
            }
        }
    }

    void display(std::string s) {
        Node* node = startsWith(s);
        if (node == nullptr)
            std::cout << "No contact" << std::endl;
        else
            displayContact(node, s, std::cout);
    }

    bool remove(std::string word) {
        return removeContact(root, word, 0);
    }

    ~Trie() {
        deleteTrie(root);
    }

private:
    void deleteTrie(Node* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < 26; i++) {
            deleteTrie(node->links[i]);
        }
        delete node;
    }

    bool removeContact(Node* node, const std::string& word, int depth) {
        if (!node)
            return false;

        if (depth == word.length()) {
            if (!node->isEnd())
                return false;
            node->flag = false;
            node->str = "";
            return isNodeEmpty(node);
        }

        int index = word[depth] - 'a';
        if (removeContact(node->links[index], word, depth + 1)) {
            delete node->links[index];
            node->links[index] = nullptr;
            return !node->isEnd() && isNodeEmpty(node);
        }

        return false;
    }

    bool isNodeEmpty(Node* node) {
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != nullptr) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Trie* t = new Trie();

    int option;
    do {
        std::cout << "\nOptions:\n";
        std::cout << "1. Insert Contact\n";
        std::cout << "2. Search Contact\n";
        std::cout << "3. Delete Contact\n";
        std::cout << "4. Show Names Starting with\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter the option number: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                // Case 1: Insert Contacts
                std::cout << "\nCase 1: Insert Contact\n";
                std::string name, phone;
                std::cout << "Contact name: ";
                std::cin >> name;
                std::cout << "Contact phone number: ";
                std::cin >> phone;
                t->insert(name, phone);
                break;
            }

            case 2: {
                // Case 2: Search Contacts
                std::cout << "\nCase 2: Search Contact\n";
                std::cout << "Enter the contact name you want to search: ";
                std::string q;
                std::cin >> q;
                t->display(q);
                break;
            }

            case 3: {
                // Case 3: Delete Contacts
                std::cout << "\nCase 3: Delete Contact\n";
                std::cout << "Enter the contact name you want to remove: ";
                std::string q;
                std::cin >> q;
                if (t->remove(q)) {
                    std::cout << "Contact removed successfully!" << std::endl;
                } else {
                    std::cout << "Contact not found!" << std::endl;
                }
                break;
            }

            case 4: {
                // Case 4: Show Names Starting with
                std::cout << "\nCase 4: Show Names Starting with\n";
                std::cout << "Enter the prefix to search: ";
                std::string prefix;
                std::cin >> prefix;
                t->display(prefix);
                break;
            }

            case 5: {
                // Case 5: Exit
                std::cout << "Exiting program...\n";
                break;
            }

            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (option != 5);

    delete t; // Clean up dynamically allocated memory
    return 0;
}
