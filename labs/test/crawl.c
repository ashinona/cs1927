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
	char *curr; // this replaces char next[BUFSIZE]
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

   if (!(handle = url_fopen(firstURL, "r"))) {
      fprintf(stderr,"Couldn't open %s\n", next);
      exit(1);
   }
   Stack ToDo = newStack();  //initialise toDo stack
   pushOnto(ToDo, firstURL); // add firstURL to the ToDo list
   Graph g = newGraph(maxURLs); // initialise Graph to hold up to maxURLs
	Set Seen = newSet();   // initialise set of Seen URLs
	insertInto(Seen, firstURL); //add firstURL to Seen

	while (!emptyStack(ToDo) && maxURLs > 0) {
      curr = popFrom(ToDo);   //    grab Next URL from ToDo list
      //addEdge(curr); //add first popped off to the graph.
      handle = url_fopen(curr, "r");// update handle next URL that has been removed from ToDo stack

      if (strstr(curr, "unsw") == NULL) continue; // if (not allowed) continue

      while(!url_feof(handle)) {
      	url_fgets(buffer,sizeof(buffer),handle);
      	//fputs(buffer,stdout);
      	int pos = 0;
      	char result[BUFSIZE];
      	memset(result,0,BUFSIZE);
      	while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
      	   printf("Found: '%s'\n",result);
      	   // ADD stuff here!
      		if (nVertices(g) < maxURLs || !isConnected(g, curr, result)) { // if (Graph not filled or both URLs in Graph)
      			addEdge(g, curr, result); // add an edge from Next to this URL
      		}

      		if (!(isElem(Seen, result))){
      			// add into ToDo stack
      			pushOnto(ToDo, result);
      			// add into Seen set
      			insertInto(Seen, result);
      		}
      		memset(result,0,BUFSIZE); //clear result array by resetting elements to 0, makes sure that the next URL is inserted properly
         }
      }
      url_fclose(handle);
      sleep(1);
	   maxURLs--;
	}

	showGraph(g, 0);
	disposeStack(ToDo);
	disposeSet(Seen);
	disposeGraph(g);
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
