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
	string line, auxiliar, auxiliar_2, delimiter = " ";
	Record aux;
	size_t pos = 0;
	myfile.open("test.txt");

	if (myfile.is_open()) {
		while(!myfile.eof()) {
			getline(myfile, line);
			aux.palavra = line;
			while ((pos = line.find(delimiter)) != string::npos) {
				aux.palavra = (line.substr(0, pos));
				line.erase(0, pos + delimiter.size());
				auxiliar = aux;
				auxiliar_2 = string_treatment(auxiliar);
				aux.palavra = auxiliar_2;

                if (!(verificaMapa(map, aux.palavra))){
                    map.emplace(palavra, aux);
                    aux.cont = 1;
                }else{
                    cout << "Palavra encontrada no Mapa: " << palavra << endl;
                    map[palavra].cont++;
                }
			}
		}
	}

	myfile.close();
}

bool verificaMapa(unordered_map<string, Record> map, string key) {
    auto verifica = map.find(key);

    if (verifica != map.end()) {
        return true;
    }
    
    return false;
}