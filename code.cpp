#include <iostream>
#include <string>
using namespace std;
struct Node {
    // ... (same as the previous implementation)
    Node* links[26] = { nullptr };
    bool flag = false;
    string str = "";

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd(string& s) {
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

    void insert(string word,string contact) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node);
            }
            node = node->get(word[i]);
        }
        node->setEnd(contact);
    }

    Node* startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (!node->containsKey(prefix[i]))
                return nullptr;
            node = node->get(prefix[i]);
        }
        return node;
    }

    void displayContact(Node* node, string& s, ostream& out) {
        if (node->isEnd()) {
            out << s << " " << node->str << std::endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != nullptr) {
                char cha = 'a' + i;
                string st = s + cha;
                displayContact(node->links[i], st, out);
            }
        }
    }

    void display(string s) {
        Node* node = startsWith(s);
        if (node == nullptr)
            cout << "No contact" << endl;
        else
            displayContact(node, s, cout);
    }

    bool remove(string word) {
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

    bool removeContact(Node* node, const string& word, int depth) {
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
        cout << "\nOptions:\n";
        cout << "1. Insert Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Show Names Starting with\n";
        cout << "5. Exit\n";
        cout << "Enter the option number: ";
        cin >> option;

        switch (option) {
            case 1: {
                // Case 1: Insert Contacts
                cout << "\nCase 1: Insert Contact\n";
                string name, phone;
                cout << "Contact name: ";
                cin >> name;
                cout << "Contact phone number: ";
                cin >> phone;
                t->insert(name, phone);
                break;
            }

            case 2: {
                // Case 2: Search Contacts
                cout << "\nCase 2: Search Contact\n";
                cout << "Enter the contact name you want to search: ";
                string q;
                cin >> q;
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
                cout << "\nCase 4: Show Names Starting with\n";
                cout << "Enter the prefix to search: ";
                string prefix;
                cin >> prefix;
                t->display(prefix);
                break;
            }

            case 5: {
                // Case 5: Exit
                cout << "Exiting program...\n";
                break;
            }

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (option != 5);

    delete t; // Clean up dynamically allocated memory
    return 0;
}
