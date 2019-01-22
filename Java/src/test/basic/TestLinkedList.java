package test.basic;

import java.util.ArrayList;
import java.util.LinkedList;

public class TestLinkedList {

    public static void TestLinkedList() {

        LinkedList<String> alink = new LinkedList<String>();

        alink.add("Item1");
        alink.add("Item5");
        alink.add("Item3");
        alink.add("Item6");
        alink.add("Item2");

        System.out.println("Linked list content : " + alink);


        // add head and tail
        alink.addFirst("Item0");
        alink.addLast("Item7");

        System.out.println("Linked list content : " + alist);

        Object firstVar = alink.get(0);
        System.out.println("First element " + firstVar);
        alink.set(0, "First element changed");
        Object firstVar2 = alink.get(0);
        System.out.println("First element after update is : " + firstVar2);

        // insert
        ArrayList<String> alink2 = new ArrayList<String>();
        alink2.add("new list0");
        alink2.add("new list1");
        alink.addAll(2, alink2);


        // remove
        alink.removeFirst();
        alink.removeLast();
        System.out.println("Linked list content : " + alink);

        alink.add(0, "Newly add item");
        alink.remove(2);
        alink.remove("Item7");
        System.out.println("Linked list content ： " + alink);

        //
        LinkedList<String> copy = alink.copy();
        System.out.println("Linked list content of copy ： " + copy);

        // location
        System.out.println("First : " + alink.getFirst());
        System.out.println("last : " + alink.getLast());
        System.out.println(" index i " + alink.get(1));

        // index
        System.out.println("index : " + alink.indexOf("Item6"));
        System.out.println("index of last one : " + alink.lastIndexOf("Item6"));

        // poll
        System.out.println("poll first one : " + alink.poll());
        System.out.println("poll last one : " + alink.pollLast());
        System.out.println("poll one of first ： " + alink.poll());

        //

    }
}
