#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    } else {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    while (q_remove_head(q, NULL, 0))
        ;
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    } else {
        list_ele_t *newh;
        newh = malloc(sizeof(list_ele_t));
        if (newh == NULL) {
            return false;
        } else {
            newh->value = malloc(strlen(s) + 1 * sizeof(char));
            if (newh->value == NULL) {
                free(newh);
                return false;
            } else {
                strncpy(newh->value, s, strlen(s) + 1);
                newh->next = q->head;
                q->head = newh;
                q->size++;
                if (q->size == 1) {
                    q->tail = q->head;
                }
                return true;
            }
        }
    }
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL) {
        return false;
    } else {
        if (q->size == 0) {
            return q_insert_head(q, s);
        } else {
            list_ele_t *newt;
            newt = malloc(sizeof(list_ele_t));
            if (newt == NULL) {
                return false;
            } else {
                newt->value = malloc((strlen(s) + 1) * sizeof(char));
                if (newt->value == NULL) {
                    free(newt);
                    return false;
                } else {
                    strncpy(newt->value, s, strlen(s) + 1);
                    newt->next = NULL;
                    q->tail->next = newt;
                    q->tail = newt;
                    q->size++;
                    if (q->size == 1) {
                        q->head = q->tail;
                    }
                    return true;
                }

            }

        }

    }
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL) {
        return false;
    } else {
        // because will modify q->head
        list_ele_t *tmp = q->head;
        if (sp != NULL) {
            strncpy(sp, tmp->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }
        q->head = q->head->next;
        q->size--;
        if (q->size <= 1) {
            // Point tail to head
            q->tail = q->head;
        }
        free(tmp->value);
        free(tmp);
        return true;
    }
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    } else {
        return q->size;
    }
}


/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size == 0 || q->head == NULL) {
        return;
    } else {
        q->tail = q->head;
        list_ele_t *currentNode = q->head;
        list_ele_t *tmpNextNode = q->head->next;

        while (tmpNextNode) {
            list_ele_t *tmp = tmpNextNode->next;
            tmpNextNode->next = currentNode;
            currentNode = tmpNextNode;
            tmpNextNode = tmp;
        }
        q->head = currentNode;
        q->tail->next = NULL;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->size == 0 || q->head == NULL) {
        return;
    } else {

        list_ele_t *tmpCurrentNode = q->head;
        list_ele_t *tmpPreviousNode = NULL;

        for (int i = 0; i < q->size; i++) {
            list_ele_t *realNextNode = tmpCurrentNode->next;
            list_ele_t *tmpCompareToNode = q->head;
            list_ele_t *tmpPreviousCompareToNode = NULL;
            _Bool insertFlag = false;
            for (int j = 0; j < i; j++) {
                int result =
                    strcmp(tmpCompareToNode->value, tmpCurrentNode->value);
                if (tmpCompareToNode == q->head) {
                    if (result >= 0) {
                        insertFlag = true;
                        tmpPreviousNode->next = realNextNode;
                        tmpCurrentNode->next = tmpCompareToNode;
                        q->head = tmpCurrentNode;
                        if (i == (q->size - 1)) {
                            q->tail = tmpCompareToNode;
                        }
                        break;
                    }
                } else {
                    if (result >= 0) {
                        insertFlag = true;
                        tmpPreviousCompareToNode->next = tmpCurrentNode;
                        tmpCurrentNode->next = tmpCompareToNode;
                        tmpPreviousNode->next = realNextNode;
                        if (i == (q->size - 1)) {
                            q->tail = tmpPreviousNode;
                        }
                        break;
                    }
                }
                tmpPreviousCompareToNode = tmpCompareToNode;
                tmpCompareToNode = tmpCompareToNode->next;
            }
            // if insert happen, the tmpPreviousNode should be the same
            if (!insertFlag) {
                tmpPreviousNode = tmpCurrentNode;
            }
            tmpCurrentNode = realNextNode;
        }

    }


}
