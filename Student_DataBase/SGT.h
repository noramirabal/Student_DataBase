#ifndef SGT_H
#define SGT_H

#include "TreeNode.h"
#include <cmath>
#include <iostream>

using namespace std;

template <typename T>
class SGT
{
public:
    SGT();
    virtual ~SGT();
    int getSize(TreeNode<T> *subTreeRoot);
    int getSizeFromRoot();
    void insert(T d);
    void remove(T d);
    bool exists(T* d);
    bool existsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
    void printTreeInOrder();
    void printTreePostOrder();
    void rebuildSubTree(TreeNode<T> *rebuildNode);
    TreeNode<T> *getScapeGoat(TreeNode<T> *newNode);
    T getMin();
    T getMax();
    T getMedian();
    T search(T* d);
    T searchHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
    TreeNode<T> *getRoot();
    T getRootData();
    T getChildData();
    void printToFile(ofstream &log);
    void printToFileHelper(TreeNode<T>* subTreeRoot,ofstream &log);


private:
    int m_size;          // number of nodes in the tree
    int m_depth;         // checks distance from specified node
    int removeCount;     // how many times we've deleted without rebuilding
    TreeNode<T> *m_root; // the root of the tree
    void insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode);
    void findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent);
    void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
    int buildArray(TreeNode<T> *node, TreeNode<T> *array[], int i);
    TreeNode<T> *getSuccessor(TreeNode<T> *rightChild);
    TreeNode<T> *buildBalancedArray(TreeNode<T> **array, int i, int n);
};

template <typename T>
SGT<T>::SGT()
{
    m_root = nullptr;
    m_size = 0;
    m_depth = 0;
}

template <typename T>
SGT<T>::~SGT()
{
    if (m_root != nullptr)
    {
        delete m_root;
    }
}

// returns the number of nodes in the subtree
template <typename T>
int SGT<T>::getSize(TreeNode<T> *subtreeRoot)
{
    if (subtreeRoot == nullptr)
    { // if the node is null the size is 0
        return 0;
    }
    return 1 + getSize(subtreeRoot->m_left) + getSize(subtreeRoot->m_right); // calculates the total size of the tree
}

template <typename T>
int SGT<T>::getSizeFromRoot(){
    return m_size;
}

template <typename T>
void SGT<T>::insert(T d)
{
    ++m_size;
    TreeNode<T> *newNode = new TreeNode<T>(d); // converting the data into a node
    insertHelper(m_root, newNode);             // passes the root of the tree and the new node
    if (m_depth > log2(m_size) * 1.7)
    { // checking if the node inserted is too deep
        TreeNode<T> *scapeGoat = getScapeGoat(m_root);
        if (scapeGoat->m_parent != nullptr){
            rebuildSubTree(scapeGoat->m_parent);
        } else{
            rebuildSubTree(scapeGoat);
        }
    }
    m_depth = 0;
}

template <typename T>
void SGT<T>::insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode)
{
    if (subTreeRoot == nullptr)
    {
        subTreeRoot = newNode; // adds the node to the empty spot
    }
    else if (newNode->m_data < subTreeRoot->m_data)
    {
        ++m_depth;
        insertHelper(subTreeRoot->m_left, newNode);
    }
    else
    {
        ++m_depth;
        insertHelper(subTreeRoot->m_right, newNode);
    }
}

template <typename T>
TreeNode<T> *SGT<T>::getScapeGoat(TreeNode<T> *newNode)
{
    if (newNode->m_parent != nullptr){
        TreeNode<T> *parentNode = newNode->m_parent;
        while (3 * getSize(parentNode) <= 2 * getSize(parentNode->m_parent))
        {
            parentNode = parentNode->m_parent;
        }
        return parentNode;
    } 
    return newNode;
}

template <typename T>
void SGT<T>::findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent)
{
    while (target != nullptr && target->m_data != key)
    {
        parent = target;
        if (key < target->m_data)
        {
            target = target->m_left;
        }
        else
        {
            target = target->m_right;
        }
    }
}

template <typename T>
void SGT<T>::remove(T d)
{
    // check if empty
    TreeNode<T>* target = nullptr;
    TreeNode<T>* parent = nullptr;
    target = m_root;
    findTarget(d, target, parent);
    if (target == nullptr)
    { // value wasn't in tree, nothing to do
        return;
    }
    // check if leaf (including the root)
    if (target->m_left == nullptr && target->m_right == nullptr)
    { // no children, it's a leaf
        if (target == m_root)
        { // leaf is the root of tree
            m_root = nullptr;
        }
        else
        { // it's not the root
            if (target == parent->m_left)
            {
                parent->m_left = nullptr;
            }
            else
            {
                parent->m_right = nullptr;
            }
        }
        if (m_depth > log2(m_size) * 1.7) 
        {
            rebuildSubTree(target);
        }
        //delete target;
    }
    else if (target->m_left != nullptr && target->m_right != nullptr)
    { // 2 child case
        TreeNode<T>* suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value); // remove successor treenode
        target->m_data = value;
        if (m_depth > log2(m_size) * 1.7) 
        {
            rebuildSubTree(target);
        }
    }
    else
    { // 1 child
        TreeNode<T> *child;
        if (target->m_left != nullptr)
        {
            child = target->m_left;
        }
        else
        {
            child = target->m_right;
        }
        if (target == m_root)
        {
            m_root = child;
        }
        else
        {
            if (target == parent->m_left)
            {
                parent->m_left = child;
            }
            else
            {
                parent->m_right = child;
            }
        }
        //delete target;
    }
    if (m_depth > log2(m_size) * 1.7) 
        {
            rebuildSubTree(target);
        }
    --m_size;
}

// template <typename T>
// void SGT<T>::printTreeInOrder()
// {
//     printTreeInOrderHelper(m_root, 0);
//     cout << "m_root: " << m_root->m_data << endl;
// }

// template <typename T>
// void SGT<T>::printTreeInOrderHelper(TreeNode<T> *subTreeRoot, int depth /*= 0*/)
// {
//     if (subTreeRoot != nullptr)
//     {    
//         printTreeInOrderHelper(subTreeRoot->m_left, depth + 1);
//         string depth_spaces_cstr = "";
//         for (int i = 0; i < depth; ++i)
//             depth_spaces_cstr += "    ";
//         cout << depth_spaces_cstr << subTreeRoot->m_data << endl;
//         printTreeInOrderHelper(subTreeRoot->m_right, depth + 1);
//     }
// }

template <typename T>
void SGT<T>::printTreeInOrder(){
  printTreeInOrderHelper(m_root);
}

template <typename T>
void SGT<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != nullptr){
    printTreeInOrderHelper(subTreeRoot->m_left);
    T temp = subTreeRoot->getData();
    temp.printMethod();
    printTreeInOrderHelper(subTreeRoot->m_right);
  }
}

template <typename T>
void SGT<T>::printToFile(ofstream &log)
{
  printToFileHelper(m_root, log);
}

template <typename T>
void SGT<T>::printToFileHelper(TreeNode<T> *subTreeRoot, ofstream &log)
{
  if (subTreeRoot != NULL)
  {
    printToFileHelper(subTreeRoot->m_left, log);
    T temp = subTreeRoot->getData();
    temp.printMethodToFile(log);
    printToFileHelper(subTreeRoot->m_right, log);
  }
}

template <typename T>
void SGT<T>::rebuildSubTree(TreeNode<T> *rebuildNode)
{
    int subTreeSize = getSize(rebuildNode);
    TreeNode<T> *parentNode = rebuildNode->m_parent;
    TreeNode<T> **storageArr = new TreeNode<T> *[subTreeSize];
    buildArray(rebuildNode, storageArr, 0);
    if (parentNode == nullptr)
    {
        m_root = buildBalancedArray(storageArr, 0, subTreeSize);
        m_root->m_parent = nullptr;
    }
    else if (parentNode->m_right == rebuildNode)
    {
        parentNode->m_right = buildBalancedArray(storageArr, 0, subTreeSize);
        parentNode->m_right->m_parent = parentNode;
    }
    else {
        parentNode->m_left = buildBalancedArray(storageArr, 0, subTreeSize);
        parentNode->m_left->m_parent = parentNode;
    }
}

template <typename T>
int SGT<T>::buildArray(TreeNode<T> *node, TreeNode<T> *array[], int i)
{
    if (node == nullptr)
    {
        return i;
    }
    else {
        i = buildArray(node->m_left, array, i);
        array[i++] = node;
        return buildArray(node->m_right, array, i);
    }
}

template <typename T>
TreeNode<T>* SGT<T>::getRoot(){
    return m_root;
}

template <typename T>
T SGT<T>::getRootData(){
    return m_root->m_data;
}

template <typename T>
TreeNode<T> *SGT<T>::buildBalancedArray(TreeNode<T> **array, int i, int n)
{
    if (n == 0)
    {
        return nullptr;
    }
    int m = n / 2;
    array[i + m]->m_left = buildBalancedArray(array, i, m);
    if (array[i + m]->m_left != nullptr)
    {
        array[i + m]->m_left->m_parent = array[i + m];
    }
    array[i + m]->m_right = buildBalancedArray(array, i + m + 1, n - m - 1);
    if (array[i + m]->m_right != nullptr)
    {
        array[i + m]->m_right->m_parent = array[i + m];
    }
    return array[i + m];
}

template <typename T>
TreeNode<T> *SGT<T>::getSuccessor(TreeNode<T> *rightChild)
{
    while (rightChild->m_left != nullptr)
    {
        rightChild = rightChild->m_left;
    }
    return rightChild;
}

template <typename T>
T SGT<T>::search(T* d){
    TreeNode<T>* newNode = new TreeNode<T>(*d);
    return searchHelper(m_root, newNode);
}

template <typename T>
T SGT<T>::searchHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
    while (newNode->m_data != subTreeRoot->m_data){
        if(newNode->m_data < subTreeRoot->m_data){
            return searchHelper(subTreeRoot->m_left,newNode);
        } else{
            return searchHelper(subTreeRoot->m_right,newNode);
        }
    }
    return subTreeRoot->m_data;
}

template <typename T>
bool SGT<T>::exists(T* d){
  TreeNode<T>* newNode = new TreeNode<T>(*d);
  return existsHelper(m_root, newNode);
}
template <typename T>
bool SGT<T>::existsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
    return false;
  } else if(newNode->m_data == subTreeRoot->m_data){
    return true;
  } else if(newNode->m_data < subTreeRoot->m_data){
    return existsHelper(subTreeRoot->m_left,newNode);
  } else{
    return existsHelper(subTreeRoot->m_right,newNode);
  }
} 



#endif