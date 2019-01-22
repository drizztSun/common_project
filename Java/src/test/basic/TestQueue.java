package test.basic;

import java.util.Queue;
import java.util.LinkedList;

/*
*A Queue is designed in such a way so that the elements added to it are placed at the end of Queue and removed
* from the beginning of Queue. The concept here is similar to the queue we see in our daily life,
* for example, when a new iPhone launches we stand in a queue outside the apple store,
* whoever is added to the queue has to stand at the end of it and persons are served
* on the basis of FIFO (First In First Out), The one who gets the iPhone is removed from the beginning of the queue.
* */

public class TestQueue {

    public static void TestQueue() {

        /*
         * We cannot create instance of a Queue as it is an
         * interface, we can create instance of LinkedList or
         * PriorityQueue and assign it to Queue
         */
        Queue<String> q = new LinkedList<String>();

        //Adding elements to the Queue
        q.add("Rick");
        q.add("Maggie");
        q.add("Glenn");
        q.add("Negan");
        q.add("Daryl");

        System.out.println("Elements in Queue:"+q);

        /*
         * We can remove element from Queue using remove() method,
         * this would remove the first element from the Queue
         */
        System.out.println("Removed element: "+q.remove());

        /*
         * element() method - this returns the head of the
         * Queue. Head is the first element of Queue
         */
        System.out.println("Head: "+q.element());

        /*
         * poll() method - this removes and returns the
         * head of the Queue. Returns null if the Queue is empty
         */
        System.out.println("poll(): "+q.poll());

        /*
         * peek() method - it works same as element() method,
         * however it returns null if the Queue is empty
         */
        System.out.println("peek(): "+q.peek());

        //Again displaying the elements of Queue
        System.out.println("Elements in Queue:"+q);
    }
}
