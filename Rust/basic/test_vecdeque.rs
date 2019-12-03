use std::collections::VecDeque;

fn test_deque_basic() {
    // create
    let instance: VecDeque<u32> = VecDeque::new();

    let mut dp_vec: VecDeque<u32> = VecDeque::with_capacity(18);

    // add back
    dp_vec.push_back(1);
    dp_vec.push_back(100);
    dp_vec.push_back(3);
    dp_vec.push_back(4);
    dp_vec.push_back(5);

    assert_eq!(dp_vec.get(1), Some(&2));

    if let Some(elem) = dp_vec.get_mut(1) {
        *elem = 2;
    }
    assert_eq!(dp_vec.get(1), Some(&2));

    // back
    dp_vec.push_back(10000);
    if let Some(a) = dp_vec.pop_back() {
        assert_eq!(a, 10000);
    }

    // front
    dp_vec.push_front(10000);
    if let Some(b) = dp_vec.pop_front() {
        assert_eq!(b, 10000)
    }

    // insert
    dp_vec.insert(0, 0);
    assert_eq!(dp_vec, &[0, 1, 2, 3, 4, 5]);

    // append
    let mut buff2: VecDeque<_> = vec![10, 20, 30].into_iter().collect();
    dp_vec.append(&mut buff2);
    assert_eq!(dp_vec, &[0, 1, 2, 3, 4, 5, 10, 20, 30]);
    assert!(buff2.is_empty());

    // capacity
    assert!(dp_vec.capacity() >= 18);

    // len
    assert!(dp_vec.len() == 6);

    // contains
    assert_eq!(dp_vec.contains(&0), true);
    assert_eq!(dp_vec.contains(&100), false);

    // empty
    assert!(!dp_vec.is_empty());

    // remove
    dp_vec.push_front(100);
    if let Some(front) = dp_vec.remove(0) {
        assert_eq!(front, 100);
        assert_eq!(dp_vec, &[0, 1, 2, 3, 4, 5]);
    }

    // front
    {
        let mut d = VecDeque::new();
        assert_eq!(d.front(), None);

        d.push_front(100);
        assert_eq!(d.front(), Some(&100));

        if let Some(a) = d.front_mut() {
            *a = 200;
            assert_eq!(d, [200]);
        }

        match d.front_mut() {
            None => {}
            Some(a) => *a *= 10,
        }
        assert_eq!(d.front(), Some(&2000));
    }

    // back
    {
        let mut d = VecDeque::new();
        assert_eq!(d.back(), None);

        d.push_back(200);
        assert_eq!(d.back(), Some(&200));

        if let Some(b) = d.back_mut() {
            *b = 400;
            assert_eq!(d, [400]);
        }

        match d.back_mut() {
            None => {}
            Some(a) => *a *= 10,
        }

        assert_eq!(d.back(), Some(&4000))
    }

    // swap
    dp_vec.swap(0, 1);
    assert_eq!(dp_vec.get(0), Some(&100));
    assert_eq!(dp_vec.get(1), Some(&1));

    // iterate
    for n in dp_vec.iter() {
        println!();
    }

    // iterate mut
    for n in dp_vec.iter_mut() {
        *n += 100;
    }

    // clear
    dp_vec.clear();
}

fn test_deque_slice() {
    let mut buff1 = VecDeque::new();

    buff1.push_back(0);
    buff1.push_back(1);
    buff1.push_back(2);
    assert_eq!(buff1.as_slices(), (&[0, 1, 2][..], &[][..]));

    buff1.push_front(10);
    buff1.push_front(9);
    assert_eq!(buff1.as_slices(), (&[9, 10][..], &[0, 1, 2][..]));

    assert_eq!(buff1, &[0, 1, 2, 9, 10]);

    let mut buff2 = VecDeque::new();

    buff2.push_back(0);
    buff2.push_back(1);

    buff2.push_front(9);
    buff2.push_front(10);

    buff2.as_mut_slices().0[0] = 42;
    buff2.as_mut_slices().1[0] = 21;

    assert_eq!(buff2.as_slices(), (&[9, 10][..], &[42, 1][..]));
}

pub fn test_vecdeque() {
    test_deque_basic();

    test_deque_slice();
}
