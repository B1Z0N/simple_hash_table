#include "hash.h"

typedef struct {//
    int key;
} item;

typedef struct {
    int size;
    item **array;
} h_table;

h_table * h_init(int max);
void h_add(void * h, int k, int * cmp, int * cop);
void h_del(h_table * hash, item key);
item* h_sch(void * h, int k, int * cmp, int * cop);
void h_free(h_table ** h);


int main() {
    h_table * tab;
    int i;
    RAND;

    void (*add_func_ptr) (void *, int, int *, int *) = h_add;
    item * (*sch_func_ptr) (void *, int, int *, int *) = h_sch;
    for(i = 0; i < TEST_NUM; i++) {
        tab = h_init(MAX);
        printf("!\n!\n!\n");
        h_gen_rand((void *) tab, MAX, add_func_ptr);
        printf("!\n!\n!\n");
        h_gen_rand((void *) tab, MAX, (void *) sch_func_ptr);
        h_free(&tab);
    }
    
    return (0);
}

h_table * h_init(int max) {
    h_table *temp = (h_table *) malloc(sizeof(h_table));
    temp->array = (item **) malloc(sizeof(item *) * max);

    temp->size = max;

    for(int i = 0; i < max; i++) {
        temp->array[i] = (item *) malloc(sizeof(item));
        temp->array[i] = NULL;
    }

    return(temp);
}
void h_add(void * h, int k, int * cmp, int * cop) {
 
    item *key = (item *)malloc(sizeof(item));
    key->key = k;

    h_table * hash = (h_table *) h;
    (*cmp)++;
    if(hash->array[key->key] != NULL) {  
       // printf("\nERROR::KEY::%d::ALREADY_EXISTS\n", key.key); 
    } else {
        (*cop)++;
        hash->array[key->key] = key;
    }
    free(key);
}
void h_del(h_table * hash, item key) {
    hash->array[key.key] = NULL;
}
item* h_sch(void * h, int k, int * cmp, int * cop) {
     h_table * hash = (h_table *) h;


    if(!(hash->array[k])) {
        (*cmp)++;
       //printf("\nERROR::KEY::%d::DOESN`T_EXISTS\n", key.key);
    }
    
    (*cop)++;

    return(hash->array[k]);
}
void h_free(h_table ** h) {
    for(int i = 0; i < (*h)->size; i++)
        free((*h)->array[i]);

    free((*h)->array);
    free(*h);
}

