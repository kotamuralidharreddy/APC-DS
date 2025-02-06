#ifndef APC_H  
#define APC_H  

#define SUCCESS 0  // Define a constant for successful operations
#define FAILURE -1  // Define a constant for failed operations

typedef int data_t;  // Define data_t as an alias for int

// Define a structure for a doubly linked list node
typedef struct node
{
	struct node *prev;  // Pointer to the previous node
	data_t data;  // Data stored in the node
	struct node *next;  // Pointer to the next node
} Dlist;  // Alias for the node structure

/* Include the prototypes here */  // Placeholder for function prototypes

// Function to insert arguments into two doubly linked lists
int insert_args(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char* argv1, char* argv2);

// Function to insert data at the end of a doubly linked list
int insert_at_last(Dlist **head1, Dlist **tail1, char *data);

// Function to perform addition on two doubly linked lists
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Function to add a result to the result list
int add_res(Dlist **headR, Dlist **tailR, int sum);

// Function to free all nodes in the doubly linked lists
int free_all(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Function to free a single node
void free_node(Dlist **head, Dlist **tail);

// Function to find the larger of two doubly linked lists
int find_larger(Dlist **head1, Dlist **head2);

// Function to perform subtraction on two doubly linked lists
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Function to print the contents of a doubly linked list
void print_list(Dlist **head, Dlist **tail);

// Function to find the length of a string argument
int find_len(char* argv);

// Function to perform division on two doubly linked lists
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Function to check if two nodes are equal
int check_node(Dlist **head1, Dlist **head2);

// Function to perform multiplication on two doubly linked lists
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Function to insert a node at the end of a doubly linked list
void insert_last(Dlist **head, Dlist **tail);

// Function to insert a node at the beginning of a doubly linked list
void insert_first(Dlist **head, Dlist **tail, int data);

// Function to free the first node of a doubly linked list
void free_first(Dlist **head);

#endif  // End of header guard
