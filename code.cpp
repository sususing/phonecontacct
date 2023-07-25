
#include <iostream>
#include <string>
struct Node {
    Node* links[26] = { NULL };
    bool flag = false;
    std::string str = "";
    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
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
                return NULL;
            node = node->get(prefix[i]);
        }
        return node;
    }
    void displayContact(Node* node, std::string& s, std::ostream& out) {
        if (node->isEnd()) {
            out << s << " " << node->str << std::endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != NULL) {
                char cha = 'a' + i;
                std::string st = s + cha;
                displayContact(node->links[i], st, out);
            }
        }
    }
    void display(std::string s) {
        Node* node = startsWith(s);
        if (node == NULL)
            std::cout << "No contact" << std::endl;
        else
            displayContact(node, s, std::cout);
    }
    ~Trie() {
        deleteTrie(root);
    }
private:
    void deleteTrie(Node* node) {
        if (node == NULL)
            return;
        for (int i = 0; i < 26; i++) {
            deleteTrie(node->links[i]);
        }
        delete node;
    }
};
int main() {
    Trie* t = new Trie();
    int n;
    std::cout << "Number of contacts that you want in your phone list: ";
    std::cin >> n;
    std::cout << "Enter names and phones of your phone list:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::string name, phone;
        std::cin >> name >> phone;
        t->insert(name, phone);
    }
    std::cout << "Enter the number of queries: ";
    int query;
    std::cin >> query;
    for (int i = 0; i < query; i++) {
        std::string q;
        std::cout << "Searched list: ";
        std::cin >> q;
        t->display(q);
    }
    delete t; // Clean up dynamically allocated memory
    return 0;
}
