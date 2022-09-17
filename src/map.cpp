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

				if (aux.compare("a") && aux.compare("à") && aux.compare("e") && aux.compare("é") && aux.compare("o")){

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
	cout << endl;
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
	for (vector <int>:: iterator it = vet.begin(); it != vet.end(); it++){
		cout << "VETOR: " << *it << " ";
	}

	for (unordered_map <string, Record>::iterator it = map.begin(); it != map.end(); it++){
		it->second.normalizedRP = calculaRP(vet[vet.size()-1], vet[0], it->second.RP);
		// cout << endl << "MAPA NORMALIZADO" << it->second.normalizedRP << " ";
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

   		forestAux->esq = NULL; 
    	forestAux->dir = NULL; 

		forestAux->reg.palavra = it->first;
		forestAux->reg.normalizedRP = it->second.normalizedRP;

		forestVet.push_back(forestAux);
	}
	
	orderedVet = sortTree(forestVet);

	while (orderedVet.size() > 1){
		treeAux = new Tree;
		
		// cout << endl << "VETOR MUDANDO: " << endl;
		// for (size_t i = 0; i < orderedVet.size(); i++){
		// 	cout << orderedVet[i]->reg.normalizedRP << " ";
		// }

		treeAux->reg.normalizedRP = orderedVet[0]->reg.normalizedRP + orderedVet[1]->reg.normalizedRP;

		treeAux->esq = orderedVet[0];
		treeAux->dir = orderedVet[1];
		
		// widthPath(treeAux);
		// widthPath2(treeAux);

		orderedVet.erase(orderedVet.begin(), orderedVet.begin()+2);

		orderedVet.push_back(treeAux);

		orderedVet = sortTree(orderedVet);

	}
	widthPath(treeAux);
}

vector<Tree*> sortTree(vector <Tree*> vetTree){
	Tree* sortAux;
	sortAux = new Tree;
	bool swapped = true;

	while(swapped){
		swapped = false;
		for (size_t i = 0; i < vetTree.size()-1; i++){
			if(vetTree[i]->reg.normalizedRP == vetTree[i+1]->reg.normalizedRP){
				sortAux = vetTree[i];
				vetTree[i] = vetTree[i+1];
				vetTree[i+1] = sortAux;
			}
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

vector <bool> stringToBoolVector(string palavraBin){
	char vetPalavra[palavraBin.length() + 1];
	vector <bool> binVet;

	strcpy(vetPalavra, palavraBin.c_str());

	for (size_t i = 0; i < palavraBin.length(); i++){
		if(vetPalavra[i] == '1'){
			binVet.push_back(1);
		}else{
			binVet.push_back(0);
		}
		cout << vetPalavra[i];
	}

	return binVet;
}

void writeBinFile(unordered_map <string, string> stringMap){
	fstream fileBin;
	ifstream file;
	string line;
	vector <bool> vetBin;

	fileBin.open("binSample.dat", ios_base::out | ios_base::binary | ios_base::app);
	file.open("test.txt");
	while(!file.eof()){
		getline(file, line, ' ');
		if((stringMap.find(line) != stringMap.end())){
			cout << endl;
			vetBin = stringToBoolVector(stringMap[line]);
			for (size_t i = 0; i < vetBin.size(); i++){
				fileBin.put(vetBin[i]);
			}
			fileBin.put(' ');
			vetBin.clear();
		}
	}
	fileBin.close();
	file.close();
}

void widthPath(Tree *t){
  Fila q;
  Item no, filho;
  unordered_map <string, string> mapAux;

  FFVazia(&q);
  no.p = t;
  Enfileira(&q, no);

  while (!isVazia(&q)){

    Desenfileira(&q, &no);
    cout << endl;
    cout << " " << no.p->reg.palavra;
    cout << " " << no.p->reg.wordBin;

    if(no.p->esq != NULL){
      filho.p = no.p->esq;
	  filho.p->reg.wordBin = no.p->reg.wordBin + '0';
	  mapAux.emplace(filho.p->reg.palavra, filho.p->reg.wordBin);
      Enfileira(&q, filho);
      // printf(" Entrei esquerda! ");
    }

    if(no.p->dir != NULL){
      filho.p = no.p->dir;
	  filho.p->reg.wordBin = no.p->reg.wordBin + '1';
	  mapAux.emplace(filho.p->reg.palavra, filho.p->reg.wordBin);
      Enfileira(&q, filho);
      // printf(" Entrei direita! ");
    }
  }

	writeBinFile(mapAux);
}