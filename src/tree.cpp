#include "tree.hpp"

Tree* CreateTree(){
  return NULL;
}

bool TVazia(Tree **t){
  return *t == NULL;
}

void insertTree(Tree **t, Record r){

  if(TVazia(t)){
    *t = new Tree;
    (*t)->esq = NULL; 
    (*t)->dir = NULL; 
    (*t)->reg = r; 
  
  } else {
    
    if(r.normalizedRP < (*t)->reg.normalizedRP){
      insertTree(&(*t)->esq, r);
    }
    
    if(r.normalizedRP > (*t)->reg.normalizedRP){
      insertTree(&(*t)->dir, r);
    }
  
  }

}

void pesquisa(Tree **t, Tree **aux, Record r){

  if(*t == NULL){
    printf("[ERROR]: Node not found!");
    return;
  }

  if((*t)->reg.normalizedRP > r.normalizedRP){ 
    pesquisa(&(*t)->esq, aux, r); 
    return;
  }
  if((*t)->reg.normalizedRP < r.normalizedRP){
    pesquisa(&(*t)->dir, aux, r);
    return;
  }

  *aux = *t;
}


int isInTree(Tree *t, Record r) {
  
  if(t == NULL){ 
    return 0;
  }
  
  return t->reg.normalizedRP == r.normalizedRP || isInTree(t->esq, r) || isInTree(t->dir, r);
}


void antecessor(Tree **t, Tree *aux){ 

	if ((*t)->dir != NULL){ 
		antecessor(&(*t)->dir, aux);
		return;
  }
  	
  aux->reg = (*t)->reg;
  aux = *t; 
  *t = (*t)->esq;
  free(aux);
} 


void removeTree(Tree **t, Record r){
	Tree *aux;
  	
  	if (*t == NULL){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if (r.normalizedRP < (*t)->reg.normalizedRP){ removeTree(&(*t)->esq, r); return; }
  	if (r.normalizedRP > (*t)->reg.normalizedRP){ removeTree(&(*t)->dir, r); return; }

  	if ((*t)->dir == NULL){ 
  		aux = *t;  
  		*t = (*t)->esq;
    	free(aux);
    	return;
  	}

  	if ((*t)->esq != NULL){ antecessor(&(*t)->esq, *t); return; }

  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
}