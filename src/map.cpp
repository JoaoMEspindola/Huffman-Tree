#include "map.hpp"

string string_treatment(string s) {
	int size = s.size();
	string aux;

	for (int i = 0; i < size; i++) {
		if (s[i] != '.' && s[i]!= ',' && s[i] != ':' && s[i] != ';' && s[i] != '?' && s[i] != '!' && s[i] != '(' && s[i] != ')' && s[i] != '[' && s[i] != ']' && s[i] != '{'
			&& s[i] != '}' && s[i] != '+'&& s[i] != '=' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '%' && !isdigit(s[i])) {
			s[i] = tolower(s[i]);
            aux += s[i];
		}
	}
 
	return aux;
}

void trataArquivo(unordered_map<string, Record> map){

    ifstream myfile;
	string line, auxiliar, auxiliar_2, delimiter = " ", aux;
	size_t pos = 0;
	myfile.open("test.txt");

	if (myfile.is_open()) {
		while(!myfile.eof()) {
			getline(myfile, line);
			aux = line;

			while ((pos = line.find(delimiter)) != string::npos) {
				aux = (line.substr(0, pos));
				line.erase(0, pos + delimiter.size());
				auxiliar = aux;
				auxiliar_2 = string_treatment(auxiliar);
				aux = auxiliar_2;

				if (aux.compare("a") && aux.compare("nos") && aux.compare("à") && aux.compare("e") && aux.compare("ser") && aux.compare("é")
					&& aux.compare("uma") && aux.compare("em") && aux.compare("como") && aux.compare("por") && aux.compare("da") && aux.compare("das")
					&& aux.compare("dos") && aux.compare("um") && aux.compare("com") && aux.compare("o") && aux.compare("de") && aux.compare("do") && aux.compare("no")
					&& aux.compare("na") && aux.compare("que") && aux.compare("se") && aux.compare("ao") && aux.compare("as") && aux.compare("não")){

					if (!(verificaMapa(map, aux))){
						map[aux].RP = 1;
					}else{
						map[aux].RP++;
					}
				}
			}
		}
	}

	normalizaMapa(map);
	myfile.close();

}

bool verificaMapa(unordered_map<string, Record> map, string key) {
    auto verifica = map.find(key);

    if (verifica != map.end()) {
        return true;
    }
    
    return false;
}

void normalizaMapa(unordered_map <string, Record> map){
	vector <int> vet;
	bool swapped = true;

	for (unordered_map <string, Record>::iterator it = map.begin(); it != map.end(); it++){
		vet.push_back(it->second.RP);
	}

	for (vector <int>:: iterator it = vet.begin(); it != vet.end(); it++){
		cout << "VETOR: " << *it << " ";
	}

	while (swapped){
		swapped = false;
		for (size_t i = 0; i < vet.size()-1; i++){
			if (vet[i] > vet[i+1]){
				vet[i] += vet[i+1];
				vet[i+1] = vet[i] - vet[i+1];
				vet[i] -= vet[i+1];
				swapped = true;
			}
		}
	}
	cout << endl;
	for (vector <int>:: iterator it = vet.begin(); it != vet.end(); it++){
		cout << "VETOR: " << *it << " ";
	}

	for (unordered_map <string, Record>::iterator it = map.begin(); it != map.end(); it++){
		it->second.normalizedRP = calculaRP(vet[vet.size()-1], vet[0], it->second.RP);
		cout << endl << "MAPA NORMALIZADO" << it->second.normalizedRP << " ";
	}

	fazFloresta(map);

}

float calculaRP(int RPmax, int RPmin, int RP){ 
	return (float) RP / (RPmax - RPmin);
}

void fazFloresta(unordered_map<string, Record> map){
	vector <Tree*> forestVet;
	vector <Tree*> orderedVet;

	Tree* forestAux;
	Tree* treeAux;

	for (unordered_map <string, Record>::iterator it = map.begin(); it != map.end(); it++){
		forestAux = new Tree;

		// cout << "BIBAO";

   		forestAux->esq = NULL; 
    	forestAux->dir = NULL; 

		forestAux->reg.palavra = it->first;
		forestAux->reg.normalizedRP = it->second.normalizedRP;

		forestVet.push_back(forestAux);

		cout << forestVet.size();
		// for (size_t i = 0; i < forestVet.size(); i++)
		// 	cout << "VETOR: " << forestVet[i]->reg.normalizedRP << " ";
	}


	// for (size_t i = 0; i < forestVet.size(); i++){
	// 	cout << "ANTES: " << forestVet[i]->reg.normalizedRP << " ";
	// }
	
	orderedVet = sortTree(forestVet);
	

	cout << endl << endl;

	// for (size_t i = 0; i < orderedVet.size(); i++){
	// 	// cout << "DEPOIS: " << orderedVet[i]->reg.normalizedRP << " ";
	// }


	
	while (orderedVet.size() > 1){
		treeAux = new Tree;
		
		orderedVet[0]->reg.charBin = 0;
		orderedVet[1]->reg.charBin = 1;

		for (size_t i = 0; i < orderedVet.size(); i++){
			cout << orderedVet[i]->reg.charBin << " ";
		}

		treeAux->reg.normalizedRP = orderedVet[0]->reg.normalizedRP + orderedVet[1]->reg.normalizedRP;

		treeAux->esq = orderedVet[0];
		treeAux->dir = orderedVet[1];
		
		orderedVet.erase(orderedVet.begin(), orderedVet.begin()+2);

		orderedVet.push_back(treeAux);

		orderedVet = sortTree(orderedVet);

		// for (size_t i = 0; i < orderedVet.size(); i++){
		// 	if (treeAux->reg.normalizedRP < orderedVet[i+1]->reg.normalizedRP){
		// 		orderedVet.insert(orderedVet.begin() + i, treeAux);
		// 	}
		// }

		// for (size_t i = 0; i < orderedVet.size(); i++){
		// 	cout << endl << "VETOR MUDANDO INSERT: " << orderedVet[i]->reg.normalizedRP << " ";
		// }

		cout << endl;

	}


}

vector<Tree*> sortTree(vector <Tree*> vetTree){
	Tree* sortAux;
	sortAux = new Tree;
	bool swapped = true;

	while(swapped){
		swapped = false;
		for (size_t i = 0; i < vetTree.size()-1; i++){
			if(vetTree[i]->reg.normalizedRP > vetTree[i+1]->reg.normalizedRP){
				sortAux = vetTree[i];
				vetTree[i] = vetTree[i+1];
				vetTree[i+1] = sortAux;
				swapped = true;
			}
		}
	}
	
	return vetTree;
}