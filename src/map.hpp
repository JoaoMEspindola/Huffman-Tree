#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"

using namespace std;

string stringTreatment(string palavra); 
void trataArquivo(unordered_map<string, Record> map);
bool verificaMapa(unordered_map<string, Record> map, string key);
unordered_map<string, Record> normalizaMapa(unordered_map<string, Record> map);
float calculaRP(int RPmax, int RPmin, int cont);
void fazFloresta(unordered_map<string, Record> map);
bool cmp(Tree* tree1, Tree* tree2);

#endif