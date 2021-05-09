#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

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

void in2Pre(char*, char*);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

    return 0;
}

int precedence(char s)
{
    if (s == '*' || s == '/') return 1;
    return 0;
}

void in2Pre(char* infix, char* prefix)
{
    char x,c;
    char postfix[80],rev[80];
    int temp,i,j, count=0;

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
    printf("%s \n",rev);


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

				postfix[j++]= x;
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
    



 // Write your code here
    

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
