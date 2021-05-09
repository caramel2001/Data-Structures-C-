#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;


void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g);
int DFS(Graph g, int v,int u,int ar[]);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    //thsi si the porperty of pratham agarwala....please dont copy
    int Prj, Std, Mtr; //Project, Student and Mentor;
    int maxMatch;
    int i,j;
    int a,b,c;
    ListNode *temp;
    //printf("Give inputs \n");

    scanf("%d %d %d", &Std, &Prj, &Mtr);
	
    //build graph
	Graph g;
    g.V=Prj+2*Std+Mtr+2;
    g.list = (ListNode **)malloc(g.V*sizeof(ListNode *));
    //clearing the arrraylist to compute the list properly
    for(i=0;i<g.V;i++)
        g.list[i] = NULL;
    for(i=0;i<Std;i++){
        scanf("%d %d",&a,&b);
        insertAdjVertex(&g.list[i],Std+i+1);
        g.E++;

        for (j=0;j<a;j++){
            scanf("%d",&c);
            insertAdjVertex(&g.list[2*Std+c-1],i+1);
            g.E++;
        }
        for (j=0;j<b;j++){
            scanf("%d",&c);
            insertAdjVertex(&g.list[Std+i],2*Std+Prj+c);
            g.E++;
        }

    }
    for(j=0;j<Prj;j++){
        insertAdjVertex(&g.list[2*Std+Prj+Mtr],2*Std+j+1);
        g.E++;
    }
    for(j=0;j<Mtr;j++){
        insertAdjVertex(&g.list[2*Std+Prj+j],2*Std+Prj+Mtr+2);
        g.E++;
    }
    // ListNode* temp1;
	// for(i=0;i<g.V;i++)
    // {
    //     printf("%d: ",i+1);
    //     temp1 = g.list[i];
    //     while(temp1!=NULL){
    //         printf("%d -> ",temp1->vertex);
    //         temp1 = temp1->next;
    //     }
    //     printf("\n");
    // }
    //apply Ford Fulkerson algorithm
    // use DFS or BFS to find a path
    // printf("%d \n",g.E);
	maxMatch = matching(g);
	// for(i=0;i<g.V;i++)
    // {
    //     printf("%d: ",i+1);
    //     temp1 = g.list[i];
    //     while(temp1!=NULL){
    //         printf("%d -> ",temp1->vertex);
    //         temp1 = temp1->next;
    //     }
    //     printf("\n");
    // }
    
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph g)
{   
    int ar[50];
    int i=0,temp1,temp2,j=0;
    ListNode *x;
    for (i=0;i<50;i++){
        ar[i]=0;
    }
    //printf("entered matching \n");
    while(DFS(g,(g.V-1),g.V,ar)==1){
        //printf("Path found \n");
        j=0;
        while(ar[j+1]!=-1){
            temp1=ar[j];
            temp2=ar[j+1];
            insertAdjVertex(&g.list[temp1-1],temp2);
            removeAdjVertex(&g.list[temp2-1],temp1);
            j++;
        }
        for (i=0;i<50;i++){
            ar[i]=0;
        }
    }
    i=0;
    x=g.list[g.V-1];
    while(x!=NULL){
        i++;
        x=x->next;
    }
    return i;

}

int DFS(Graph g, int v,int u,int ar[])
{
    //printf("Enetred DFS \n");
    Stack s;s.size=0;s.head=NULL;
    ListNode *x;
    int i,w,j=0;
    int *visited;
    visited=malloc(sizeof(int)*g.V);
    for (i=0;i<g.V;i++){ visited[i]=0;}
    
    push(&s,v);
    visited[v-1]=1;
    int unvisited;
    while(isEmptyStack(s)==0){
        w=peek(s);
        //printf("%d \n",w);
        unvisited=0;
        x=g.list[w-1];
        while(x != NULL){
            if(visited[x->vertex-1]==0){
                push(&s,x->vertex);
                visited[x->vertex-1]=1;
                unvisited=1;
                break;
            }
            x=x->next;
        }
        if (unvisited==0){
            if (w!=u){
                pop(&s);
            }
            else{
                while(isEmptyStack(s)==0){
                    w=peek(s);
                    //printf("%d \n",w);
                    ar[j]=w;
                    j++;
                    pop(&s);
                }
                ar[j]=-1;
                //printf("vertex found \n");
                
                return 1;
            }
            
        }
    }
    return 0;
    
}

//////////////////////////////////////////////////////
void removeAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp, *preTemp;
    if(*AdjList != NULL)
    {
        if((*AdjList)->vertex ==vertex){//first node
            temp = *AdjList;
            *AdjList = (*AdjList)->next;
            free(temp);
            return;
        }
        preTemp = *AdjList;
        temp = (*AdjList)->next;
        while(temp!=NULL && temp->vertex != vertex)
        {
            preTemp= temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }

}
void insertAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp;
    if(*AdjList==NULL)
    {
        *AdjList = (ListNode *)malloc(sizeof(ListNode));
        (*AdjList)->vertex = vertex;
        (*AdjList)->next = NULL;
    }
    else{
        temp = (ListNode *)malloc(sizeof(ListNode));
        temp->vertex = vertex;
        temp->next = *AdjList;
        *AdjList = temp;
    }
}
void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
    if(cur==NULL) printf("Empty");

    while (cur != NULL){
        printf("%d ", cur->vertex);
        cur = cur->next;
    }
    printf("\n");
}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
