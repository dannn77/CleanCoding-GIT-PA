/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa 

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} STK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node -> data = v;
    new_node -> next = NULL;
    return new_node;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);

    new_node -> next = graph -> adjacency_lists[src];
    graph -> adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node -> next = graph -> adjacency_lists[dest];
    graph -> adjacency_lists[dest] = new_node;  
}

GPH *create_graph(int vertices)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph -> vertices = vertices;
    graph -> adjacency_lists = malloc((vertices + 1) * sizeof(NODE *));
    graph -> visited = malloc((vertices + 1) * sizeof(int));

    for (int i = 1; i <= vertices; i++)
    {
        graph -> adjacency_lists[i]=NULL;
        graph -> visited[i] = 0;
    }  
    return graph;
}

STK *create_stack(int capacity)
{
    STK *stack = malloc(sizeof(STK));
    stack -> array = malloc(capacity * sizeof(int));
    stack -> top = -1;
    stack -> capacity = capacity;

    return stack;
}

void push(int element, STK *stack)
{
    stack -> top ++;
    stack -> array[stack -> top] = element;
}

void DFS(GPH *graph, STK *stack, int vertex_nr)
{
    NODE *adj_list = graph -> adjacency_lists[vertex_nr];
    NODE *aux = adj_list;

    graph -> visited[vertex_nr] = 1;
    push(vertex_nr, stack);
    
    while (aux != NULL)
    {
        int connected_vertex = aux -> data;
        if (graph -> visited[connected_vertex] == 0)
        {
            DFS(graph, stack, connected_vertex);
        }
        aux = aux -> next;
    } 
}


void insert_edges(GPH *graph, int nr_of_edges, int nr_of_vertices)
{
    int src, dest, i;

    printf("adauga %d munchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GPH *graph, int nr_of_vertices)
{
    for (int i = 1; i <= nr_of_vertices; i++)
    {
        graph -> visited[i] = 0;
    }
}

int can_be_path(GPH *graph, int nr_of_vertices, STK *stack1, STK *stack2, int vertex_1, int vertex_2)
{
    int can_be_path = 0;
    DFS(graph, stack1, vertex_1);
    wipe(graph, nr_of_vertices);
    DFS(graph, stack2, vertex_2);

    for(int i = 1; i <= nr_of_vertices && !can_be_path; i++)
    {
        if(stack1 -> array[i] == vertex_2)
        {
            for(int j = 1; j <= nr_of_vertices && !can_be_path; j++)
            {
                if(stack2 -> array[j] == vertex_1)
                {
                    can_be_path = 1;
                }
            }
        }
    }
    if(can_be_path)
        return 1;
    return 0;
}

int main()
{
    int nr_of_vertices;
    int nr_of_edges;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("cate noduri are girafa?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are giraful?");
    scanf("%d", &nr_of_edges);

    printf("care sunt cele 2 restaurante?");
    scanf("%d %d", &vertex_1, &vertex_2);

    GPH *graph = create_graph(nr_of_vertices);

    STK *stack1 = create_stack(2 * nr_of_vertices);
    STK *stack2 = create_stack(2 * nr_of_vertices);

    insert_edges(graph, nr_of_edges, nr_of_vertices);

    if(can_be_path(graph, nr_of_vertices, stack1, stack2, vertex_1, vertex_2))
        printf("exista drum intre %d si %d\n", vertex_1, vertex_2);
    else
        printf("nu exista drum intre %d si %d\n", vertex_1, vertex_2);

    return 0;
}
