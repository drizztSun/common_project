package test.basic;

import java.util.LinkedHashMap;
import java.util.Set;
import java.util.Iterator;
import java.util.Map;

public class TestLinkedHashMap {

    public static void TestLinkedHashMap() {

        LinkedHashMap<Integer, String> lhashm =
                new LinkedHashMap<Integer, String>();

        lhashm.put(22, "Abey");
        lhashm.put(33, "Dawn");
        lhashm.put(1, "Sherry");
        lhashm.put(2, "Karon");
        lhashm.put(100, "Jim");

        Set set = lhashm.entrySet();
        Iterator it = set.iterator();

        while (it.hasNext()) {
            Map.Entry me = (Map.Entry) it.next();

            System.out.println("Key is : " + me.getKey() + " &Value is : " + me.getKey());
        }
    }
}
