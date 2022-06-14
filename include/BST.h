#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include <cassert>

template<typename T>
class BSTNode {
public:
    T e;    //节点元素
    BSTNode<T> *left;   //左节点
    BSTNode<T> *right;  //右节点

public:
    BSTNode(const T &E) : e(E), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    BSTNode<T> *root;   //根节点
    int size;   //大小
/*------------------------------------------------------------------*/
private:
    //返回插入新节点后二分搜索树的根
    BSTNode<T> *add(BSTNode<T> *node, const T &e) {
        if (node == nullptr) {  //如果结点为空
            ++size;     //大小+1
            return new BSTNode<T>(e);   //插入元素e返回新节点
        }
        if (node->e > e) {  //如果要插入的节点值小于当前节点元素
            node->left = add(node->left, e);    //第归左子树直到为空返回新节点为当前节点的左孩子
        } else if (node->e < e) {   //如果要插入的节点值大于当前节点元素
            node->right = add(node->right, e);  //第归右子树直到为空返回新节点为当前节点的右孩子
        }
        return node;    //返回原节点
    }

public:
    void add(const T &e) { //添加节点
        root = add(root, e);    //添加新节点传入根结点和元素并返回新的根结点
    }
/*------------------------------------------------------------------*/
private:
    bool contains(BSTNode<T> *BSTNode, const T &e) const {  //判断是否有元素e
        if (BSTNode == nullptr)return false;   //如果节点为空，则返回false
        if (BSTNode->e == e)return true;   //如果要找的的元素等于节点元素e，则返回true
        else if (BSTNode->e > e) { //如果要找的元素小于节点元素
            return contains(BSTNode->left, e); //则第归当前节点的左子树
        } else { // if(BSTNode->e<e)   //如果要找的元素大于节点元素
            return contains(BSTNode->right, e);    //则第归当前节点的右子树
        }
    }

public:
    bool contains(const T &e) const {    //判断是否有元素e
        return contains(root, e);
    }
/*------------------------------------------------------------------*/
private:
    void preOrder(BSTNode<T> *BSTNode) const {//第归前序遍历
        if (BSTNode == nullptr)return; //如果节点为则空返回
        std::cout << BSTNode->e << std::endl;//打印节点元素
        preOrder(BSTNode->left);   //第归当前节点左子树
        preOrder(BSTNode->right);  //第归当前节点右子树
    }

public:
    void preOrder() const {//第归前序遍历
        preOrder(root);
    }

    //非递归前序遍历 深度优先遍历
    void preOrderNR() const {
        std::stack<BSTNode<T> *> s;//创建一个栈
        s.push(root);//根节点入栈
        while (!s.empty()) {    //如果栈为空，则停止循环
            BSTNode<T> *cur = s.top();  //创建一个节点暂存栈顶节点
            std::cout << cur->e << " "; //打印栈顶节点
            s.pop();    //出栈
            if (nullptr != cur->right) {    //如果栈顶节点右节点不为空
                s.push(cur->right); //栈顶节点右节点如栈
            }
            if (nullptr != cur->left) {     //如果栈顶节点左节点不为空
                s.push(cur->left);  //栈顶节点左节点如栈
            }
        }
        std::cout << std::endl;
    }
/*------------------------------------------------------------------*/
private:
    void inOrder(BSTNode<T> *BSTNode) const {    //第归中序遍历
        if (BSTNode == nullptr)return;
        inOrder(BSTNode->left);
        std::cout << BSTNode->e << " ";
        inOrder(BSTNode->right);
    }
    //也叫排序遍历，它会有序打印二分搜索树
public:
    void inOrder() const {   //第归中序遍历
        inOrder(root);
    }

    //非递归中序遍历
    void inOrderNR() const {
        std::stack<BSTNode<T> *> s; //创建一个栈
        BSTNode<T> *cur = root;     //当前节点为根节点
        while (!s.empty() || nullptr != cur) {  //如果栈为空或当前节点为空
            //树的左边一列入栈
            while (nullptr != cur) {
                s.push(cur);
                cur = cur->left;
            }
            if (!s.empty()) {   //如果栈不为空
                cur = s.top();  //当前节点为栈顶
                std::cout << cur->e << " ";//打印节点元素
                s.pop();    //出栈
                cur = cur->rigfht;   //当节点赋值为当前节点的右节点
            }
        }
        std::cout << std::endl;
    }
/*------------------------------------------------------------------*/
private:
    void postOrder(BSTNode<T> *BSTNode) const {//第归后续遍历
        if (BSTNode == nullptr)return;
        postOrder(BSTNode->left);
        postOrder(BSTNode->right);
        std::cout << BSTNode->e << std::endl;
    }

public:
    void postOrder() const {  //后续遍历
        postOrder(root);
    }

    //后续遍历适用于析沟函数
    void postOrderNR() { //非第归后续遍历
        std::stack<BSTNode<T> *> s;   //创建一个栈
        BSTNode<T> *cur = root;
        BSTNode<T> *temp;
        while (nullptr != cur || !s.empty()) {
            //树的左边一列入栈
            while (nullptr != cur) {
                s.push(cur);
                cur = cur->left;
            }
            if (!s.empty()) { //如果栈不为空
                cur = s.top();  //当前节点为栈顶
                if (cur->right == temp || nullptr == cur->right) {   //如果当前节点为暂存节点的父节点或当前节的右节点为空
                    std::cout << cur->e << " "; //打印当前节点元素
                    s.pop();    //出栈
                    temp = cur; //暂存当前节点
                    cur = nullptr;  //cur赋值为空
                } else {
                    cur = cur->right;   //否则遍历右节点
                }
            }
        }
        std::cout << std::endl;
    }
/*------------------------------------------------------------------*/
public:
    //层次遍历 广度优先遍历 适用于搜索
    void levelOrder() const {
        std::queue<BSTNode<T> *> q;   //创建一个队列
        q.push(root);   //根结点如对
        while (!q.empty()) {  //如果队列不为空
            BSTNode<T> *cur = q.front();    //取出对头节点
            q.pop();    //出队
            std::cout << cur->e << " "; //打印对头节点元素
            if (nullptr != cur->left) {   //如果当前节点的左孩子不为空
                q.push(cur->left);  //则当前节点的左孩子入队
            }
            if (nullptr != cur->right) {   //如果当前节点的右孩子不为空
                q.push(cur->right); //则当前节点的右孩子入队
            }
        }
        std::cout << std::endl;
    }
/*------------------------------------------------------------------*/
private:
    //返回最小值的节点
    BSTNode<T> *min(BSTNode<T> *BSTNode) const {
        if (BSTNode->left == nullptr)  //二分搜索树最小值肯定是最左边的节点
            return BSTNode;
        return min(BSTNode->left);
    }

    //返回最大值的节点
    BSTNode<T> *max(BSTNode<T> *BSTNode) const {
        if (BSTNode->right == nullptr) //二分搜索树最大值肯定是最右边的节点
            return BSTNode;
        return max(BSTNode->right);
    }

public:
    T minimun() const {//返回最小值
        if (size > 0) return min(root)->e;
    }

    T maximun() const {//返回最大值
        if (size > 0) return max(root)->e;
    }
/*------------------------------------------------------------------*/
private:
    //删除以BSTNode为根的二分搜索树的最小节点
    //返回删除节点后新的二分搜搜索树的根结点
    BSTNode<T> *removeMin(BSTNode<T> *node) {
        if (node->left == nullptr) { //如果当前节点左孩子为空
            BSTNode<T> *rightNode = node->right;    //则暂存当前节点的右孩子
            node->right = nullptr;
            delete node;    //删除当前节点
            node = nullptr;
            --size; //个数-1
            return rightNode;   //返回被删除节点的右孩子
        }
        node->left = removeMin(node->left); //第归节点的左孩子，把返回的右孩子放入上一节点的左孩子
        return node;    //返回根结点
    }

    //删除以node为根的二分搜索树的最大节点
    //返回删除节点后新的二分搜搜索树的根结点
    BSTNode<T> *removeMax(BSTNode<T> *node) {
        if (node->right == nullptr) {
            BSTNode<T> *leftNode = node->left;
            node->left = nullptr;
            delete node;
            node = nullptr;
            --size;
            return leftNode;
        }
        node->right = removeMax(node->right);
        return node;
    }

public:
    T removeMin() { //删除最小值并返回最小值
        T ret = minimun();
        root = removeMin(root);
        return ret;
    }

    T removeMax() { //删除最大值并返回最大值
        T ret = maximun();
        root = removeMax(root);
        return ret;
    }
/*------------------------------------------------------------------*/
private:
    //删除元素e 后继法
    BSTNode<T> *RRemove(BSTNode<T> *node, const T &e) {
        if (nullptr == node)return nullptr;  //如果节点为空，则返回空
        if (e < node->e)   //如果要删除元素小于当前节点元素
        {
            node->left = RRemove(node->left, e); //当前节点的左孩子赋值为，第归当前节点的左孩子返回当节点前左孩子的右孩子
            return node;    //返当根节点
        } else if (e > node->e) {//如果要删除元素大于当前节点元素
            node->right = RRemove(node->right, e);//当前节点的右孩子赋值为，第归当前节点的右孩子返回当前节点右孩子的左孩子
            return node;    //返回根节点
        } else { //e == node->e 如果要删除元素等于当前节点元素
            if (nullptr == node->left) {    //如果当前节点没有左孩子
                BSTNode<T> *rightNode = node->right;    //就暂存当前节点的右孩子
                delete node;    //删除当前节点
                --size; //大小-1
                return rightNode;   //返回当前节点的右孩子
            }
            if (nullptr == node->right) {   //如果当前节点没有左孩子
                BSTNode<T> *leftNode = node->left;  //就暂存当前节点的左孩子
                delete node;    //删除当前节点
                --size; //大小-1
                return leftNode;    //返回当前节点的左孩子
            }
            //如果不为空就把离要删除节点最近的比节点要大的节点拿过来，换成它。
            BSTNode<T> *successor = new BSTNode<T>(min(node->right)->e);    //创建一个节点把要删除节点的右子树中最小值给新建节点
            successor->right = removeMin(node->right);  //新建节点的右孩子指向，删除当前节点的右子树中的最小节点并返回这个根结点。
            // removeMin过程中size已经-1，所以不需要再-1
            successor->left = node->left;   //新建节点的左孩子指向要删除节点的左孩子
            node->left = node->right = nullptr; //把要删除节点左右孩子指向空
            delete node;    //删除要删除节点
            return successor;   //返回新建节点给上一级
        }
    }

    //删除元素e 前驱法
    BSTNode<T> *LRemove(BSTNode<T> *node, const T &e) {
        if (nullptr == node)return nullptr;
        if (node->e > e) {
            node->left = LRemove(node->left, e);
            return node;
        } else if (node->e < e) {
            node->right = LRemove(node->right, e);
            return node;
        } else { //node->e == e
            if (nullptr == node->left) {
                BSTNode<T> *rightNode = node->right;
                delete node;
                --size;
                return rightNode;
            }
            if (nullptr == node->right) {
                BSTNode<T> *leftNode = node->left;
                delete node;
                --size;
                return leftNode;
            }
            BSTNode<T> *precursor = new BSTNode<T>(min(node->left)->e);
            precursor->left = removeMin(node->left);
            precursor->right = node->right;
            node->left = node->right = nullptr;
            delete node;
            return precursor;
        }
    }

public:
    void RRemove(const T &e)//删除任意元素e前驱法
    {
        root = RRemove(root, e);
    }

    void LRemove(const T &e)//删除任意元素e后继法
    {
        root = LRemove(root, e);
    }
/*------------------------------------------------------------------*/
private:
    void generateDepthString(const int depth) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << "--";
        }
    }

public:
    void generateBSTString(BSTNode<T> *node, const int depth) const {
        if (node == nullptr) {
            generateDepthString(depth);
            std::cout << "NULL" << std::endl;
            return;
        }
        generateDepthString(depth);
        std::cout << node->e << std::endl;
        generateBSTString(node->left, depth + 1);
        generateBSTString(node->right, depth + 1);
    }

    void print() const {
        generateBSTString(root, 0);
    }
/*------------------------------------------------------------------*/
public:
    BST() : root(nullptr), size(0) {}

    ~BST() {
        clear();
    }

    void clear() {
        int s = size;
        for (int i = 0; i < s; ++i) {
            removeMin();
        }
    }

    constexpr int getSize() const {      //返回当前树的大小
        return size;
    }

    constexpr bool isEmpty() const {  //判断当前树是否为空
        return size == 0;
    }
};