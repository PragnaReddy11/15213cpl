/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: Sree Pragna Machupalli , Andrew-id: smachupa
 * @author XXX <smachupa@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>
#include<stdio.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    // explanation - queue is going to be stored on heap (dont know how many nodes) so we call
    //malloc to allocate space
     queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
     
    
    // if null we return null 
    if(q==NULL)
    {
        //print-the memory cant be allocated
        printf("Out of Memory");
        return NULL;
    }

    //even head,tail and size!
    q->size = 0;
    q->head = NULL;
    q->tail = q->head;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    //case-1 : if the queue is null then return nothing
    if(q==NULL)
    {
        return;
    }
    /* How about freeing the list elements and the strings? */
    //explanation - A prev pointer to go over the queue and strings shall be freed
    list_ele_t *pre = q->head,*cur=q->head;
    //next shall be used to access value deleted by pre (let that be cur)
    //later the val shall be freed
    while(q->head != NULL)
    {
        free(pre->value);
        pre=cur;
        cur=pre->next;
        free(pre);
    }
    /* Free queue structure */
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    if(q==NULL)
    {
        return false;
    }
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    if (!newh)
    {  // q is NULL or fail to allocate space
        return false;
    }
    char *cstr;
    newh->value = (char*)malloc(strlen(s)+1);
    if(newh->value == NULL)
    {
        free(newh);
        return false;
    }
    memset(newh->value, '\0',strlen(s)+1);
    strcpy(newh->value,s);

    if(!q->tail)
    {
        q->tail = newh;
    }
    else 
    {
         newh->next = q->head;
         q->head = newh;
    }
    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(!q)
    {
        return false;
    }
    list_ele_t *ntail ;
    ntail = malloc(sizeof(list_ele_t));
    if(ntail == NULL)
    {
        return false;
    }
    char* cstr;
    cstr = (char*) malloc(sizeof(char)* strlen(s)+1);

    if(cstr == NULL)
    {
        free(ntail);
        return false;
    }

    memset(cstr, '\0' , strlen(s)+1);
    strcpy(cstr,s);
    ntail->value = cstr;
     if (q->tail == NULL)//当前队列中元素为空
    {
      q->head = ntail;
      q->tail = ntail;
    }
    else
    {
      q->tail->next = ntail;
      q->tail = ntail;
    }
    if (q->size == 0) {
        q->head = cstr;
    }
    ntail->next = NULL;
    q->size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
     if (q == NULL || q->size == 0 || q->head == NULL) {
        return false;
    }
    list_ele_t *oldhead = q->head, *newhead = q->head->next;

    if(buf !=NULL)
    {
        strncpy(buf,oldhead->value,bufsize-1);
        buf[bufsize=1] = '\0';
    }


    // we gotta free the space which was used by oldhead
    free(oldhead->value);
    free(oldhead);

    if(q->tail == q->head)
    {
        q->tail = q->head->next;
    }
    q->head = q->head->next;
    
    q->size--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
     if (q == NULL || q->head==NULL)
    {
      return 0;
    }
    return q->size;
    
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if(!q || !q->size)
    {
        return;
    }
    list_ele_t *ohead = q->head,*otail = q->tail;

    list_ele_t *f1=q->head;
    list_ele_t *f2 = NULL;
    list_ele_t *next = NULL;


     while(f1){
      next = f1->next;
      f1->next = f2;
      f2 = f1;
      f1 = next;
    }
    q->tail = ohead;
    q->head = f2;
  

}
