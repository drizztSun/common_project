package test.basic;

import java.util.ArrayList;

public class TestArrayList {

    public static void TestArrayList() {

        ArrayList<String> alist = new ArrayList<String>();

        alist.add("Steve");
        alist.add("Tim");
        alist.add("Lucy");
        alist.add("Pat");
        alist.add("Angela");

        // displayment
        System.out.println(alist);

        // insert
        alist.add(3, "Steve");

        System.out.println(alist);

        // removing elements
        alist.remove("Steve");

        alist.remove(2);

        System.out.println(alist);

        // change elements
        alist.set(2, "Tim2");
        System.out.println("Index of Time 2 ： " + alist.indexOf("Tim2"));

        System.out.println("Index of 2 val is : " + alist.get(2));

        System.out.println("alist contains Tim2 : " + alist.contains("Tim2"));

        // iterate elements
        for (String element : alist) {
            System.out.println(element);
        }
    }

}
