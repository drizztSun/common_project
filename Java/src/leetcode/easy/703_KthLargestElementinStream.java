package leetcode.easy;

import java.util.PriorityQueue;

class KthLargest {

    public KthLargest(int k, int[] nums) {

        this.k = k;

        queue = new PriorityQueue<>(k);

        for (int i = 0; i < nums.length; i++) {
            this.add(nums[i]);
        }

    }

    public int add(int val) {
        if (queue.size() < k) {
            queue.add(val);
        } else if (val > queue.peek()){
            queue.remove();
            queue.add(val);
        }
        return queue.peek();
    }

    int k;
    PriorityQueue<Integer> queue;


    public static void test_703() {


        KthLargest obj = new KthLargest(3, new int[]{4, 5, 8, 2});

        System.out.println(obj.add(3));
        System.out.println(obj.add(5));
        System.out.println(obj.add(10));


    }
};
