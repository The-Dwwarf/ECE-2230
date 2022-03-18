/* list.c                  <<-- A template to update and 
 * John Williams           <<-- change
 * jonccal
 * ECE 2230 Spring 2022
 * MP3
 *
 * Propose: A template for list.c. You will make many changes.
 *
 * Assumptions: Many details are incomplete.  
 *
 * Bugs: Many details have not been implemented.
 *
 * The interface definition for the two-way linked list ADT is based on one 
 * defined by OPNET, Inc. http://www.opnet.com/
 */

#include <stdlib.h>
#include <assert.h>

#include "datatypes.h"   /* defines Data */
#include "list.h"        /* defines public functions for list ADT */

/* definitions for private constants used in list.c only */

#define LIST_SORTED_ASCENDING   -29634
#define LIST_SORTED_DESCENDING  -61801
#define LIST_UNSORTED           -72467

/* prototypes for private functions used in list.c only */
void list_debug_validate(List *L);
void list_bubble_sort(List** L, int sort_order);
void list_insertion_sort(List** L, int sort_order);
void list_recursive_selection_sort(List** L, int sort_order);
void list_selection_sort(List** L, int sort_order);
void list_merge_sort(List** L, int sort_order);

/* sorting helper functions) */

/* Sorts a list used a specific sorting algorithm and direction.
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * sort_type: sorting algorithm used during sorting: 1) Bubble Sort; 
 *            2)Insertion Sort; 3) Recursive Selection Sort; 
 *            4) Iterative Selection Sort; and 5) Merge Sort
 *
 * sort_order: if 1 then the items are to be sorted in descending order.
 *             if 2 then the items are to be sorted in ascending order.
 *
 * return value: None.
 */
void list_sort(List **list_ptr, int sort_type, int sort_order)
{
    /* TODO: Complete the function sorting the list */

    //Checks to see if there is at least 2 items in the list
    if((*list_ptr)->current_list_size == 0)
    {
        printf("Shit broke my boy\n");
        return NULL;
    }

    else if((*list_ptr)->current_list_size == 1)
    {
        printf("Shit broke my boy\n");
        return NULL;
    }


   (*list_ptr)->list_sorted_state = LIST_SORTED_ASCENDING;// ? is ASCENDING or DESCENDING;
   

    if((*list_ptr)->head == NULL)
    {
        return NULL;
    }

    //Picks the correct sort based on the sort_type input 
    if(sort_type == 1)
    {
        list_bubble_sort(list_ptr, sort_order);
        (*list_ptr)->list_sorted_state == LIST_SORTED_DESCENDING;
    }

    else if(sort_type == 2)
    {
        list_insertion_sort(list_ptr, sort_order);
        (*list_ptr)->list_sorted_state == LIST_SORTED_ASCENDING;
    }

    else if(sort_type == 3)
    {
        list_selection_sort(list_ptr, sort_order);
    }

    else if(sort_type == 4)
    {
        list_selection_sort(list_ptr, sort_order);
    }

    else
    {
        list_merge_sort(list_ptr, sort_order);
    }

    list_debug_validate(*list_ptr);
}

/* Sorting the list via the insertion sort algorithm
 * 
 * L: pointer to list-of-interest.  
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order 
 */
void list_bubble_sort(List** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */

    int compareNum; 

    if ((*L)->current_list_size <= 1) assert("List is not valid"); //If the size is 1 or less then it is not a valid list

    list_node_tag *rover = (*L)->head;

    // Determines if it is going ascending or descending 
    if(sort_order == 1)
    {
        compareNum = 1;
    }

    else
        compareNum = -1;

    for(int i = 0; i < (*L)->current_list_size - 1; i++) // Loops through to acces each array element
    {
        for (int j = 0; j < (*L)->current_list_size - i - 1; j++) // Loop compares each array element
        {
            if((*L)->comp_proc(rover->data_ptr, rover->next->data_ptr) == compareNum)
            {
                swap(rover, rover->next);
                rover = rover->next;
            } 

            rover = (*L)->head; // Goes back to the start of the list

        }
    } 
}

/* Sorting the list via the insertion sort algorithm
 * 
 * L: pointer to list-of-interest.  
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order 
 */
void list_insertion_sort(List** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */
    if ((*L)->current_list_size <= 1) assert("List is not valid"); // Checks to see if list has at least 2 items

    List *NewList = list_construct((*L)->comp_proc, (*L)->data_clean); // Creates new list that is to be added to
    ListNode *NewHead;

    NewHead = (*L)->head;
    NewList = list_construct((*L)->comp_proc, (*L)->data_clean);

    // Determines wheter it is descending or ascending
    if(sort_order == 1)
    {
        NewList->list_sorted_state = LIST_SORTED_DESCENDING;
    }

    else if (sort_order == 2)
    {
        NewList->list_sorted_state = LIST_SORTED_ASCENDING;
    } 

    for (int i = 0; i < (*L)->current_list_size; i++) // Goes through list element by element
    {
        list_insert_sorted(NewList, list_remove(*L,0));  // Gets rid of head and adds it to another list
    }

    list_destruct(*L); // Empties List 
    *L =NewList;

}

/*
Helper function to find the max value of a list

input: pointer to list

output: max value of list
*/

ListNode *FindMax(List *L, ListNode *state, ListNode *end)
{
    Data *max = state->data_ptr;
    ListNode *MaxPos = NULL;
    while(state != NULL)
    {
        if(L->comp_proc(max, L->head->data_ptr) == -1)
        {
            max = state->data_ptr;
                if(state != NULL)
                {
                    MaxPos = state;
                }
        }

        state = state->next;
    }

    return MaxPos;
}

/*
Helper function to find the min value of a list

input: pointer to list

output: min value of list
*/

ListNode *FindMin(List *L, ListNode *state, ListNode *end)
{
    Data *min = state->data_ptr;
    ListNode *MinPos = NULL;
    while(state != NULL)
    {
        if(L->comp_proc(min, state->data_ptr) == 1)
        {
            min = state->data_ptr;
                if(state != NULL)
                {
                    MinPos = state;
                }
        }

        state = state->next;
    }

    return MinPos;
}

/* Sorting the list via the recursive selection sort algorithm
 * 
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order 
 */
void list_recursive_selection_sort(List** L, int sort_order)
{

    /* TODO: see MP3 document for implementation notes */
}

/* Sorting the list via the selection sort algorithm
 * 
 * L: pointer to list-of-interest.  
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order 
 */
void list_selection_sort(List** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */
    if ((*L)->current_list_size <= 1) assert("List is not valid due to size"); // Checks to see if list has at least 2 items
    if ((*L) == NULL || L == NULL) assert("List is not valid due to lack of elements") // Checks to see if the list is empty

    int compare; 

    if(sort_order == 1)
    {
        compare = 1;
    }

    else 
    {
        compare = -1;
    }

    list_node_tag *top, *temp, *rover;

    int j = 0;

    while(j < (*L)->current_list_size -1)
    {
        top = (*L)->head;
        
        for(int i = 0; i < j; i++)
        {
            top = top->next;
            i++;
            temp = top;
            rover = temp->next;

            while (rover)
            {
                /* code */
            }
            
        }
    }

}

/* Sorting the list via the merge sort algorithm
 * 
 * L: pointer to list-of-interest.  
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order 
 */
void list_merge_sort(List** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */

}




/* ----- below are the functions  ----- */

/* Obtains a pointer to an element stored in the specified list, at the
 * specified list position
 * 
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * pos_index: position of the element to be accessed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * return value: pointer to element accessed within the specified list.  A
 * value NULL is returned if the pos_index does not correspond to an element in
 * the list.  For example, if the list is empty, NULL is returned.
 */
Data * list_access(List *list_ptr, int pos_index)
{
    ListNode *L;

 
    assert(list_ptr != NULL);

    /* debugging function to verify that the structure of the list is valid */
    list_debug_validate(list_ptr);

    /* TODO: handle four special cases.
     *   1.  The list is empty
     *   2.  Asking for the head 
     *   3.  Asking for the tail
     *   4.  Asking for invalid pos
     */

    if(list_ptr->current_list_size == 0 || list_ptr->head __ list_ptr == NULL) // If the list is empty
    {
        return NULL;
    }

    else if(pos_index == 0 || pos_index == LISTPOS_HEAD) //Gets the head
    {
        L = list_ptr->head;
    }

    else if(pos_index >= list_ptr->current_list_size) //Gets the tail
    {
        L = list_ptr->tail;
    }

    else if()

    /* we now know pos_index is for an interal element */
    /* TODO: loop through the list until find correct position index */
    
    assert(L != NULL);
    return L->data_ptr;
}

/* Allocates a new, empty list 
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values LIST_SORTED_ASCENDING LIST_SORTED_DESCENDING or 
 * LIST_UNSORTED
 *
 * Use list_free to remove and deallocate all elements on a list (retaining the
 * list itself).
 *
 * comp_proc = pointer to comparison function
 *
 * Use the standard function free() to deallocate a list which is no longer
 * useful (after freeing its elements).
 */
List * list_construct(int (*fcomp)(const Data *, const Data *),
        void (*dataclean)(Data *))
{
    List *L;
    L = (List *) malloc(sizeof(List));
    L->head = NULL;
    L->tail = NULL;
    L->current_list_size = 0;
    L->list_sorted_state = LIST_SORTED_ASCENDING;
    L->comp_proc = fcomp;
    L->data_clean = dataclean;

    /* the last line of this function must call validate */
    list_debug_validate(L);
    return L;
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: use the comp_proc function pointer found in the List 
 *           header block. 
 *
 * The function returns a pointer to the matching element with lowest index if
 * a match if found.  If a match is not found the return value is NULL.
 *
 * The function also returns the integer position of matching element with the
 *           lowest index.  If a matching element is not found, the position
 *           index that is returned should be -1. 
 *
 * pos_index: used as a return value for the position index of matching element
 *
 *
 */
Data * list_elem_find(List *list_ptr, Data *elem_ptr, int *pos_index)
{
    list_debug_validate(list_ptr);

    /*TODO: */
    /* fix the return value */
    *pos_index = -1;

    list_node_tag *list = list_ptr->head; // Creates list 

    Data *found = NULL;

    if(list_access(list_ptr, *pos_index) == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < list_ptr->current_list_size; i++)
    {
        if(list_ptr->comp_proc(list->))
    }
    return NULL;
}

/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 *
 * Free all elements in the list, and the header block.  Use the data_clean
 * function point to free the Data items in the list.
 */
void list_destruct(List *list_ptr)
{
    /* the first line must validate the list */
    list_debug_validate(list_ptr);

    /*TODO*/
    // Your code starts here
    assert(list_ptr != NULL);

    if(list_ptr->current_list_size == 0) // If the list is empty
    {
        free(list_ptr); 
    }

    else
    {
        for(int i = (list_ptr->current_list_size) - 1; i >= 0; i--)
        {
            list_node_tag *list = list_ptr->tail;
            free(list_ptr->tail->data_ptr);
            list_ptr->tail = list_ptr->tail->prev;
            free(list);
        }
        free(list_ptr);
    }
}

/*
The function takes two nodes and swaps their data

Input: 
*xp: Pointer to first node
*yp: Pointer to second node

Returns NULL

*/

void swap(int *xp, int *yp)
{
    Data *temp = xp->data_ptr;
    xp->data_ptr = yp->data_ptr;
    yp->data_ptr = temp;
    temp = NULL;

}

/* Inserts the specified data element into the specified list at the specified
 * position.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * pos_index: numeric position index of the element to be inserted into the 
 *            list.  Index starts at 0 at head of the list, and incremented by 
 *            one until the tail is reached.  The index can also be equal
 *            to LISTPOS_HEAD or LISTPOS_TAIL (these are special negative 
 *            values use to provide a short cut for adding to the head
 *            or tail of the list).
 *
 * If pos_index is greater than the number of elements currently in the list, 
 * the element is simply appended to the end of the list (no additional elements
 * are inserted).
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->list_sorted_state must be equal 
 * to LIST_UNSORTED.
 */
void list_insert(List *list_ptr, Data *elem_ptr, int pos_index)
{
    assert(list_ptr != NULL);

    /*TODO*/

      ListNode *new = (ListNode*) malloc(sizeof(ListNode));

    if(list_ptr->current_list_size == 0) //When list is empty
    {
        new->prev = NULL;
        new->next = NULL;
        list_ptr->head = new;
        list_ptr->tail = new;
        list_ptr->current_list_size++;
    }

    else if(pos_index == 0 || pos_index == LISTPOS_HEAD) //Insert at the head
    {
        new->prev = NULL;
        new->next = NULL;
        list_ptr->head = new;
        list_ptr->tail = new;
        list_ptr->current_list_size++;
    }

     else if(pos_index == 0 || pos_index == LISTPOS_TAIL) //Insert at the tail
    {
        list_ptr->tail->next = new;
        new->prev = list_ptr->tail;
        new->next = NULL;
        list_ptr->tail = new; 
        list_ptr->current_list_size++;
    }

    else //Inserts at pos_index
    {
        ListNode *L;
        L = list_ptr->head;
        ListNode *Fin;

        for(int i = 0; i < pos_index; i++)
        {
            Fin = L->prev;
            new->prev = Fin;
            Fin->next = new;
            new->next = L;
            L->prev = new;
            list_ptr->current_list_size++;
        }
    }

    if (list_ptr->list_sorted_state != LIST_UNSORTED)
        list_ptr->list_sorted_state = LIST_UNSORTED;
    list_debug_validate(list_ptr);
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the comp_proc function pointer found in the header block.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * should generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type Data.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 * This definition results in the list being in ascending order.  To insert
 * in decending order, change the sign of the value that is returned.
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly inserted element will be placed after all the
 * elements of equal rank that are already in the list.
 */
void list_insert_sorted(List *list_ptr, Data *elem_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->list_sorted_state != LIST_UNSORTED);

    /* insert your code here */
    /*TODO*/

    int location = 0;

    ListNode *L = list_ptr->head;

    if(list_ptr->list_sorted_state == LIST_SORTED_ASCENDING)
    {
        while (L != NULL && list_ptr->comp_proc(L->data_ptr, elem_ptr) != 1)
        {
            location++;
            L = L->next;
        }
    }

    else if(list_ptr->list_sorted_state == LIST_SORTED_DESCENDING)
    {
        while(list != NULL && list_ptr->comp_proc(L->data_ptr, elem_ptr) != 1)
        {
            location++;
            L = L->next;
        }
    }

    list_insert(list_ptr, elem_ptr, location);

    list_ptr->list_sorted_state = list_ptr->list_sorted_state;


    /* the last line of this function must be the following */
    list_debug_validate(list_ptr);
}

/* Removes an element from the specified list, at the specified list position,
 * and returns a pointer to the element.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * pos_index: position of the element to be removed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * Attempting to remove an element at a position index that is not contained in
 * the list will result in no element being removed, and a NULL pointer will be
 * returned.
 */
Data * list_remove(List *list_ptr, int pos_index)
{
    list_debug_validate(list_ptr);

     Data *N;
     /* fix the return value */

     if(list_ptr->current_list_size == 0 || list_ptr->current_list_size <= pos_index) // Case for when it is 0
     {
         return NULL;
     }

     if((pos_index == 0 || pos_index == LISTPOS_HEAD) && list_ptr->current_list_size == 1) // Removes the head (Wish it was mine)
     {

         N = list_ptr->head->data_ptr;
         free(list_ptr->head);
         list_ptr->head = NULL;
         list_ptr->tail = NULL;
         list_ptr->current_list_size -=1;
         return N;
     }

     else if(pos_index == 0 || pos_index == LISTPOS_HEAD) //removes the head
     {
         N = list_ptr->head->data_ptr;
         list_ptr->head = list_ptr->head->next;
         free(list_ptr->head->prev);
         list_ptr->head->prev = NULL;
         list_ptr->current_list_size -=1;
         return N;
     }

     else if(pos_index == list_ptr->current_list_size-1 || pos_index == LISTPOS_TAIL) //removes the tail
     {
         N = list_ptr->tail->data_ptr;
         list_ptr->tail = list_ptr->tail->prev;
         free(list_ptr->tail->next);
         list_ptr->tail->next = NULL;
         list_ptr->current_list_size -=1;
         return N;
     }

     else
     {
         ListNode * L=list_ptr->head;
         for(int i=0; i<pos_index; i++)
         {
             L = L->next;
         }
         N = L->data_ptr;
         L->prev->next = L->next;
         L->next->prev = L->prev;
         L->next = NULL;
         L->prev = NULL;
         free(L);
         list_ptr->current_list_size -= 1;
         return N;
     }
 }
}

/* Reverse the order of the elements in the list.  Also change the 
 * list_sorted_state flag.  This function can only be called on a list
 * that is sorted.
 *
 * list_ptr: pointer to list-of-interest.  
 */
void list_reverse(List *list_ptr)
{
    assert(list_order(list_ptr) != 0);
    /*TODO*/

    ListNode *L, *reverse = list_ptr->head;

    list_ptr->tail = reverse;

    if(list_ptr->current_list_size > 1 && (list_ptr->head != list_ptr->tail))
    {
        while(reverse != NULL)
        {
            L = reverse->prev;
            reverse->prev = reverse->next;
            reverse->next = prev;
            reverse = reverse->prev;
        }

        list_ptr->head = L->prev;
    }

    if(list_ptr->list_sorted_state == LIST_SORTED_ASCENDING)
    {
        list_ptr->list_sorted_state = LIST_SORTED_DESCENDING;
    }

    else
    {
        list_ptr->list_sorted_state = LIST_SORTED_ASCENDING;
    }

    // after the list is reversed verify it is valid.
    list_debug_validate(list_ptr);
}
}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 */
int list_size(List *list_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->current_list_size >= 0);
    return list_ptr->current_list_size;
}

/* Obtains the sort status and order of the specified list. 
 *
 * list_ptr: pointer to list-of-interest.  
 *
 * Returns 
 *    1: the list is sorted in ascending order
 *   -1: descending order
 *    0: the list is not sorted but a queue
 */
int list_order(List *list_ptr)
{
    assert(list_ptr != NULL);
    if (list_ptr->list_sorted_state == LIST_SORTED_ASCENDING)
        return 1;
    else if (list_ptr->list_sorted_state == LIST_SORTED_DESCENDING)
        return -1;
    else if (list_ptr->list_sorted_state == LIST_UNSORTED)
        return 0;
    else 
        exit(5);  // this should not happen
}


/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void list_debug_validate(List *L)
{
#ifdef VALIDATE
    ListNode *N;
    int count = 0;
    assert(L != NULL);
    if (L->head == NULL)
        assert(L->tail == NULL && L->current_list_size == 0);
    if (L->tail == NULL)
        assert(L->head == NULL && L->current_list_size == 0);
    if (L->current_list_size == 0)
        assert(L->head == NULL && L->tail == NULL);
    assert(L->list_sorted_state == LIST_SORTED_ASCENDING 
            || L->list_sorted_state == LIST_SORTED_DESCENDING
            || L->list_sorted_state == LIST_UNSORTED);

    if (L->current_list_size == 1) {
        assert(L->head == L->tail && L->head != NULL);
        assert(L->head->next == NULL && L->head->prev == NULL);
        assert(L->head->data_ptr != NULL);
    }
    if (L->head == L->tail && L->head != NULL)
        assert(L->current_list_size == 1);
    if (L->current_list_size > 1) {
        assert(L->head != L->tail && L->head != NULL && L->tail != NULL);
        N = L->head;
        assert(N->prev == NULL);
        while (N != NULL) {
            assert(N->data_ptr != NULL);
            if (N->next != NULL)
                assert(N->next->prev == N);
            else
                assert(N == L->tail);
            count++;
            N = N->next;
        }
        assert(count == L->current_list_size);
    }
    if (L->list_sorted_state != LIST_UNSORTED && L->head != NULL) {
        N = L->head;
        int comp_val = -1 * list_order(L);
        while (N->next != NULL) {
            assert((L->comp_proc)(N->data_ptr, N->next->data_ptr) != comp_val);
            N = N->next;
        }
    }
#endif
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */

