#include "tree.hpp"

void treeInit (Tree **t) {
    *t = NULL;
}

void treeInsert (Tree **t, Data content, int *previousLevel) {
    if (*t == NULL) {
        (*t) = new Tree;
        (*t) -> fd = NULL;
        (*t) -> fe = NULL;
        content.level = *previousLevel + 1;
        (*t) -> item = content;
    } else {
        if ((*t) -> item.value > content.value) {
            treeInsert(&(*t) -> fe, content, &(*t) -> item.level);
        } else {
            treeInsert(&(*t) -> fd, content, &(*t) -> item.level);
        }
    }
}