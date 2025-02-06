#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "APC.h"

extern int neg_flag; // Declare external variable for negative flag

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int result = 0, count = 0, multiply = 0, carry = 0; // Declare the variables for result, count, multiplication, and carry
    Dlist *temp1 = *tail1; // Initialize temp1 to point to the tail of the first list
    Dlist *temp2 = *tail2; // Initialize temp2 to point to the tail of the second list
    Dlist *result_head1 = NULL; // Initialize result_head1 to NULL for the first result list
    Dlist *result_tail1 = NULL; // Initialize result_tail1 to NULL for the first result list
    Dlist *result_head2 = NULL; // Initialize result_head2 to NULL for the second result list
    Dlist *result_tail2 = NULL; // Initialize result_tail2 to NULL for the second result list

    while (temp2) // Loop through the second list until reaching NULL
    {
        carry = 0; // Reset carry to 0 for each iteration
        temp1 = *tail1; // Reset temp1 to the tail of the first list for each iteration
        while (temp1) // Loop through the first list until reaching NULL
        {
            multiply = carry; // Initialize multiply with the current carry value
            for (int i = 0; i < temp2->data; i++) // Multiply temp1's data by temp2's data
            {
                multiply = multiply + temp1->data; // Add temp1's data to multiply
            }
            carry = multiply / 10; // Calculate carry for the next iteration
            multiply = multiply % 10; // Get the last digit of the multiplication result
            if (count == 0) // Check if it's the first multiplication
            {
                add_res(&result_head1, &result_tail1, multiply); // Add the result to the first result list
            }
            else
            {
                add_res(&result_head2, &result_tail2, multiply); // Add the result to the second result list for subsequent multiplications
            }
            temp1 = temp1->prev; // Move to the previous node in the first list
        }
        if (carry > 0 && count > 0) // Check if there is a carry to add
        {
            add_res(&result_head2, &result_tail2, carry); // Add carry to the second result list
        }
        if (count == 0) // Check if it's the first multiplication
        {
            if (carry > 0) // If there is a carry
            {
                add_res(&result_head1, &result_tail1, carry); // Add carry to the first result list
            }
            add_res(&result_head1, &result_tail1, 0); // Add 0 for the next iteration
        }
        if (count >= 1) // Check if it's the second multiplication or more
        {
            for (int i = 1; i <= count; i++) // Add zeros to the end of the second result list
            {
                insert_last(&result_head2, &result_tail2); // Insert a new node with value 0 at the end
            }
            if (count % 2 == 1) // Check if count is odd
            {
                addition(&result_head1, &result_tail1, &result_head2, &result_tail2, headR, tailR); // Add the two result lists
                free_node(&result_head2, &result_tail2); // Free the second result list nodes
                free_node(&result_head1, &result_tail1); // Free the first result list nodes
                add_res(headR, tailR, 0); // Add a zero to the final result list
            }
            else // If count is even
            {
                addition(headR, tailR, &result_head2, &result_tail2, &result_head1, &result_tail1); // Add the two result lists
                free_node(headR, tailR); // Free the final result list nodes
                free_node(&result_head2, &result_tail2); // Free the second result list nodes
                add_res(&result_head1, &result_tail1, 0); // Add a zero to the first result list
            }
        }
        temp2 = temp2->prev; // Move to the previous node in the second list
        count++; // Increment the count for the next iteration
    }
    if (count % 2) // Check if count is odd
    {
        printf("Result = "); // Print the result message
        free_first(&result_head1); // Free the leading zero in the first result list
        if (neg_flag) // Check if the negative flag is set
            add_res(&result_head1, &result_tail1, '-'); // Add a negative sign if needed
        print_list(&result_head1, &result_tail1); // Print the first result list
    }
    else // If count is even
    {
        free_first(headR); // Free the leading zero in the final result list
        if (neg_flag) // Check if the negative flag is set
            add_res(headR, tailR, '-'); // Add a negative sign if needed
        print_list(headR, tailR); // Print the final result list
    }
    free_node(&result_head1, &result_tail1); // Free the first result list nodes
    free_node(&result_head2, &result_tail2); // Free the second result list nodes

    return SUCCESS; // Return success status
}

/*Insert at last function*/
void insert_last(Dlist **head, Dlist **tail)
{
    Dlist *new = malloc(sizeof(Dlist)); // Allocate memory for a new node
    if (new == NULL) // Check if memory allocation failed
    {
        printf("Memory allocation failed\n"); // Print error message
    }
    else
    {
        new->data = 0; // Initialize new node's data to 0
        new->prev = *tail; // Set the previous pointer to the current tail
        (*tail)->next = new; // Link the current tail to the new node
        new->next = NULL; // Set the next pointer of the new node to NULL
        *tail = new; // Update the tail to the new node
    }
}

/*Function to free the first node*/
void free_first(Dlist **head)
{
    Dlist *temp = *head; // Store the current head in a temporary variable
    *head = (*head)->next; // Move the head pointer to the next node
    (*head)->prev = NULL; // Set the previous pointer of the new head to NULL
    free(temp); // Free the memory of the old head
}
