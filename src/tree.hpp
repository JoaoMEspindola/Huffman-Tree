#ifndef TREE_HPP
#define TREE_HPP

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <unordered_map>
#include <iostream>
#include <string>

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	string palavra;
	int cont;
	int RP;
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

#endif