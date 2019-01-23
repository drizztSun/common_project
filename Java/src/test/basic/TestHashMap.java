package test.basic;

import java.util.HashMap;
import java.util.Map;
import java.util.Iterator;
import java.util.Set;

public class TestHashMap {

    public static void TestHashMap() {

        HashMap<Integer, String> hmap = new HashMap<Integer, String>();

        hmap.put(12, "Tom");
        hmap.put(13, "Peter");
        hmap.put(7, "Singh");
        hmap.put(3, "Anuj");
        hmap.put(2, "Michael");

        /*Display connect use iterator*/

        Set set = hmap.entrySet();
        Iterator it = set.iterator();

        while (it.hasNext()) {
            Map.Entry entry = (Map.Entry) it.next();
            System.out.println("Key is " + entry.getKey() + " &Value is " + entry.getValue() );
        }

        //Get value
        String var = hmap.get(2);
        System.out.println("hmap[2]: " + var);

        /*Remove values based on key*/
        hmap.remove(3);
        System.out.println("Map key and value after removal");
        Set set2 = hmap.entrySet();
        Iterator it2 = set2.iterator();

        while (it2.hasNext()) {
            Map.Entry entry = (Map.Entry) it2.next();
            System.out.println("Key is " + entry.getKey() + " &Value is " + entry.getValue());
        }
    }

}
