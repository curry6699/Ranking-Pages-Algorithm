// Url structs
typedef struct url *Url;
struct url {
    char **urls; // Stores urls
    int num_urls; 
};

// Graph structs
typedef struct GraphRep *Graph;
typedef struct VertexRep *Vertex;
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;
typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
   double *pagerank;
} GraphRep;

// Vertex struct
typedef struct VertexRep {
    int url_num;
    // char *url_name;
} VertexRep;

// Url functions
/**
 * Return the number of urls for the given file
 */
int num_urls();

/**
 * Return a struct which stores the urls
 */
Url store_urls();

/**
 * Free the memory associated with the struct containing urls
 */
void free_url_info(Url url_Info);

// From 2521 T3 Lecture Code
// Graph and Vertex Functions
/**
 * Creates a new graph
 */
Graph new_graph(int);

/**
 * Inserts an edge into a graph
 */
void  insert_edge(Graph, Edge);

/**
 * Free memory associated with graph
 */
void  free_graph(Graph);

/**
 * Create and return a new vertex
 */
Vertex new_vertex(char *url, int i);

// Link functions
/**
 * Get the urls and number of urls of the given file
 */
void get_links(char *url, Url url_Info, Graph g);

/**
 * Return the number of inlinks for a specific url
 */
int num_inlinks(Graph g, int url_num);

/**
 * Return the number of outlinks for a specific url
 */
int num_outlinks(Graph g, int url_num);

/**
 * Return W_in x W_out
 */
double w_in_out(Graph g, int dest, int src);

// Pagerank functions
/**
 * Calculate the pagerank of the given urls
 */
void page_rank(Graph g, double d, double diffPR, int maxIterations);

/**
 * Helper function for sortArray that swaps the given doubles
 */
void sort_array_helper_double_swap(double *xp, double *yp);

/**
 * Helper function for sortArray that swaps the given ints
 */
void sort_array_helper_double_int(int *xp, int *yp);

/**
 * Sort the given array of pageranks
 */
void sort_array(Graph g, Url url, int *outLinks);