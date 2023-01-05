#include <cassert>
#include <iostream>
#include <string>

/*
 * File: pqueue.h
 * --------------
 * This interface exports the PriorityQueue template class, which implements
 * a queue in which the elements are dequeued in priority order.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "csc300222fall/assignment5/lib.h" // uncomment this line when you submit to OJ

using namespace std;

/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a linear structure called a priority queue in which
 * values are processed in order of priority.  As in conventional English
 * usage, lower priority numbers correspond to higher effective priorities,
 * so that a priority 1 item takes precedence over a priority 2 item.
 */

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new empty queue.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this queue.
 */

   ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) . . .
 * ------------------------------
 * Returns true if the queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from this queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value);
 *        pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the priority queue.  If priority is specified, the new
 * value goes immediately after any other entries with that priority.
 * If no value for priority is supplied, the priority value defaults to 0.
 */

   void enqueue(ValueType value, double priority = 0);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the first item in the queue.  This method
 * signals an error if called on an empty queue.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the first value in the queue without removing it.  This
 * method signals an error if called on an empty queue.
 */

   ValueType peek() const;

/*
 * Copy constructor and assignment operator
 * ----------------------------------------
 * These methods implement deep copying for queues.
 */

   PriorityQueue(const PriorityQueue<ValueType> & src);
   PriorityQueue<ValueType> & operator=(const PriorityQueue<ValueType> & src);

/* Private section */

/*
 * Implementation notes
 * --------------------
 * This implementation of PriorityQueue uses a linked list to store
 * the elements.  Each cell in the list maintains a priority value,
 * which is used to determine the order of the elements.
 */

private:

/* Type for linked list cell */

   struct Cell {
      ValueType data;                   /* The data value                  */
      double priority;                  /* The priority of this value      */
      Cell *link;                       /* Link to the next cell           */
   };

/* Instance variables */

   Cell *head;                          /* Pointer to the cell at the head */
   int count;                           /* Number of elements in the queue */

/* Private method prototypes */

   void deepCopy(const PriorityQueue<ValueType> & src);

};

/*
 * Implementation section
 * ----------------------
 * C++ requires that the implementation for a template class be available
 * to the compiler whenever that type is used.  The effect of this
 * restriction is that header files must include the implementation.
 * Clients should not need to look at any of the code beyond this point.
 */

/*
 * Implementation notes: PriorityQueue constructor
 * -----------------------------------------------
 * The constructor creates an empty linked list and sets the count to 0.
 */

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   head = NULL;
   count = 0;
}

/*
 * Implementation notes: PriorityQueue destructor
 * ----------------------------------------------
 * The destructor frees any heap memory allocated by the queue.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   clear();
}

/*
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These methods use the count variable and therefore run in constant time.
 */

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   while (count > 0) {
      dequeue();
   }
}

/* TODO PART:
 * Implementation notes: enqueue
 * -----------------------------
 * This method allocates a new list cell and chains it into the list at
 * the appropriate position.  In this implementation, that position is
 * determined using linear search and therefore runs in O(N) time.
 * Chapter 19 introduces an alternate implementation of PriorityQueue
 * that runs in O(log N) time.
 */

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   Cell *cp = new Cell;
   cp->data = value;
   cp->priority = priority;
   cp->link = NULL;
   if (head == NULL) {
      head = cp;
   } else {
      Cell *leftHead = NULL;
      Cell *leftTail = NULL;
      Cell *right = NULL;
      for (Cell *tra = head; tra != NULL; tra = tra->link) {
         int tmp = tra->priority;
         if (tmp <= priority) {
            Cell *tmpCell = new Cell;
            tmpCell->data = tra->data;
            tmpCell->priority = tra->priority;
            tmpCell->link = NULL;
            if (leftHead == NULL){
               leftHead = tmpCell;
            } else {
               leftTail->link = tmpCell;
            }
            leftTail = tmpCell;
         } else {
            right = tra;
            break;
         }
      }
      cp->link = right;
      leftTail->link = cp;
      head = leftHead;
   }
   ++count;
}

/* TODO PART:
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods checks for an empty queue and reports an error if
 * there is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   if (isEmpty()) error("dequeue: Attempting to dequeue an empty queue.");
   Cell *cp = head;
   ValueType result = cp->data;
   head = cp->link;
   delete cp;
   --count;
   return result;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   if (isEmpty()) error("peek: Attempting to peek at an empty queue.");
   return head->data;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods follow the standard template, leaving the work to deepCopy.
 */

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(const PriorityQueue<ValueType> & src) {
   deepCopy(src);
}

template <typename ValueType>
PriorityQueue<ValueType> & PriorityQueue<ValueType>::operator=(const PriorityQueue<ValueType> & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This function copies the data from the src parameter into the current
 * object.  This implementation copies the list into a new list of cells.
 */

template <typename ValueType>
void PriorityQueue<ValueType>::deepCopy(const PriorityQueue<ValueType> & src) {
   head = NULL;
   Cell **target = &head;
   for (Cell *scp = src.head; scp != NULL; scp = scp->link) {
      Cell *cp = new Cell;
      cp->data = scp->data;
      cp->priority = scp->priority;
      *target = cp;
      target = &cp->link;
   }
   *target = NULL;
   count = src.count;
}

#endif

/* DO NOT modify this part */
int main() {
   PriorityQueue<string> pq;
   assert(pq.size() == 0);
   assert(pq.isEmpty());
   pq.enqueue("A", 1);
   assert(!pq.isEmpty());
   assert(pq.peek() == "A");
   pq.enqueue("D", 3);
   pq.enqueue("C", 2);
   pq.enqueue("B", 1);
   assert(pq.peek() == "A");
   assert(pq.size() == 4);
   assert(pq.dequeue() == "A");
   assert(pq.peek() == "B");
   assert(pq.dequeue() == "B");
   assert(pq.dequeue() == "C");
   assert(pq.dequeue() == "D");
   assert(pq.isEmpty());
   cout << "Priority queue test succeeded" << endl;
   return 0;
}
