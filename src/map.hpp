#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "fila.hpp"
#include <ostream>

using namespace std;

string stringTreatment(string palavra); 
void trataArquivo(unordered_map<string, Record> map);
bool verificaMapa(unordered_map<string, Record> map, string key);
void normalizaMapa(unordered_map<string, Record> map);
float calculaRP(int RPmax, int RPmin, int cont);
void fazFloresta(unordered_map<string, Record> map);
vector <Tree*> sortTree(vector <Tree*> vetTree);
void codificaPalavra(Tree *t);
vector <bool> stringToBoolVector(string palavraBin);
void writeBinFile(unordered_map<string, Record> stringMap);
void widthPath(Tree *t);

#endif