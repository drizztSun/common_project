use std::collections::HashMap;

/*
    *** HashMap ***
Where vectors store values by an integer index, HashMaps store values by key.
HashMap keys can be booleans, integers, strings, or any other type that implements the Eq and Hash traits. More on this in the next section.

Like vectors, HashMaps are growable, but HashMaps can also shrink themselves when they have excess space.
You can create a HashMap with a certain starting capacity using HashMap::with_capacity(uint), or use HashMap::new() to get a HashMap with a default initial capacity (recommended).

*/

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
        // *** Creating a New Hash Map
        let teams = vec![String::from("Blue"), String::from("Yellow")];
        let init_scores = vec![10, 20];

        let scores: HashMap<_, _> = teams.iter().zip(init_scores.iter()).collect();

        println!("scores = {:?}", scores);

        // *** Hash Maps and Ownership
        // For types that implement the Copy trait, like i32, the values are copied into the hash map.
        // For owned values like String, the values will be moved and the hash map will be the owner of those values,
        let field_name = String::from("Favorite color");
        let field_value = String::from("Blue");
        let mut map = HashMap::new();
        map.insert(field_name, field_value);
        // field_name and field_value are invalid at this point, try using them and
        // see what compiler error you get!

        // We aren’t able to use the variables field_name and field_value after they’ve been moved into the hash map with the call to insert.
        // If we insert references to values into the hash map, the values won’t be moved into the hash map.
        // The values that the references point to must be valid for at least as long as the hash map is valid.
    }

    {
        // *** Access Values in the hasmap
        let mut scores = HashMap::new();

        scores.insert(String::from("Navy"), String::from("Best color"));
        scores.insert(String::from("Red"), String::from("Years color"));

        let colorName = String::from("Navy");
        let score = scores.get(&colorName);

        // Here, score will have the value that’s associated with the Blue team, and the result will be Some(&10).
        // The result is wrapped in Some because get returns an Option<&V>; if there’s no value for that key in the hash map, get will return None.

        println!("score = {:?}", score);

        // We can iterate over each key/value pair in a hash map in a similar manner as we do with vectors, using a for loop:
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
        // The or_insert method on Entry is defined to return a mutable reference to the value for the corresponding Entry key if that key exists,
        // and if not, inserts the parameter as the new value for this key and returns a mutable reference to the new value.
        println!("{:?}", scores);
    }

    {
        // *** Updating a Value Based on the Old Value
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

/*

    *** Alternate/custom key types ***
Any type that implements the Eq and Hash traits can be a key in HashMap. This includes:

1) bool (though not very useful since there is only two possible keys)
2) int, uint, and all variations thereof
3) String and &str (protip: you can have a HashMap keyed by String and call .get() with an &str)
Note that f32 and f64 do not implement Hash, likely because floating-point precision errors would make using them as hashmap keys horribly error-prone.

All collection classes implement Eq and Hash if their contained type also respectively implements Eq and Hash.
For example, Vec<T> will implement Hash if T implements Hash.

You can easily implement Eq and Hash for a custom type with just one line: #[derive(PartialEq, Eq, Hash)]

The compiler will do the rest. If you want more control over the details, you can implement Eq and/or Hash yourself.
This guide will not cover the specifics of implementing Hash.

To play around with using a struct in HashMap, let's try making a very simple user logon system:
*/
// Eq requires that you derive PartialEq on the type.
#[derive(PartialEq, Eq, Hash)]
struct Account<'a> {
    username: &'a str,
    password: &'a str,
}

struct AccountInfo<'a> {
    name: &'a str,
    email: &'a str,
}

type Accounts<'a> = HashMap<Account<'a>, AccountInfo<'a>>;

fn try_logon<'a>(accounts: &Accounts<'a>, username: &'a str, password: &'a str) {
    println!("Username: {}", username);
    println!("Password: {}", password);
    println!("Attempting logon...");

    let logon = Account { username, password };

    match accounts.get(&logon) {
        Some(account_info) => {
            println!("Successful logon!");
            println!("Name: {}", account_info.name);
            println!("Email: {}", account_info.email);
        }
        _ => println!("Login failed!"),
    }
}

fn test_hasmap_customer_key() {
    let mut accounts: Accounts = HashMap::new();

    let account = Account {
        username: "j.everyman",
        password: "password123",
    };

    let account_info = AccountInfo {
        name: "John Everyman",
        email: "j.everyman@email.com",
    };

    accounts.insert(account, account_info);

    try_logon(&accounts, "j.everyman", "psasword123");

    try_logon(&accounts, "j.everyman", "password123");
}

pub fn test_hashmap() {
    println!(" --- hashmap ---");

    test_hashmap_basic();

    test_hasmap_customer_key();
}
