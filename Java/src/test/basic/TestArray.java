package test.java;

class Student {

    public int roll_no;
    public String name;

    public Student(int roll_no, String name) {
        this.roll_no = roll_no;
        this.name = name;
    }
}

public class TestArray {


    public static void TestArray() {

        int array1[]; // declaration

        array1 = int[20] //

        array1[0] = 0;



        int array2[20];

        int[] array3 = new int[]{1, 2, 3, 4, 5, 6, 7, 8};


        for (int i = 0; i < array3.length; i++) {
            System.out.println("Element at index " + i + " : " + array3[i]);
        }


        Student[] arr;
        arr = new Student[5];

        arr[0] = new Student(1, "Tom");
        arr[1] = new Student(2, "vaibhav");
        arr[2] = new Student(3, "Peter");
        arr[3] = new Student(4, "Micael");
        arr[4] = new Student(5, "Foot");

        for (int i = 0; i < arr.length; i++) {
            System.out.println("ELement at index "  + i + " : " + arr[i].roll_no + " , " + arr[i].name);
        }
    }

}

