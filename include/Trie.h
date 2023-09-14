#pragma once

#include <map>
#include <string>

class Node {
public:
    explicit Node() noexcept: isWord(false) {}

    explicit Node(bool isWord) : isWord(isWord), next() {}

public:
    bool isWord;
    std::map<char, Node> next;
};

class Trie {
public:
    explicit Trie() : size(0) {
        root = new Node();
    }

    ~Trie() noexcept {
        delete root;
        root = nullptr;
    }

    constexpr int getSize() const noexcept {
        return size;
    }

    void add(const std::string &word) {
        Node *cur = root;
        for (int i = 0; i < word.length(); ++i) {
            const char c = word.at(i);
            if (cur->next.find(c) == cur->next.end()) {     //如果找不到字母，就说明这个字母还没添加
                cur->next.insert(std::pair<char, Node>(c, Node()));
            }
            cur = &cur->next.find(c)->second;
        }

        if (!cur->isWord) { //如果以前不表示单词的结尾，否侧添加重复
            cur->isWord = true;
            size++;
        }
    }

    bool contains(const std::string &word) {
        const Node *cur = root;
        for (int i = 0; i < word.length(); ++i) {
            const char c = word.at(i);
            if (cur->next.find(c) == cur->next.end()) { //如果其中字母找不到，就说明单词不匹配直接看返回
                return false;
            }
            cur = &cur->next.find(c)->second;
        }
        return cur->isWord; //如果是 int interesting 类似的前缀， 所以返回记录是否为字母结尾的成员变量
    }

    //查询单词是否为前缀
    bool isPrefix(const std::string &prefix) {
        const Node *cur = root;
        for (int i = 0; i < prefix.length(); ++i) {
            const char c = prefix.at(i);
            if (cur->next.find(c) == cur->next.end()) {
                return false;
            }
            cur = &cur->next.find(c)->second;
        }
        return true;
    }

private:
    Node *root;
    int size;
};
