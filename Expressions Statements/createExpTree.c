#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
    BTNode *t, *l, *r;
    Stack s;
    s.size=0;
    s.head=NULL;
    int i=0,j=10,temp=0,count=0;
    char c,revfix[SIZE];


    while (prefix[count] != '\0'){
        count++;
    }
    j = count - 1;
    for (i = 0; i < count; i++)
    {
        revfix[i] = prefix[j];
        j--;
    }
    revfix[i]='\0';
        

    j=1;
    for (int i=0; i<count; i++)
    {
        if (revfix[i]>='0' && revfix[i]<='9') 
        {
            while(revfix[i]>='0' && revfix[i]<='9')
            {
                
                temp += j*(revfix[i]-'0');         
                i++;
                j*=10;
            }
            t=malloc(sizeof(BTNode));        
            t->item = temp;
            t->left=NULL;
            t->right=NULL;
            push(&s, t);
            temp=0;
            j=1;
        }
        else if (revfix[i]==' ' || revfix[i]=='(' || revfix[i]==')'){
            continue;
        }
        else 
        {
            t=malloc(sizeof(BTNode));        
            t->item = revfix[i];
        
            l = peek(s); 
            pop(&s);      
            
            r = peek(s);
            pop(&s);
 
            t->left = l;
            t->right = r;
 
            push(&s, t);
        }
    } 
    t = peek(s);
    pop(&s);
    (*root) = t;   
}

void printTree(BTNode *node){
    //Write your code here
    if (node==NULL){
        return;
    }
    

    printTree(node->left);
    if(node->left==NULL && node->right==NULL){
        printf("%d",node->item);
    }
    else{
        printf(" %c ",node->item);
    }
    printTree(node->right);
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if (node==NULL){
        return;
    }
    printTreePostfix(node->left);
    printTreePostfix(node->right);

    if(node->left==NULL && node->right==NULL){
        printf("%d",node->item);
        printf(" ");
    }
    else
    {
        printf("%c",node->item);
        printf(" ");
    }
}

double computeTree(BTNode *node){
//Write your code here
    double l,r;
    if (node==NULL){
        return 0;
    }
    if (node->left==NULL && node->right==NULL){
        return node->item;
    }
    l=computeTree(node->left);
    r=computeTree(node->right);
    if (node->item=='+'){
        return l+r;
    }
    if (node->item=='-'){
        return l-r;
    }
    if (node->item=='*'){
        return l*r;
    }
    if (node->item=='/'){
        return l/r;
    }
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}