use std::collections::HashMap;

fn test_hashmap_basic() {
    {
        // A HashMap with fixed list of elements can be initialized from an array:
        let timber_resouces: HashMap<&str, i32> =
            [("Norway", 12), ("Denmark", 16), ("Iceland", 20)]
                .iter()
                .cloned()
                .collect();
    }

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

        for (k, v) in &scores {
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

// The easiest way to use HashMap with a custom key type is to derive Eq and Hash. We must also derive PartialEq.
#[derive(Hash, Eq, PartialEq, Debug)]
struct Viking {
    name: String,
    country: String,
}

impl Viking {
    // Create a new Viking
    fn new(name: &str, country: &str) -> Viking {
        Viking {
            name: name.to_string(),
            country: country.to_string(),
        }
    }
}

fn test_hashmap_customerkey() {
    let mut vikings = HashMap::new();

    vikings.insert(Viking::new("Einer", "Noway"), 25);
    vikings.insert(Viking::new("Olaf", "Denmark"), 20);
    vikings.insert(Viking::new("Harald", "Iceland"), 15);

    for (viking, health) in &vikings {
        println!("{:?} has {} hp", viking, health);
    }
}

pub fn test_hashmap() {
    println!(" --- hashmap ---");

    test_hashmap_basic();
}
