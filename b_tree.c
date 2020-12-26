#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_KEYS (1024)

typedef struct btNode *bTree;

void btPrintKeys(bTree t);

struct btNode {
    int isLeaf;    
    int numKeys;   
    int keys[MAX_KEYS];
    struct btNode *kids[MAX_KEYS+1];  
};

bTree
btCreate(void)
{
    bTree b;
    b = malloc(sizeof(*b));
    assert(b);
    b->isLeaf = 1;
    b->numKeys = 0;
    return b;
}

void
btDestroy(bTree b)
{
    if(!b->isLeaf) {
        for(int i = 0; i < b->numKeys + 1; i++) {
            btDestroy(b->kids[i]);
        }
    }
    free(b);
}


static int
searchKey(int n, const int *a, int key)
{
    int lo=-1;
    int hi=n;
    int mid;

    while(lo + 1 < hi) {
        mid = (lo+hi)/2;
        if(a[mid] == key) {
            return mid;
        } else if(a[mid] < key) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

int
btSearch(bTree b, int key)
{
    int pos;
    if(b->numKeys == 0) {
        return 0;
    }
    pos = searchKey(b->numKeys, b->keys, key);

    if(pos < b->numKeys && b->keys[pos] == key) {
        return 1;
    } else {
        return(!b->isLeaf && btSearch(b->kids[pos], key));
    }
}


static bTree
btInsertInternal(bTree b, int key, int *median)
{
    int pos;
    int mid;
    bTree b2;
    pos = searchKey(b->numKeys, b->keys, key);

    if(pos < b->numKeys && b->keys[pos] == key) {
   
        return 0;
    }

    if(b->isLeaf) {

       
        memmove(&b->keys[pos+1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
        b->keys[pos] = key;
        b->numKeys++;

    } else {

     
        b2 = btInsertInternal(b->kids[pos], key, &mid);
       
        if(b2) {

            
            memmove(&b->keys[pos+1], &b->keys[pos], sizeof(*(b->keys)) * (b->numKeys - pos));
         
            memmove(&b->kids[pos+2], &b->kids[pos+1], sizeof(*(b->keys)) * (b->numKeys - pos));

            b->keys[pos] = mid;
            b->kids[pos+1] = b2;
            b->numKeys++;
        }
    }

   
    if(b->numKeys >= MAX_KEYS) {
        mid = b->numKeys/2;

        *median = b->keys[mid];

    
        b2 = malloc(sizeof(*b2));

        b2->numKeys = b->numKeys - mid - 1;
        b2->isLeaf = b->isLeaf;

        memmove(b2->keys, &b->keys[mid+1], sizeof(*(b->keys)) * b2->numKeys);
        if(!b->isLeaf) {
            memmove(b2->kids, &b->kids[mid+1], sizeof(*(b->kids)) * (b2->numKeys + 1));
        }

        b->numKeys = mid;

        return b2;
    } else {
        return 0;
    }
}

void
btInsert(bTree b, int key)
{
    bTree b1;   
    bTree b2;   
    int median;

    b2 = btInsertInternal(b, key, &median);

    if(b2) {
        

        b1 = malloc(sizeof(*b1));
        assert(b1);

       
        memmove(b1, b, sizeof(*b));

      
        b->numKeys = 1;
        b->isLeaf = 0;
        b->keys[0] = median;
        b->kids[0] = b1;
        b->kids[1] = b2;
    }
}
