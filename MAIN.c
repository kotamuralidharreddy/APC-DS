/*
NAME : KOTA MURALIDHAR REDDY



DISCRIPTION:  Arbitrary-precision arithmetic, also called big-num arithmetic, multiple precision arithmetic, or sometimes infinite-precision 
arithmetic, indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system.
This contrasts with the faster fixed-precision arithmetic found in most arithmetic logic unit (ALU) hardware, which typically offers between 8 and 64 bits of precision.
Data Structres Projects Explore the intersection of data structures and arithmetic with our projects and extend your skills through our calculator project in C.
For our implementation following mathematical operations are considered: 

Addition (+)
Subtraction (-)
Multiplication (*)
Division (/)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "APC.h"

int neg_flag = 0;	 // Global flag to track negative numbers in the result

int main(int argc, char *argv[])
{
	/* Error handling to pass the valid arguments */
	if (argc < 4)
	{
		printf("Please Pass Valid Arguments\n");
		printf("Usage : result.exe operand operator operand\n");
		return SUCCESS; // Exit if not enough arguments are provided
	}

	/* Validation for the operator */
	if ((strcmp(argv[2], "+") != 0) && (strcmp(argv[2], "-") != 0) && (strcmp(argv[2], "x") != 0) && (strcmp(argv[2], "/") != 0))
	{
		printf("Please Pass Valid Arguments\n");
		return SUCCESS; // Exit if the operator is invalid
	}

	/* Declare pointers for the data and result */
	Dlist *head1 = NULL;  // Head pointer for the first operand
	Dlist *tail1 = NULL;  // Tail pointer for the first operand
	Dlist *head2 = NULL;  // Head pointer for the second operand
	Dlist *tail2 = NULL;  // Tail pointer for the second operand
	Dlist *headR = NULL;  // Head pointer for the result
	Dlist *tailR = NULL;  // Tail pointer for the result

	char operator = argv[2][0];  // Store the operator ('+', '-', 'x', '/')

	/* Insert arguments into lists */
	if (insert_args(&head1, &tail1, &head2, &tail2, argv[1], argv[3]) == SUCCESS)
	{
		// printf("Inserting successful\n"); // Uncomment for debugging
	}
	else
	{
		printf("Inserting failed\n");
		return SUCCESS; // Exit if insertion fails
	}

	printf("Operand 1: ");
	print_list(&head1, &tail1);  // Print Operand 1
	printf("\nOperand 2: ");
	print_list(&head2, &tail2);  // Print Operand 2
	printf("\n");

	int diff; // Variable to store the difference in lengths
	if (operator != 'x')   // If the operator is not multiplication
	{
		/* Find length of both arguments excluding sign */
		int len1 = find_len(argv[1]);    // Get length of the first operand
		int len2 = find_len(argv[3]);     // Get length of the second operand
		/* Based on difference add 0's to make lists equal */
		if (len1 > len2)
		{
			diff = len1 - len2;   // Calculate the difference in length
			for (int i = 0; i < diff; i++)
			{
				add_res(&head2, &tail2, 0); // Add zeroes to the second operand
			}
		}
		else if (len2 > len1)
		{
			diff = len2 - len1;   // Calculate the difference in length
			for (int i = 0; i < diff; i++)
			{
				add_res(&head1, &tail1, 0); // Add zeroes to the first operand
			}
		}
	}

	/* Find big number among two lists */
	int large = find_larger(&head1, &head2);
	if (operator == '+') // If operator is addition
	{
		if (argv[1][0] == '-' && argv[3][0] == '-') // If both signs are negative, add sign bit
		{
			neg_flag = 1; // Set negative flag
		}
		else if (argv[large][0] == '-') // If big number has negative, add negative sign
		{
			neg_flag = 1; // Set negative flag
		}
	}
	else if (operator == '-') // If operator is subtraction
	{
		if (large == 1 && argv[1][0] == '-') // If both arguments are negative, enable negative flag 
		{
			neg_flag = 1; // Set negative flag
		}
		else if (argv[3][0] != '-' && large != 1) // If second argument has negative and big number is not 1, enable negative flag
		{
			neg_flag = 1; // Set negative flag
		}
	}
	else if (operator == '/' || operator == 'x') // If the operator is division or multiplication
	{
		if (argv[1][0] == '-' && argv[3][0] != '-') // If first operand is negative, set neg_flag
		{
			neg_flag = 1; // Set negative flag
		}
		else if (argv[1][0] != '-' && argv[3][0] == '-') // If second operand is negative, set neg_flag
		{
			neg_flag = 1; // Set negative flag
		}
	}

	/* Choose correct operator based on signs given for arguments */
	if (argv[2][0] == '+') // If the operator is '+'
	{
		if ((argv[1][0] != '-' && argv[3][0] == '-') || (argv[1][0] == '-' && argv[3][0] != '-')) // Check the signs of operands and choose correct operator
		{
			operator = '-'; // Change operator to subtraction
		}
		else
		{
			operator = '+'; // Otherwise, the operator remains '+'
		}
	}
	else if (argv[2][0] == '-') // If the operator is '-'
	{
		if ((argv[1][0] == '-' && argv[3][0] != '-') || (argv[1][0] != '-' && argv[3][0] == '-')) // Check the signs of operands and choose correct operator
		{
			operator = '+'; // If one operand is negative, the operator changes to '+'
		}
		else
		{
			operator = '-'; // Otherwise, the operator remains '-'
		}
	}

    /* Switch case based on operator */
	switch (operator)
	{
		case '+':
		    /* Call addition Function */
			if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
			{
				; // Successful addition
			}
			break;

		case '-':
		    /* Call Subtraction Function */
			if (large == 1)
			{
				if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
				{
                    ; // Successful subtraction
                }
			}
			else if (large == 3)
			{
				if (subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == SUCCESS)
				{
                    ; // Successful subtraction
				}
			}

	   		// Check if the result is zero
            if (headR == NULL || (headR->next == NULL && headR->data == 0)) 
		    {
                neg_flag = 0; // Reset negative flag for zero result
            }	
		    break;

		case '/':
		    /* Call division Function */
		    if (head2 == NULL || (head2->data == 0 && head2->next == NULL)) 
			{
                printf("Error: Divide by zero\n");
                return SUCCESS; // Exit the program
            }
			if (*argv[3] == '0' && strlen(argv[3]) == 1)
	        {
		            printf("Error : Divide by zero\n");
		            return SUCCESS; // Exit the program
	        }
			if (large == 3)
			{
				// printf("Division Successful\n"); // Uncomment for debugging
				printf("Result = 0");  // If the denominator is larger, result is zero
				printf("\nOperation successfully completed\n");
                return SUCCESS; // Exit after successful operation
			}
			else
			{
				if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
				{
                    ; // Successful division
                }
				else
				{
                    printf("Division failed\n"); // Print failure message
                }  
			}
			break;
		
		case 'x':
		    /* Call Multiplication Function */
			if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
			{
				; // Successful multiplication
			}
			else
			{
                printf("Multiplication failed\n"); // Print failure message
            }  
			break;
	}
	 
	/* Based on negative flag add sign for result */
	if (neg_flag == 1)    // If the negative flag is set, add a negative sign to the result
	{
		add_res(&headR, &tailR, '-'); // Add negative sign to the result
	}

	// Print result if operator is addition or subtraction
	if (operator != 'x' && operator != '/')
	{
		printf("Result = ");
		print_list(&headR, &tailR); // Print the result
		// printf("\n"); // Uncomment for debugging
	}
	printf("\nOperation successfully completed\n");

	/* Free all the nodes after the operation */
	free_all(&head1, &tail1, &head2, &tail2, &headR, &tailR);
	return SUCCESS; // Exit the program
}


/* Insert arguments into linked lists */
int insert_args(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv1, char *argv2)
{
	// Function calls to insert the arguments
	insert_at_last(head1, tail1, argv1); // Insert first operand
	insert_at_last(head2, tail2, argv2); // Insert second operand
	return SUCCESS; // Return success
}

/* Insert data at the last node in the linked list */
int insert_at_last(Dlist **head, Dlist **tail, char *argv) // Perform insert at last function
{
	for (int i = 0; i < strlen(argv); i++) // Till end of argument vector run loop
	{
		Dlist *new = malloc(sizeof(Dlist)); // Allocate memory dynamically
		if (new == NULL)
		{
			printf("Memory allocation failed\n"); // If memory not allocated return failure
			return FAILURE; // Return failure
		}
		if (argv[i] != '-' && argv[i] != '+') // If there were any signs ignore
		{
			new->data = argv[i] - 48; // Convert character into decimal
			if (new->data >= 0 && new->data <= 9) // If it is between 0 and 9
			{
				new->prev = NULL; // Initialize previous pointer
				new->next = NULL; // Initialize next pointer
				if (*head == NULL)
				{
					*head = new; // If list is empty, directly update the list with new address
					*tail = new; // Update tail to new
				}
				else
				{
					new->prev = *tail; // If not, update the new previous with tail
					(*tail)->next = new; // Update tail next with new 
					*tail = new; // Update tail with new
				}
			}
		}
	}
	return SUCCESS; // Return success
}

/* Function to free all nodes */
int free_all(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	// Call function to free each node
	free_node(head1, tail1); // Free first operand
	free_node(head2, tail2); // Free second operand
	free_node(headR, tailR); // Free result
}

/* Free each node */
void free_node(Dlist **head, Dlist **tail)
{
	Dlist *temp = (*head); // Temporary pointer to head
	Dlist *prev = NULL; // Previous pointer
	while (temp != NULL) // Run loop till end of list and free each node
	{
		prev = temp->next; // Update previous with next address
		free(temp); // Free temp 
		temp = prev; // Update temp with previous
	}
	*head = NULL; // Update head and tail with NULL
	*tail = NULL;
}

/* Function to find larger based on lists */
int find_larger(Dlist **head1, Dlist **head2)
{
	Dlist *temp1 = *head1; // Temporary pointer for first list
	Dlist *temp2 = *head2; // Temporary pointer for second list
	while (temp1 && temp2) // Loop through both lists
	{
		if (temp1->data > temp2->data) // Compare data of the nodes
		{
			return 1; // Operand 1 is larger
		}
		else if (temp2->data > temp1->data)
		{
			return 3; // Operand 2 is larger
		}
		temp1 = temp1->next; // Move to the next node in first list
		temp2 = temp2->next; // Move to the next node in second list
	}
	return SUCCESS; // Return success
}

/* Print result function to print data of node */
void print_list(Dlist **head, Dlist **tail)
{
	// printf("Result is "); // Uncomment for debugging
	Dlist *temp = *head; // Temporary pointer to head
	if (temp == NULL) {
        printf("0"); // If the list is empty, print 0
        return; // Exit the function
    }
	while (temp != NULL) // Loop through the list
	{
		if (temp->data == '-')
		{
			printf("%c", '-'); // Print negative sign
		}
		else
		{
			printf("%d", temp->data); // Print data
		}
		temp = temp->next; // Move to the next node
	}
	// printf("\n"); // Uncomment for debugging
}

/* Find length of argument ignoring the signs */
int find_len(char* argv)
{
	int i = 0, count = 0; // Initialize counters
	while (argv[i] != '\0') // Loop through each character
	{
		if (argv[i] == '-' || argv[i] == '+')
		{
			i++; // Skip sign
			continue; // Continue to next iteration
		}
		else
		{
			count++; // Increment the length for each digit
			i++; // Move to the next character
		}
	}
	return count; // Return the length of the argument excluding signs
}
