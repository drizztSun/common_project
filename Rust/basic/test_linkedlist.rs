#![feature(drain_filter)]
use std::collections::LinkedList;

/*
A doubly-linked list with owned nodes.

The LinkedList allows pushing and popping elements at either end in constant time.
Almost always it is better to use Vec or VecDeque instead of LinkedList. 
In general, array-based containers are faster, more memory efficient and make better use of CPU cache.
*/

fn test_linkedlist_basic() {

    let list: LinkedList<u32> = LinkedList::new();

    {
        let mut list1 = LinkedList::new();
        list1.push_back('a');

        let mut list2 = LinkedList::new();

        list2.push_back('b');
        list2.push_back('c');

        list1.append(&mut list2);

        let mut iter = list1.iter();
        assert_eq!( iter.next(), Some(&'a') );
        assert_eq!( iter.next(), Some(&'b') );
        assert_eq!( iter.next(), Some(&'c') );
        assert!( iter.next().is_none());

        assert!( list2.is_empty() );

        list1.push_back('d');
        assert_eq!( list1.pop_back(), Some('d') );

        list1.push_front('0');
        assert_eq!( list1.pop_front(), Some('0') );

        // len
        assert_eq!( list1.len(), 3 );

        assert_eq!(list.is_empty(), true);

        // front and back
        assert_eq!( list1.front(), Some(&'a') );

        assert_eq!( list1.back(), Some(&'c') );

        // front 
        match list1.front_mut() {
            None => {},
            Some(m) => *m = 'f',
        }
        assert_eq!( list1.front(), Some(&'f'));

        match list1.back_mut() {
            None => {},
            Some(m) => *m = 'e',
        }
        assert_eq!( list1.back(), Some(&'f'));

        // clear
        list1.clear();
        
        assert_eq!( list.is_empty(), false );
    }

    {
        // iter
        let mut list: LinkedList<u32> = LinkedList::new();

        list.push_back(0);
        list.push_back(1);
        list.push_back(2);

        let mut iter = list.iter();
        assert_eq!(iter.next(), Some(&0));
        assert_eq!(iter.next(), Some(&1));
        assert_eq!(iter.next(), Some(&2));
        assert_eq!(iter.next(), None);

        // iter_mut
        for element in list.iter_mut() {
            *element += 10;
        }

        let mut iter = list.iter();

        assert_eq!(iter.next(), Some(&10));
        assert_eq!(iter.next(), Some(&11));
        assert_eq!(iter.next(), Some(&12));
        assert_eq!(iter.next(), None);

        // contain
        assert_eq!( list.contains(&0), true);
        assert_eq!( list.contains(&100), false);


    }

    {
        // split
        let mut d = LinkedList::new();

        d.push_back(1);
        d.push_back(2);
        d.push_back(3);

        let mut splitted = d.split_off(2);

        assert_eq!(splitted.pop_back(), Some(3));
        assert_eq!(splitted.pop_back(), None);
    }

    {
        // drain 
        let mut numbers: LinkedList<u32> = LinkedList::new();
        numbers.extend(&[1, 2, 3, 4, 5, 6, 8, 9, 11, 13, 14, 15]);

        // let evens = numbers.drain_filter(|x| *x % 2 == 0).collect::<LinkedList<_>>();
        let odds = numbers;

        // assert_eq!(evens.into_iter().collect::<Vec<_>>(), vec![2, 4, 6, 8, 14]);
        assert_eq!(odds.into_iter().collect::<Vec<_>>(), vec![1, 3, 5, 9, 11, 13, 15]);
    }
}



pub fn test_linkedlist() {

    test_linkedlist_basic();
}


