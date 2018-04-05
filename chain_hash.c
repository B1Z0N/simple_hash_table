#include "hash.h"

typedef struct node {
    struct node * next;
    int key;
} node;

typedef struct h_table {
    node ** array;
    int size;
} h_table;

node * n_init();
void n_add(node ** root, int key, int * cmp, int * cop);
void n_del(node ** root, int key);
node * n_sch(node * root, int key, int * cmp, int * cop);

h_table * h_init(int max);
void h_add(void * h, int key, int * cmp, int * cop);
void h_del(h_table * h, int key);
node * h_sch(void * h, int key, int * cmp, int * cop);
void h_free(h_table ** h);
int main() {
    h_table * hash;
    int i;
    RAND;

    void (*add_func_ptr) (void *, int, int *, int *) = h_add;
    node *(*sch_func_ptr) (void *, int, int *, int *) = h_sch;
    
    for(i = 0; i < TEST_NUM; i++) {
        hash = h_init(N);
        printf("!\n!\n!\n");
        h_gen_rand((void *) hash, MAX, add_func_ptr);
        printf("!\n!\n!\n");
        h_gen_rand((void *) hash, MAX, (void *) sch_func_ptr);
        h_free(&hash);
    }

    return(0);
}

node * n_init() {
    node * temp = (node *) malloc(sizeof(node));
    temp = NULL;

    return(temp);
}
void n_add(node ** root, int key, int * cmp, int * cop) {
    node * temp = (node *) malloc(sizeof(node));
    temp->key = key;

    temp->next = (*root);
    (*root) = temp;

    (*cop) += 2;
}
void n_del(node ** root, int key) {
    node * prev, * temp = (*root);
    
    if((*root)->key == key) { (*root) = (*root)->next; free(temp); return; }

    while(temp->key != key) {
        prev = temp;
        temp = temp->next;
        if(temp == NULL) return;
    }

    prev->next = temp->next;
    free(temp);
}
node * n_sch(node * root, int key, int * cmp, int * cop) {  
    while(root) {
        (*cmp)++;
        if(root->key == key) return root;
        (*cop)++;
        root = root->next;
    }

    return NULL;
}
////////////////////////////////////////////////////////////
h_table * h_init(int max) {
    h_table * temp = (h_table *) malloc(sizeof(h_table));
    temp->array = (node **) malloc(sizeof(node *) * max);

    temp->size = max;

    for(int i = 0; i < max; i++) {
        temp->array[i] = n_init();
        //temp->array[i]->next = NULL;
    }

    return(temp);
}
void h_add(void * h, int key, int * cmp, int * cop) {
    h_table * tab = (h_table *) h;
    int num = key % tab->size;
    n_add(&(tab->array[num]), key, cmp, cop);

}
void h_del(h_table * h, int key) {
    int num = key % h->size;
    n_del(&(h->array[num]), key);

}

node * h_sch(void * h, int key, int * cmp, int * cop) {
    h_table * tab = (h_table *) h;

    int num = key % tab->size;

    node * temp = n_sch(tab->array[num], key, cmp, cop);
    (*cop)++;
    
    if (!temp) { 
        //printf("\nERROR::KEY::%d::DOESN`T_EXISTS\n", key.key);
        (*cmp)++;
    }    

    return(temp);
}

void h_free(h_table ** h) {
    for(int i = 0; i < (*h)->size; i++)
        free((*h)->array[i]);

    free((*h)->array);
    
    free((*h));
}