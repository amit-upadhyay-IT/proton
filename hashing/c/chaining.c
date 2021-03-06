#include<stdio.h>
#include<stdlib.h>

struct LinkedListNode
{
    int data;
    struct LinkedListNode *next;
};

struct LinkedListNode* getNewNode()
{
    // I don't need to cast the malloc in c
    return malloc(sizeof(struct LinkedListNode));
}

struct LinkedListNode* insertAtBeginning(struct LinkedListNode** hashTable, int index, int data)
{
    struct LinkedListNode* newNode = getNewNode(); // the new node
    newNode->data = data;
    newNode->next = NULL; // for now I can put the next to be null

    // check if the block is containing null or not
    if (hashTable[index] == NULL)
    {
        // now just insert the new element at beginning
        hashTable[index] = newNode;
        return hashTable[index]; // returning the new address of the block
    }

    // if collisions occur
    struct LinkedListNode* blockListAddress = hashTable[index]; // the address pointing to first node of linked list
    newNode->next = blockListAddress; // storing the address of block in the next of the new linkedlist
    hashTable[index] = newNode; // changing the block address to the address of new node (as we have to insert in beginning)
    return hashTable[index];
}

struct LinkedListNode* searchMe(struct LinkedListNode** hashTable, int index, int key)
{
    struct LinkedListNode* res = NULL;
    struct LinkedListNode* temp = hashTable[index];

    if (temp == NULL)
        return NULL;

    // if we just have one element in the block then the while loop below won't get executed
    // because here condition is temp->next which will be null, thus here I have written if condition
    if (hashTable[index] != NULL && hashTable[index]->data == key)
    {
        return hashTable[index];
    }

    // if not null then traverse through linked list
    while (temp != NULL)
    {
        if (key == temp->data)
            res = temp;
        temp = temp->next;
    }
    return res;
}

int hashFunction(int num)
{
    return num%10;
}

int main()
{
    int n;
    printf("\nEnter elements to be stored\n");
    scanf("%d", &n);

    // declaring the hashTable of size n (i.e. size of input elements), its gonna have pointers to LinkedListNode
    struct LinkedListNode** hashTable = malloc(10*sizeof(struct LinkedListNode*)); // I have given memory to the table, now I even need to give memory to the elements in the table
    int i;
    for (i = 0; i < 10; ++i)
    {
        hashTable[i] = NULL;
    }

    int d;
    printf("\nEnter the elements in array\n");
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &d);
        int hashedValue = hashFunction(d);
        hashTable[hashedValue] = insertAtBeginning(hashTable, hashedValue, d);
    }

    int key;
    printf("\nEnter the element you want to search for\n");
    scanf("%d", &key);
    int ind = hashFunction(key);
    struct LinkedListNode* res = searchMe(hashTable, ind, key);

    if (res == NULL)
    {
        printf("\nNot found\n");
    }
    else
    {
        printf("\n%d is found\n", res->data);
    }
}


// time complexity in worst case for searching = O(n),
// average case t.c = O(1+alpha), where alpha = n/m
// n <- number of elements in hashtable
// m <- size of hashtable
// so alpha is 1 in this case
// thus average t.c = theta(1)
