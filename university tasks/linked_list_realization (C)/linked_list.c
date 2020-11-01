#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 33

typedef struct linked_list
{
    int value;
    struct linked_list* next;
} linked_list;

linked_list* list_create(int value)
{
    linked_list* element_pointer = (linked_list*)malloc(sizeof(linked_list));
    if (element_pointer != NULL)
    {
        element_pointer -> value = value;
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    return element_pointer;
}

void list_add_front(int value, linked_list** head)
{
    linked_list* buffer = *head;
    *head = list_create(value);
    (*head)->next = buffer;
}

linked_list* list_add_back(int value, linked_list** head)
{
    *head = list_create(value);
    (*head)->next = NULL;

    return *head;
}

size_t list_length(linked_list* head)
{
    size_t length = 1;
    linked_list* buffer = NULL;
    if (head == NULL) return 0;
    buffer = head -> next;
    while (buffer != NULL)
    {
        length ++;
        buffer = buffer -> next;
    }
    return length;
}

linked_list* list_node_at(size_t  index, linked_list* head)
{
    size_t counter = 0;
    linked_list* buffer = NULL;
    if (list_length(head) < index) return NULL;
    if (index == 0) return head;
    buffer = head -> next;
    counter ++;
    while (counter < index)
    {
        buffer = buffer -> next;
        counter ++;
    }

    return buffer;
}

void list_get(size_t  index, linked_list* head)
{
    linked_list* buffer = list_node_at(index, head);
    if (buffer != NULL)
    {
        printf("The element with index %i is %i\n", (int)index, buffer -> value);
    }
    else
    {
        printf("Index %i is out of bounds. Length of the linked list is %i\n", (int)index, (int)list_length(head));
    }
}

int list_sum(linked_list* head)
{
    int sum;
    linked_list* buffer = NULL;
    if (list_length(head) == 0) return 0;
    else sum = head -> value;
    buffer = head -> next;
    while (buffer != NULL)
    {
        sum += buffer -> value;
        buffer = buffer -> next;
    }

    return sum;
}

void list_free(linked_list** head)
{
    linked_list* free_buffer = NULL;
    if (*head != NULL)
    while ((*head) -> next != NULL)
    {
        free_buffer = (*head) -> next;
        free(*head);
        (*head) = free_buffer;
    }
    free(*head);
    *head = NULL;
}

int main(int argc, char *argv[])
{
    int char_buffer = 0, value;
    char buffer[BUFFER_LENGTH] = {0};
    unsigned char beginning = 0, first = 0, index;
    linked_list* head = NULL;

    printf("Random number of integers in stdin. Task:\n"
		"1. Save them in the linked list in reverse order\n"
		"2. Create function that counts sum of the elements\n"
		"3. Print the sum\n"
		"4. Print the elements of the list by the index if the list is long enough,\n"
		"else print message about too short length with exact length value\n"
		"5. Clear the memory after the list\n"
		"Restrictions:\n"
		"In stdin only numbers separated by several (random number of) whitespaces\n"
		"Every number fits in int\n"
		"Staring to read stdin until EOF (Ctrl+Z for Windows, Ctrl+D for *nix):\n ");
    while (char_buffer != EOF)
    {
        char_buffer = getchar();
        if (((char_buffer <= '9' && char_buffer >= '0') || char_buffer == '-') && beginning == 0)
        {
            beginning = 1;
            index = 0;
            memset(buffer, 0, BUFFER_LENGTH);
            buffer[index] = char_buffer;
            index ++;
        }
        else if (!((char_buffer <= '9' && char_buffer >= '0') || char_buffer == '-') && beginning == 1)
        {
            beginning = 0;
            value = atoi(buffer);
            if (first == 1) list_add_front(value, &head);
            else head = list_add_back(value, &head);
            if (first == 0) first = 1;
        }
        else if (((char_buffer <= '9' && char_buffer >= '0') || char_buffer == '-') && beginning == 1)
        {
            if (index >= BUFFER_LENGTH)
            {
                printf ("Error: Value is bigger than integer.\n");
                break;
            }
            buffer[index] = char_buffer;
            index ++;
        }
    }
    printf("Sum of the elements: %i\n",list_sum(head));
    for (index = 0; index <= list_length(head); index++)
    {
        list_get(index, head);
    }
    list_free(&head);

    return 0;
}
