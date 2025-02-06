#include <stdio.h> 
#include <string.h> 
#include "APC.h" 

extern int neg_flag; // Declare external variable for negative flag

// Function to perform division on two doubly linked lists
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Check if any of the input list heads or tails are NULL
    if (!head1 || !tail1 || !head2 || !tail2 || !headR || !tailR)
    {
        fprintf(stderr, "Error: Invalid input to the division function.\n"); // Print error message
        return FAILURE; // Return failure status
    }

    int flag = 0; // Initialize flag for loop control
    int count = 0, result = 0; // Initialize count and result variables
    Dlist *temp; // Temporary pointer for list manipulation

    // Loop until the flag indicates to stop
    while (flag != 1)
    {
        if (result % 2 == 0) // If result value is even
        {
            count++; // Increment count
            // Perform subtraction and check for failure
            if (subtraction(head1, tail1, head2, tail2, headR, tailR) == FAILURE)
            {
                fprintf(stderr, "Error: Subtraction failed during division.\n"); // Print error message
                return FAILURE; // Return failure status
            }
            temp = *headR; // Assign result to temporary variable
        }
        else // If result value is odd
        {
            count++; // Increment count
            // Perform subtraction and swap the lists, check for failure
            if (subtraction(headR, tailR, head2, tail2, head1, tail1) == FAILURE)
            {
                fprintf(stderr, "Error: Subtraction failed during division.\n"); // Print error message
                return FAILURE; // Return failure status
            }
            temp = *head1; // Assign result to temporary variable
        }

        // Check if the result is greater than the denominator
        flag = check_node(&temp, head2); 
        if (flag == 1) // If the result is greater
        {
            break; // Stop the process
        }
        else // If the result is not greater
        {
            // Free the nodes based on the result value
            if (result % 2 == 0)
                free_node(head1, tail1); // Free nodes from the first list
            else
                free_node(headR, tailR); // Free nodes from the result list
            result++; // Increment result
        }
    }

    // Print the result
    printf("Result = ");
    if (neg_flag) // Check if the result is negative
        printf("-"); // Print negative sign
    printf("%d", count); // Print the count as the result
    return SUCCESS; // Return success status
}

/* Function to check which node is bigger */
int check_node(Dlist **head1, Dlist **head2)
{
    // Check if either of the list heads is NULL
	if (!*head1 || !*head2) {
        fprintf(stderr, "Error: One of the lists is NULL in check_node.\n"); // Print error message
        return FAILURE; // Return failure status
    }

	Dlist *temp1 = *head1; // Temporary pointer for the first list
	Dlist *temp2 = *head2; // Temporary pointer for the second list
	while(temp1 && temp2) // Traverse both lists
	{
		if(temp1->data > temp2->data) // If first list data is greater
			return 0; // Return 0
		else if(temp1->data < temp2->data) // If second list data is greater
			return 1; // Return 1
		temp1 = temp1->next; // Move to the next node in the first list
		temp2 = temp2->next; // Move to the next node in the second list
	}
     
	return SUCCESS; // If both lists are equal, return success
}
