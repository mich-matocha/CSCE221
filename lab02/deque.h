#ifndef DEQUE_H
#define DEQUE_H

#include <exception>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class Type>
class Deque
{
private:
	// data here
   Type* queue;
   int head;
   int tail;
   int qSize;
   int totSize; //the size of the entire array

public:
   Deque(int n)
   {
      queue = new Type[n];
      qSize = 0;
      totSize = n;
      head = totSize - 1;
      tail = totSize - 1;
   }

   ~Deque(void)
   {
      delete queue;
      queue = nullptr;
   }

   bool empty(void) const
   {
      return size() == 0;
   }

   int size(void) const
   {
      return qSize;
   }

   Type front(void) const
   {
      return queue[head];
   }

   Type back(void) const
   {
      return queue[tail];
   }

   void insertFront(Type o) //fixed!
   {
      if(!empty())
      {
         if(size() != totSize) //queue isn't full
         {
            if(head == 0)
            {
               head = totSize - 1;
            }
            else
            {
               --head;
            }
         }
         else
         {
            cout << "InsertionError" << endl;
            throw "InsertionError";
         }
      }
      //actually remember to insert it!!
      queue[head] = o;
      //cout << "Inserted " << queue[head] << " successfully at " << head << " (head), hopefully." << endl;
      ++qSize;
   }

   void insertBack(Type o)
   {
      if(!empty())
      {
         if(size() != totSize) //queue isn't full
         {
            if(tail == totSize - 1)
            {
               tail = 0;
            }
            else
            {
               ++tail;
            }
         }
         else
         {
            cout << "InsertionError" << endl;
            throw "InsertionError";
         }
      }
      //actually remember to insert it!!
      queue[tail] = o;
      //cout << "Inserted " << queue[tail] << " successfully at " << tail << " (tail), hopefully." << endl;
      ++qSize;

      /*int insertIndex;
      if(tail == totSize - 1 && head != 0) //if tail is the back
      {
         insertIndex = 0;
      }
      else if(size() != totSize) //queue isn't full
      {
         insertIndex = tail + 1;
      }
      else if(head == tail && empty())
      {
         insertIndex = head;
      }
      else
      {
         cout << "InsertionError" << endl;
         throw "InsertionError";
      }
      if(empty())
         head = insertIndex;
      cout << "Inserting at back at: " << insertIndex << endl;
      queue[insertIndex] = o;
      cout << "Inserted " << queue[insertIndex] << " successfully, hopefully." << endl;
      tail = insertIndex;
      ++qSize;*/
   }

   Type removeFront(void) //this works, i think
   {
      bool small = size() == 1;
      //cout << "this is the item to be removed from the front: " << queue[tail] << endl;
      //cout << "the index of the item: " << head << endl;

      Type ret = queue[head];
      if(!empty())
      {
         if(small)
         {
            --qSize;
         }
         else
         {
            if(head == totSize - 1)
            {
               head = 0;
            }
            else
            {
               ++head;
            }
            --qSize;
         }
         return ret;
      }
      else
      {
         //cout << "Nothing to remove" << endl;
         throw "Nothing to remove";
      }
   }

   Type removeBack(void)
   {
      bool small = size() == 1;
      //cout << "for fun, here's the head: " << queue[head] << endl;
      //cout << "this is the item to be removed from the back: " << queue[tail] << endl;
      //cout << "the index of the item: " << tail << endl;

      Type ret = queue[tail];
      if(!empty())
      {
         if(small)
         {
            --qSize;
         }
         else
         {
            if(tail == 0)
            {
               tail = totSize - 1;
            }
            else
            {
               --tail;
            }
            --qSize;
         }
         return ret;
      }
      else
      {
         //cout << "Nothing to remove" << endl;
         throw "Nothing to remove";
      }
   }
};

#endif