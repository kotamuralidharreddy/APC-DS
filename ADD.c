
#include <stdio.h> 
#include <stdlib.h> 
#include "APC.h" 

// Function to perform addition of two doubly linked lists

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
    int carry = 0, sum = 0, res = 0, car = 0; 
    // Initialize carry, sum, result, and carry for the next iteration

    Dlist *temp1 = *tail1; // Start from the tail of the first list
    Dlist *temp2 = *tail2; // Start from the tail of the second list

    // Loop until both lists are fully traversed
    while (temp1 != NULL || temp2 != NULL) {

        // If the first list is exhausted but the second is not
        if (temp1->prev == NULL && temp2->prev != NULL) {
            add_res(head1, tail1, 0); // Add a zero to the result for the first list
        }

        // If the second list is exhausted but the first is not
        else if (temp2->prev == NULL && temp1->prev != NULL) {
            add_res(head2, tail2, 0); // Add a zero to the result for the second list
        }
        
        // Calculate the sum of the current digits and the carry

        res = (temp1->data) + (temp2->data) + carry; // Sum the current digits and carry
        car = res / 10; // Calculate the new carry
        res = res % 10; // Get the current digit to store in the result
        sum = res; // Store the result digit

        add_res(headR, tailR, sum); // Add the result digit to the result list

        temp1 = temp1->prev; // Move to the previous node in the first list
        temp2 = temp2->prev; // Move to the previous node in the second list
        carry = car; // Update carry for the next iteration
    }
    
    // If there is a carry left after processing both lists
    if (carry != 0) {
        add_res(headR, tailR, carry); // Add the carry to the result list
    }
    
    return SUCCESS; // Return success status
}

// Function to add a result node to the result list

int add_res(Dlist **headR, Dlist **tailR, int sum) {
    Dlist *new = malloc(sizeof(Dlist)); // Allocate memory for a new node
    if (new == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed\n"); // Print error message
        return FAILURE; // Return failure status
    }

    new->data = sum; // Set the data of the new node
    new->prev = NULL; // Initialize previous pointer to NULL
    new->next = NULL; // Initialize next pointer to NULL
    
    // If the result list is empty
    if (*headR == NULL) { 
        *headR = new; // Set the new node as the head of the result list
        *tailR = new; // Set the new node as the tail of the result list
    } else {
        new->next = *headR; // Link the new node to the current head
        (*headR)->prev = new; // Link the current head back to the new node
        *headR = new; // Update the head to the new node
    }
    
    return SUCCESS; // Return success status
}
