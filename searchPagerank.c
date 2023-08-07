#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // Url structs
// typedef struct url *Url;
// struct url {
//     char **urls; // Stores urls
//     int num_urls; 
// };

// // Graph structs
// typedef struct GraphRep *Graph;
// typedef struct VertexRep *Vertex;
// typedef struct Edge {
//    Vertex v;
//    Vertex w;
// } Edge;
// typedef struct GraphRep {
//    int  **edges;   // adjacency matrix
//    int    nV;      // #vertices
//    int    nE;      // #edges
//    double *pagerank;
// } GraphRep;

// // Vertex struct
// typedef struct VertexRep {
//     int url_num;
//     // char *url_name;
// } VertexRep;

// int count_word_in_url(char *site, char *word, Url url);

int main(int argc, char *argv[]) {
    // // Create struct to store urls, and insert into a graph
    // Url url = store_urls();
    // Graph g = new_graph(url->num_urls);
    // for (int i = 0; i < url->num_urls; i++) {
    //     get_links(url->urls[i], url, g);
    // }
    // FILE *fptr = fopen("invertedIndex.txt", r);
    // char site[MAX_SIZE];
    // char word[MAX_SIZE] = "";
    // strcpy(word, argv[1]);
    // while (fscanf(fptr, "%s", site) != EOF) {
    //     if (strcmp(site, word) == 0) {
    //         fscanf(fptr, "%s", site);
    //         int count = count_word_in_url(site, word, url);
    //         // Store count for each url
    //     }
    //     break;
    // }
    // print the urls

}

// int count_word_in_url(char *site, char *word, Url url_Info) {
//     char file_name[100] = "";
//     strcpy(file_name, site);
//     strcat(file_name, ".txt");
//     FILE *fptr = fopen(file_name, "r");
    
//     int count = 0;
//     char temp[100] = "";
//     while (fscanf(fptr, "%s", temp) != EOF) {
//         if (strcmp(temp, word) == 0) {
//             count++;
//         }
//     }
//     return count;
// }






//
// Url functions
//

// int num_urls() {
//     FILE *fptr = fopen("collection.txt", "r");

//     char site[MAX_SIZE];
//     int count = 0;
//     while(fscanf(fptr, "%s", site) != EOF) {
//         count++;
//     }
//     fclose(fptr);
//     return count;
// }

// Url store_urls() {
//     int count = num_urls();
//     FILE *fptr = fopen("collection.txt", "r");
//     char site[MAX_SIZE];

//     Url url_Info = malloc(sizeof(*url_Info));
//     url_Info->num_urls = count; 
//     url_Info->urls = malloc(sizeof(char *) * count);

//     int i = 0;
//     while (fscanf(fptr, "%s", site) != EOF) {
//         char *temp = malloc((strlen(site) + 1) * sizeof(char));
//         strcpy(temp, site);
//         url_Info->urls[i] = temp;
//         i++;
//     }

//     fclose(fptr);
//     return url_Info;
// }

// void free_url_info(Url url_Info) {
//     int i = 0;
//     while (i < url_Info->num_urls) {
//         free(url_Info->urls[i]);
//         i++;
//     }
//     free(url_Info->urls);
//     free(url_Info);
// }

// //
// // Graph functions
// //

// Graph new_graph(int V) {
//     int i;
//     Graph g = malloc(sizeof(GraphRep));
//     g->nV = V;
//     g->nE = 0;

//     // allocate memory for each row
//     g->edges = malloc(V * sizeof(int *));
//     assert(g->edges != NULL);
//     // allocate memory for each column and initialise with 0
//     for (i = 0; i < V; i++) {
//         g->edges[i] = calloc(V, sizeof(int));
//         assert(g->edges[i] != NULL);
//     }

//     return g;
// }

// void insert_edge(Graph g, Edge e) {
//     if (!g->edges[e.v->url_num][e.w->url_num]) {  // edge e not in graph
//         g->edges[e.v->url_num][e.w->url_num] = 1;
//         g->nE++;
//     }
// }

// Vertex new_vertex(char *url, int i) {
//     Vertex v = malloc(sizeof(*v));
//     v->url_num = i;
//     return v;
// }

// void free_graph(Graph g) {
//     int i;
//     for (i = 0; i < g->nV; i++) 
//         free(g->edges[i]);
//     free(g->edges);
//     free(g);
// }