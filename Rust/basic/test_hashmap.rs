use std::collections::HashMap;

fn test_hashmap_basic() {

    {
        let mut h = HashMap::new();
        // overite a value
        h.insert(String::from("Blue"), 10);
        h.insert(String::from("Yellow"), 20);
    }

    {
        let teams = vec![String::from("Blue"), String::from("Yellow")];
        let init_scores = vec![10, 20];

        let scores: HashMap<_, _> = teams.iter().zip(init_scores.iter()).collect();

        println!("scores = {:?}", scores);
    }

    {
        // Access Values in the hasmap
        let mut scores = HashMap::new();

        scores.insert(String::from("Navy"), String::from("Best color"));
        scores.insert(String::from("Red"), String::from("Years color"));

        let colorName = String::from("Navy");
        let score = scores.get(&colorName);

        println!("score = {:?}", score);

        for (k ,v) in &scores {
            println!("k = {}, v = {}", k, v);
        }
    }

    {
        // overwrite a value
        let mut scores = HashMap::new();

        scores.insert(String::from("Blue"), 20);
        println!("scores blue is {:?}", scores.get(&String::from("Blue")));

        scores.insert(String::from("Blue"), 10);
        println!("After changed :");
        println!("scores blue is {:?}", scores.get(&String::from("Blue")));

        // only insert a value if the key is empty
        scores.entry(String::from("Yellow")).or_insert(50);
        scores.entry(String::from("Blue")).or_insert(50);

        println!("{:?}", scores);
    }

    {
        let mut words = HashMap::new();
        let s = "The world most famous people is the people who eats the biggest hubgur";
        for c in s.split_whitespace() {
            let count = words.entry(c).or_insert(0);
            *count += 1; 
        }

        println!("{:?}", words);
    }
    
}

pub fn test_hashmap() {

    println!(" --- hashmap ---");

    test_hashmap_basic();

}