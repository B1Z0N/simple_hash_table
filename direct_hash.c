#include "hash.h"

typedef struct {
    int key;
} item;

typedef struct {
    int size;
    item *array;
} h_table;

h_table * h_init(int max);
void h_add(void * h, int k, int * cmp, int * cop);
void h_del(h_table * hash, item key);
item* h_sch(void * h, int k, int * cmp, int * cop);
void h_free(h_table ** h);


int main() {
    h_table * tab;
    tab = h_init(MAX);
    int i;

    void (*add_func_ptr) (void *, int, int *, int *) = h_add;
    item * (*sch_func_ptr) (void *, int, int *, int *) = h_sch;
    
    for(i = 0; i < TEST_NUM; i++)
        h_gen_rand((void *) tab, MAX, add_func_ptr);
    printf("!\n!\n!\n");

    for(i = 0; i < TEST_NUM; i++)
        h_gen_rand((void *) tab, MAX, (void *) sch_func_ptr);

    h_free(&tab);
    return (0);
}

h_table * h_init(int max) {
    h_table *temp = (h_table *) malloc(sizeof(h_table));
    temp->array = (item *) malloc(sizeof(item) * max);

    for(int i = 0; i < max; i++)
        temp->array[i].key = 0;

    return(temp);
}
void h_add(void * h, int k, int * cmp, int * cop) {
 
    item key;
    key.key = k;

    h_table * hash = (h_table *) h;

    if(hash->array[key.key].key) {
        (*cmp)++;
       // printf("\nERROR::KEY::%d::ALREADY_EXISTS\n", key.key); 
    } else {
        (*cop)++;
        hash->array[key.key] = key;
    }
}
void h_del(h_table * hash, item key) {
    hash->array[key.key].key = 0;
}
item* h_sch(void * h, int k, int * cmp, int * cop) {
     h_table * hash = (h_table *) h;


    if(!(hash->array[k].key)) {
        (*cmp)++;
       // printf("\nERROR::KEY::%d::DOESN`T_EXISTS\n", key.key);
    }
    
    (*cop)++;

    return(&(hash->array[k]));
}
void h_free(h_table ** h) {
    free((*h)->array);
    free(*h);
}

