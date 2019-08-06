use std::io;
use std::cmp::Ordering;
use rand::Rng;

// main is starting function
fn main() {
    println!("---Starting the guessing game---");

    let secret_number = rand::thread_rng().gen_range(1, 1001);
    println!("The secret numnber is {}", secret_number); 

    loop {
        println!("---Please enter your guess ----");

        let mut guess = String::new();

        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        println!("You guess {}", guess);

        let guess: i32 = guess.trim().parse()
            .expect("Pleased type a number");

        match guess.cmp(& secret_number) {
            Ordering::Less => println!("Less"),
            Ordering::Equal => {
                println!("Equal");
                break;
            }
            Ordering::Greater => println!("Greater"),
        }
    }
}