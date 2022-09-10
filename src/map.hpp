#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"

using namespace std;

string stringTreatment(string palavra); 
void trataArquivo(unordered_map<string, Record> map);
bool verificaMapa(unordered_map<string, Record> map, string key);

#endif