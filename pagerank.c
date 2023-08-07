// Written by: Prithvi Sajit
// Date: 11/11/2021

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagerank.h"

#define MAX_SIZE 100

int main(int argc, char *argv[]) {
    // Create struct to store urls, and insert into a graph
    Url url = store_urls();
    Graph g = new_graph(url->num_urls);
    for (int i = 0; i < url->num_urls; i++) {
        get_links(url->urls[i], url, g);
    }

    // Convert to strings to appropriate types and find pagerank
    g->pagerank = calloc(g->nV, sizeof(double));
    page_rank(g, atof(argv[1]), atof(argv[2]), atoi(argv[3]));

    // Create array which counts outlinks of each url in order to make sorting 
    // easier
    int *outLinks = calloc(g->nV, sizeof(int));
    for (int i = 0; i < g->nV; i++) {
        outLinks[i] = num_outlinks(g, i);
    }

    // Sort the pagerank and print
    sort_array(g, url, outLinks);
    for (int i = 0; i < g->nV; i++) {
        printf("%s, %d, %.7lf\n", url->urls[i], outLinks[i], g->pagerank[i]);
    }

    // Free memory
    free(outLinks);
    free_url_info(url);
    free(g->pagerank);
    free_graph(g);
    return 1;
}

//
// Url functions
//

int num_urls() {
    FILE *fptr = fopen("collection.txt", "r");

    char site[MAX_SIZE];
    int count = 0;
    while(fscanf(fptr, "%s", site) != EOF) {
        count++;
    }
    fclose(fptr);
    return count;
}

Url store_urls() {
    int count = num_urls();
    FILE *fptr = fopen("collection.txt", "r");
    char site[MAX_SIZE];

    Url url_Info = malloc(sizeof(*url_Info));
    url_Info->num_urls = count; 
    url_Info->urls = malloc(sizeof(char *) * count);

    int i = 0;
    while (fscanf(fptr, "%s", site) != EOF) {
        char *temp = malloc((strlen(site) + 1) * sizeof(char));
        strcpy(temp, site);
        url_Info->urls[i] = temp;
        i++;
    }   

    fclose(fptr);
    return url_Info;
}

void free_url_info(Url url_Info) {
    int i = 0;
    while (i < url_Info->num_urls) {
        free(url_Info->urls[i]);
        i++;
    }
    free(url_Info->urls);
    free(url_Info);
}

//
// Graph functions
//

Graph new_graph(int V) {
    int i;
    Graph g = malloc(sizeof(GraphRep));
    g->nV = V;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

void insert_edge(Graph g, Edge e) {
    if (!g->edges[e.v->url_num][e.w->url_num]) {  // edge e not in graph
        g->edges[e.v->url_num][e.w->url_num] = 1;
        g->nE++;
    }
}

Vertex new_vertex(char *url, int i) {
    Vertex v = malloc(sizeof(*v));
    v->url_num = i;
    return v;
}

void free_graph(Graph g) {
    int i;
    for (i = 0; i < g->nV; i++) 
        free(g->edges[i]);
    free(g->edges);
    free(g);
}

//
// Link Functions
//

void get_links(char *url, Url url_Info, Graph g) {
    char file_name[MAX_SIZE] = "";
    strcpy(file_name, url);
    strcat(file_name, ".txt");
    FILE *fptr = fopen(file_name, "r");
    
    char temp[MAX_SIZE];
    fgets(temp, MAX_SIZE, fptr);

    int rep_src;
    for (int j = 0; j < url_Info->num_urls; j++) {
        if (strcmp(url_Info->urls[j], url) == 0) {
            rep_src = j;
            break;
        }
    }
    Vertex src = malloc(sizeof(*src));
    src->url_num = rep_src;

    while (1) {
        fscanf(fptr, "%s", temp);
        if (strcmp(temp, "#end") == 0) {
            break;
        }
        int rep_dest;
        for (int j = 0; j < url_Info->num_urls; j++) {
            if (strcmp(url_Info->urls[j], temp) == 0) {
                rep_dest = j;
                break;
            }
        }

        if (strcmp(temp, url) != 0) {
            Vertex dest = malloc(sizeof(*dest));
            dest->url_num = rep_dest;
            Edge new;
            new.v = src;
            new.w = dest;
            insert_edge(g, new);
            free(dest);
        }
    }
    free(src);
    fclose(fptr);
}

//
// Pagerank functions
//

void page_rank(Graph g, double d, double diffPR, int maxIterations) {
    for (int b = 0; b < g->nV; b++) {
        g->pagerank[b] = 1 /(double)g->nV;
    }
    int iteration = 1;
    double diff = diffPR; 
    double prev_pr[g->nV];
    // Make iteration = 1 and calc by hand
    while (iteration < maxIterations && diff >= diffPR) {
        for (int c = 0; c < g->nV; c++) {
            prev_pr[c] = g->pagerank[c];
        }
        double M;
        for (int i = 0; i < g->nV; i++) {
            // sum of PR(Pj, t) * Win(Pj, Pi) * Wout(Pj, Pi)
            M = 0.0;
            for (int j = 0; j < g->nV; j++) {
                if (g->edges[j][i] == 1) {
                    double winout = w_in_out(g, i, j);
                    M = (prev_pr[j] * winout) + M;
                }
            }  
            // PR(Pi, t + 1) = 1 - d / N + d * M
            g->pagerank[i] = (((1.0 - d) / (double)(g->nV))) + d * M;
        }
        // diff = PR - PR
        double total = 0.0;
        for (int a = 1; a < g->nV; a++) {
            total += (fabs(g->pagerank[a] - prev_pr[a]));
        }            
        diff = total;
        iteration++;
    }
}


int num_outlinks(Graph g, int url_num) {
    int i = 0;
    int count = 0;
    while (i < g->nV) {
        if (g->edges[url_num][i] == 1) {
            count++;
        }
        i++;
    }
    return count;
}

int num_inlinks(Graph g, int url_num) {
    int i = 0;
    int count = 0;
    while (i < g->nV) {
        if (g->edges[i][url_num] == 1) {
            count++;
        }
        i++;
    }
    return count;
}

double w_in_out (Graph g, int dest, int src) {
    // Calc w_In
    double total = 0.0;
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[src][i] == 1) {
            // possible error / maybe remove it
            if (num_inlinks(g, i) == 0) {
                total += 0.5;
            } 
            total += num_inlinks(g, i);
        }
    }
    double w_in = num_inlinks(g, dest) / (double)total;

    // Calc w_Out
    double total2 = 0.0;
    for (int i = 0; i < g->nV; i++) {
        if (g->edges[src][i] == 1) {
            if (num_outlinks(g, i) == 0) {
                total2 += 0.5;
            } 
            total2 += num_outlinks(g, i);
        }
    }
    if (num_outlinks(g, dest) == 0) {
        double w_out = 0.5 / (double)total2;
        return w_out * w_in;
    }
    double w_out = num_outlinks(g, dest) / (double)total2;

    // Multiply w_in and w_out and return
    return w_out * w_in;
}


void sort_array_helper_double_swap(double *xp, double *yp) {
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_array_helper_double_int(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Selection sort, I used code from:
// https://www.geeksforgeeks.org/selection-sort/
void sort_array(Graph g, Url url, int *outLinks) {
    int i, j, min_idx;
    for (i = 0; i < g->nV-1; i++) {
        min_idx = i;
        for (j = i+1; j < g->nV; j++) {
            if (g->pagerank[j] > g->pagerank[min_idx] || 
            g->pagerank[j] == g->pagerank[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        sort_array_helper_double_swap(&g->pagerank[i], &g->pagerank[min_idx]);
        char temp[MAX_SIZE] = "";
        if (strcmp(url->urls[i], url->urls[min_idx]) != 0) {
            strcpy(temp, url->urls[i]);
            strcpy(url->urls[i], url->urls[min_idx]);
            strcpy(url->urls[min_idx], temp);
        }
        sort_array_helper_double_int(&outLinks[i], &outLinks[min_idx]);
    }
}