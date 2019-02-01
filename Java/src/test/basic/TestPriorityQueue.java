package test.basic;

import java.util.PriorityQueue;
import java.util.Comparator;


class MyComparator implements Comparator<String> {

    @Override
    public int compare(String x, String y) {
        return x.length() - y.length();
    }
}

public class TestPriorityQueue {

    public static void TestPriorityQueue() {

        PriorityQueue<String> queue =
                new PriorityQueue<String>(15, new MyComparator());
        queue.add("Tyrion Lannister");
        queue.add("Daenerys Targaryen");
        queue.add("Arya Stark");
        queue.add("Petyr 'Littlefinger' Baelish");

        /*
         * What I am doing here is removing the highest
         * priority element from Queue and displaying it.
         * The priority I have set is based on the string
         * length. The logic for it is written in Comparator
         */
        System.out.println("Peek element is : " + queue.peek());
        System.out.println("Array it is : " + queue.toArray());

        if (queue.contains("Tyrion Lannister"))
            queue.remove("Tyrion Lannister");

        while (queue.size() != 0)
        {
            // remove the header
            System.out.println(queue.poll());
        }

        System.out.println("Array it is : " + queue.toArray());
    }
}
