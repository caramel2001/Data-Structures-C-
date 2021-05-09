#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}
int precedence(char s)
{
    if (s == '*' || s == '/') return 1;
    return 0;
}
void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
    char x,c;
    char postfix[80],rev[80],prefix[80];
    int temp,i,j,count=0;

    while (infix[count] != '\0'){
        count++;
    }
    j = count - 1;
    for (i = 0; i < count; i++)
    {
        rev[i] = infix[j];
        j--;
    }
    rev[i]='\0';

    j=0;
    i=0;
    Stack s;
    s.head=NULL;
    s.size=0;
    while(rev[i]!='\0')
    {
        c=rev[i++];
        switch(c)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!isEmptyStack(s) && peek(s)!=')' && precedence(peek(s))>precedence(c)){
                postfix[j++]=peek(s);
                pop(&s);

            }
            postfix[j++]=' ';
            push(&s,c);
            break;
        case ')':
            push(&s,c);           
            break;
        case '(':
            x=peek(s);
            pop(&s);
            while(x != ')')                
			{

				postfix[j]= x;
				j++;
				x = peek(s);
                pop(&s);
			}		
            break;
        
        default:
            postfix[j++]=c;    
        }          
    }
    while(!(isEmptyStack(s))){
        postfix[j++]=peek(s);
        pop(&s);
    }
    postfix[j]='\0';

    j=0;
    count=0;
    while (postfix[count] != '\0')
    {
        count++;
    }
    j = count - 1;

    for (i = 0; i < count; i++)
    {
        prefix[i] = postfix[j];
        j--;
    }
    prefix[i]='\0';
    

    i=0;
    j=10;
    temp=0; 
    while(prefix[i] != '\0')
    {
        c=prefix[i];
        switch (c)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':

                insertNode(inExpLL,c,OPT);
                i++;
                break;
            case ' ':
                i++;
                break;
            
            default:
                while(c>='0' && c<='9')
                {
                    temp*=j;
                    temp+=(c -'0');
                    i++;
                    c=prefix[i];
                    
                }
                insertNode(inExpLL,temp,OPERAND);
                temp=0;
        }
        
    }
    ListNode *prev = NULL;
    ListNode *current = inExpLL->head;
    ListNode *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    inExpLL->head=prev;

  
  
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}