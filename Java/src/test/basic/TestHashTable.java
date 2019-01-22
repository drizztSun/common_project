package test.basic;

import java.util.Hashtable;
import java.util.Enumeration;

/*
* This class implements a hash table, which maps keys to values. Any non-null object can be used as a key or as a value.
* Hashtable is similar to HashMap except it is synchronized. There are few more differences between HashMap and Hashtable class,
* you can read them in detail at: Difference between HashMap and Hashtable.

In this tutorial we will see how to create a Hashtable, how to populate its entries and then we will learn
how to display its key-value pairs using Enumeration. At the end of this article we will see Hashtable tutorials and methods of Hashtable class.
* */


public class TestHashTable {

    public static void TestHashTable() {

        Enumeration names;
        String key;

        // Creating a Hashtable
        Hashtable<String, String> hashtable =
                new Hashtable<String, String>();

        // Adding Key and Value pairs to Hashtable
        hashtable.put("Key1","Chaitanya");
        hashtable.put("Key2","Ajeet");
        hashtable.put("Key3","Peter");
        hashtable.put("Key4","Ricky");
        hashtable.put("Key5","Mona");

        names = hashtable.keys();
        while(names.hasMoreElements()) {
            key = (String) names.nextElement();
            System.out.println("Key: " +key+ " & Value: " +
                    hashtable.get(key));
        }

    }
}
