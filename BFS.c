/*
    Bu kod .txt filesindan komsuluk listesini okur ve BFS algoritmasi ile tum dugumleri gezer. Gezme sirasi ekrana yazdirilir.
    Not: Olusturulan komsuluk listesi yapisini anlamak icin ekte bulunan resme bakiniz.
    Not: Resimde tum dugumler sigmamistir.
*/
/*
    This code reads the adjacency list from a .txt file and travers all the nodes in it with BFS algorithm.
    Note: Take a look at to added picture to understand better the adjacency list structure which is made of singly linked list.
    Note: All of the nodes didn't fit to picture.
*/

#include <stdio.h>
#include <stdlib.h>

struct node{
    char nodeName; //Node name
    struct node *nextNode; //It points to the next adjacent node
    int mainNode; //In the adjacency list, if a node is; one of the main nodes -> 1, one of the main node's adjacent nodes -> 0 
    struct node *nextMainNode; //It points to the next main node
    int isVisited; //If it's a main node, not visited -> 0, visited -> 1; if it's not, not related -> -1
};

FILE *file;
struct node *firstNode=NULL; //First node of the adjacency list
struct node *nodeIter=NULL; //The node which travel between the adjacency nodes
struct node *mainNodeIter=NULL; //The node which travel between the main nodes
int control=0; //If no main node added before -> 0, if it's added ->1 
int mainNodeNumber=0; //It counts the main node number

void BuildingAdjacencyList(){ //Read the characters in the .txt file and add them to singly linked list
    char readCharacter=fgetc(file);
    char previousCharacter='\n';  // If this variable doesn't start with '\n', algorithm can't make the first node to a main node
    while(!feof(file)){ //Until to read all the characters in the file
        if(readCharacter!='\n'&&readCharacter!=' '&&previousCharacter=='\n'){ //Main Nodes
            if(control==0){ //First Main Node
                nodeIter->mainNode=1; 
                nodeIter->nodeName=readCharacter; 
                mainNodeIter=nodeIter;
                firstNode=mainNodeIter;
                control=1;
                mainNodeNumber++;
            }
            else{ 
                mainNodeIter->nextMainNode=(struct node*)malloc(sizeof(struct node)); //Other Main Nodes
                nodeIter=mainNodeIter->nextMainNode; 
                nodeIter->mainNode=1;
                nodeIter->nodeName=readCharacter;
                mainNodeIter=nodeIter;
                mainNodeNumber++;
            }
            mainNodeIter->nextMainNode=NULL;
        }
        else if(readCharacter!='\n'&&readCharacter!=' '&&previousCharacter!='\n'){ //Adjacent Nodes
            nodeIter->nextNode=(struct node*)malloc(sizeof(struct node));  
            nodeIter=nodeIter->nextNode;
            nodeIter->nodeName=readCharacter;
            nodeIter->mainNode=0; 
            nodeIter->nextNode=NULL;
        } 
        previousCharacter=readCharacter;
        readCharacter=fgetc(file);
    }
}

void PrintingAdjacencyList(){ //Print the structure
    mainNodeIter=firstNode;
    nodeIter=mainNodeIter;
    while(mainNodeIter!=NULL){ //Do it until the all rows are travelled.
        while(nodeIter!=NULL){  //Travel between adjacent nodes in the first main node's row, when the row is complete, go to the next main node's row.
            if(nodeIter->mainNode==1){ //Main node...
                printf("%c->", nodeIter->nodeName);
            }
            else{ //Adjacent node...
                printf("%c-", nodeIter->nodeName);
            }
            nodeIter=nodeIter->nextNode; 
        }
        printf("NULL\n");
        mainNodeIter=mainNodeIter->nextMainNode;
        nodeIter=mainNodeIter;
    }
}

void FindTheNodeFromTheAdjacencyList(char wantedCharacter){ //Makes visited node's isVisited -> 1
    mainNodeIter=firstNode;
    while(mainNodeIter!=NULL){ 
        if(mainNodeIter->nodeName==wantedCharacter){
            mainNodeIter->isVisited=1;
            break;
        }
        mainNodeIter=mainNodeIter->nextMainNode;
    }
}

struct queue{
    char nodeName; //Node name
    struct queue *nextNode; //It points to next node in the queue which is made of singly linked list.
};

struct queue *queueFirstNode=NULL; //It points to first node in the queue.
struct queue *queueNodeIter=NULL; //It traversals nodes in the queue.

char *traversalOrder=NULL; //It keeps record of the nodes' traversal order.

void PrintQueue(){ //Printing the queue.
    struct queue *temp=(struct queue*)malloc(sizeof(struct queue));
    temp=queueFirstNode;
    printf("Queue: ");
    if(temp==NULL) printf("-");
    while(temp!=NULL){
        printf("%c ", temp->nodeName);
        temp=temp->nextNode;
    }
    printf("\n");
}

struct node *dugumBul(char wantedCharacter){ //It finds the first node of the queue in the adjacency list
    mainNodeIter=firstNode;
    while(mainNodeIter!=NULL){ 
        if(mainNodeIter->nodeName==wantedCharacter){
            break;
        }
        mainNodeIter=mainNodeIter->nextMainNode;
    }
    return (mainNodeIter);
}

int CheckIfVisited(char wantedCharacter){ //It checks the node is visited or not.
    mainNodeIter=firstNode;
    while(mainNodeIter!=NULL){ 
        if(mainNodeIter->nodeName==wantedCharacter){
            if(mainNodeIter->isVisited==1){
                printf("%c is added before. It can't be added to the queue again!\n", wantedCharacter);
                return 0;
            }
            else{
                printf("%c isn't added before.\n", wantedCharacter);
                return 1;
            }
        }
        mainNodeIter=mainNodeIter->nextMainNode;
    }
}

void AddToQueue(char name){ //It adds a node to the queue.
    if(CheckIfVisited(name)==1){
        if(queueFirstNode==NULL){
            queueFirstNode=(struct queue*)malloc(sizeof(struct queue));
            queueFirstNode->nodeName=name;
            queueFirstNode->nextNode=NULL;
            queueNodeIter=(struct queue*)malloc(sizeof(struct queue));
            queueNodeIter=queueFirstNode;
        }
        else{
            while(queueNodeIter->nextNode!=NULL){
                queueNodeIter=queueNodeIter->nextNode;
            }
            queueNodeIter->nextNode=(struct queue*)malloc(sizeof(struct queue));
            queueNodeIter=queueNodeIter->nextNode;
            queueNodeIter->nodeName=name;
            queueNodeIter->nextNode=NULL;
        }
        FindTheNodeFromTheAdjacencyList(queueNodeIter->nodeName);
        printf("%c is added to the queue.\n", queueNodeIter->nodeName);
    }
}

void DeleteFromQueue(){ //It deletes the first node in the queue.
    if(queueFirstNode->nextNode==NULL){
        printf("%c is deleted from the queue.\n", queueFirstNode->nodeName);
        queueFirstNode=NULL;
    }
    else{
        struct queue *temp=(struct queue*)malloc(sizeof(struct queue));
        temp=queueFirstNode;
        queueFirstNode=queueFirstNode->nextNode;
        printf("%c is deleted from the queue.\n", temp->nodeName);
        free(temp);
    }
}

int c=0; //If first node and it's adjacencies isn't added to the queue -> 0, if added -> 1
int a=0; //It helps to keep the index number of traversalOrder

void BFS(){ //Recursive BFS Algorithm
    if(c==0){
        nodeIter=firstNode;
        AddToQueue(nodeIter->nodeName);
        PrintQueue();
        traversalOrder[a++]=queueFirstNode->nodeName;
        DeleteFromQueue();
        PrintQueue();
        nodeIter=nodeIter->nextNode;
        while(nodeIter!=NULL){
            AddToQueue(nodeIter->nodeName);
            PrintQueue();
            nodeIter=nodeIter->nextNode;
        }
        c=1;
    }
    else{
        nodeIter=dugumBul(queueFirstNode->nodeName);
        traversalOrder[a++]=queueFirstNode->nodeName;
        DeleteFromQueue();
        PrintQueue();
        nodeIter=nodeIter->nextNode;
        while(nodeIter!=NULL){
            AddToQueue(nodeIter->nodeName);
            PrintQueue();
            nodeIter=nodeIter->nextNode;
        }
    }
    printf("\n***********************\n\n");
    if(queueFirstNode!=NULL){ //Recursive...
        BFS();
    }
}

int main(){
    file=fopen("adjacency_list.txt", "r"); //File is opening for reading.
    if(file==NULL){
        printf("\nFile is Empty!");
        return 0;
    }
    else{
        printf("\nAdjacency List:\n");
        firstNode=(struct node*)malloc(sizeof(struct node));
        nodeIter=(struct node*)malloc(sizeof(struct node));
        mainNodeIter=(struct node*)malloc(sizeof(struct node));
        nodeIter=firstNode;
        mainNodeIter=firstNode;
        BuildingAdjacencyList();
        PrintingAdjacencyList();
    }   
    fclose(file); //File is closed.
    nodeIter=firstNode;
    printf("\n***********************\n\n");
    traversalOrder=(char*)malloc(mainNodeNumber*sizeof(char)); //It needs a specific byte memory, and it is equal to main node number.
    BFS();
    free(mainNodeIter);
    free(nodeIter);
    free(firstNode);
    free(queueFirstNode);
    free(queueNodeIter);
    printf("Traversal Order With The BFS Algorithm: ");
    for(int i=0 ; i<mainNodeNumber ; i++){ 
        printf("%c ", traversalOrder[i]);
    }
    printf("\n\n");
    return 0;
}
