// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"
#include "queue.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}
		
	// You need to modify the code below to implement:
	// add firstURL to the ToDo list
        Queue ToDoList = newQueue();
        enterQueue(ToDoList, firstURL);
        showQueue(ToDoList);                                          //firstURL PTR?
	// initialise Graph to hold up to maxURLs
        Graph graph = newGraph(maxURLs);
        showGraph(graph,0);
	// initialise set of Seen URLs
        Set seenSet = newSet();
	// while (ToDo list not empty and Graph not filled) {
        while(!emptyQueue(ToDoList) && nVertices(graph) < maxURLs) {
	//    grab Next URL from ToDo list
            char *next = leaveQueue(ToDoList);
            insertInto(seenSet,next);
            printf("\n");
            printf("We're looking at %s\n",next);
	//    if (not allowed) continue
            if(!(handle = url_fopen(next,"r"))) continue;
	//    foreach line in the opened URL {
                 handle = url_fopen(next,"r");
                 while(!url_feof(handle)){
                     url_fgets(buffer,sizeof(buffer),handle);
                     int pos = 0;
                     char result[BUFSIZE];
                     memset(result,0,BUFSIZE);
                     while((pos = GetNextURL(buffer,next,result,pos))> 0){
                        printf("It includes %s\n",result);
                      
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
                        if(nVertices(graph) < maxURLs || isConnected(graph,next,result) == 0) {   
	//             add an edge from Next to this URL
                           addEdge(graph,next,result);
                        }
	//          if (this URL not Seen already) {
                        if(!isElem(seenSet,result)){
	//             add it to the Seen set
                           insertInto(seenSet,result);
	//             add it to the ToDo list
                           enterQueue(ToDoList, result);
                        }
	             } 
	       }
    //    }
               url_fclose(handle); 
        }
	//    close the opened URL
        sleep(1);
        showGraph(graph,0);
        showGraph(graph,1);
	// }
	if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		//fputs(buffer,stdout);
		int pos = 0;
		char result[BUFSIZE];
		memset(result,0,BUFSIZE);
		while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
			printf("Found: '%s'\n",result);
			memset(result,0,BUFSIZE);
		}
	}
	url_fclose(handle);
	sleep(1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}
