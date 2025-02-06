#include <stdio.h> 
#include <string.h> 
#include "APC.h" 

/* Function to perform subtraction */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int sub = 0; // Variable to store the result of subtraction
    Dlist *temp1 = *tail1; // Pointer to the last node of the first list
    Dlist *temp2 = *tail2; // Pointer to the last node of the second list
    Dlist *temp3 = temp1; // Temporary pointer for traversing backwards in the first list

    // Check for invalid input
    if (!head1 || !tail1 || !head2 || !tail2 || !headR || !tailR) // Validate input pointers
    {
        fprintf(stderr, "Error: Invalid input to the subtraction function.\n"); // Print error message
        return FAILURE; // Return failure status
    }

    // Loop until both lists are fully traversed

    while (temp1 != NULL || temp2 != NULL) // Continue while either pointer is not NULL
    {
        // If the current digit of the first number is greater than or equal to the second
        
        if (temp1->data >= temp2->data) // Direct subtraction possible
        {
            sub = temp1->data - temp2->data; // Perform subtraction
        }
        else // If the first number's digit is less than the second
        {
            temp3 = temp1->prev; // Set temp3 to the previous node of temp1
            // Traverse backwards to find a non-zero digit
            while (temp3 != NULL) // Continue until the beginning of the list
            {
                if (temp3->data > 0) // Found a non-zero digit
                {
                    temp3->data--; // Decrement the non-zero digit
                    break; // Exit the loop after borrowing
                }
                else if (temp3->data == 0 && temp3->prev != NULL) // If a zero is found
                {
                    temp3->data = 9; // Change zero to nine for borrowing
                }
                temp3 = temp3->prev; // Move to the previous node
            }

            sub = (temp1->data + 10) - temp2->data; // Calculate the result with borrow
        }

        // Add the result to the resultant list
        if (add_res(headR, tailR, sub) == FAILURE) // Check if adding result was successful
        {
            fprintf(stderr, "Error: Failed to add result during subtraction.\n"); // Print error message
            return FAILURE; // Return failure status
        }

        // Move to the previous nodes for the next iteration
        temp1 = temp1->prev; // Move temp1 backwards
        temp2 = temp2->prev; // Move temp2 backwards
    }

    return SUCCESS; // Return success after completion
}
