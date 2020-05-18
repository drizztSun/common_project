use minigrep::Config;
use std::env;
use std::process;

fn main() {
    /*
    Note that std::env::args will panic if any argument contains invalid Unicode.
    If your program needs to accept arguments containing invalid Unicode, use std::env::args_os instead.
    That function returns an iterator that produces OsString values instead of String values.
    We’ve chosen to use std::env::args here for simplicity,
    because OsString values differ per platform and are more complex to work with than String values.
    */

    // let args: Vec<String> = env::args().collect(); // only unicode inpit, env::args_os for invalid unicode

    // The env::args function returns an iterator! Rather than collecting the iterator values into a vector and then passing a slice to Config::new,
    // now we’re passing ownership of the iterator returned from env::args to Config::new directly.
    let config = Config::new(std::env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing the args {}", err);
        process::exit(1);
    });

    println!("Query {} in file {}", config.query, config.filename);

    if let Err(e) = minigrep::run(config) {
        eprintln!("Application error: {}", e);
        process::exit(1);
    };
}
