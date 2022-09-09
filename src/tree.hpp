#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
using namespace std;

typedef struct Data Data;
typedef struct Tree Tree;

struct Data {
    int value;
    int level;
};

struct Tree {
    Data item;
    Tree *fe, *fd;
};

void treeInit(Tree **t);
void treeInsert(Tree **t, Data value, int *previousLevel);