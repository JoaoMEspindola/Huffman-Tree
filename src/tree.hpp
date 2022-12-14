#ifndef TREE_HPP
#define TREE_HPP

#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	string palavra;
	int RP;
	float normalizedRP;
	string wordBin;
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
};

Tree* CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);
int isInTree(Tree *t, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);
void posordem(Tree *t);
void central(Tree *t);

#endif