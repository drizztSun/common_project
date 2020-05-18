use std::error::Error;
use std::fs;
use std::vec::Vec;

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents =
        fs::read_to_string(config.filename).expect("Something went wrong reading the file");

    let results = if config.case_sensitive {
        search(&config.query, &contents)
    } else {
        search_case_insensitive(&config.query, &contents)
    };

    for line in results {
        println!("{}", line);
    }
    Ok(())
}

fn search<'a>(query: &str, content: &'a str) -> Vec<&'a str> {
    /*
    let mut result = Vec::new();

    for line in content.lines() {
        if line.contains(query) {
            result.push(line);
        }
    }

    result

    *** We can write this code in a more concise way using iterator adaptor methods. ***
    */

    content
        .lines()
        .filter(|line| line.contains(query))
        .collect()
}

pub fn search_case_insensitive<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let query = query.to_lowercase();
    /*
    let mut results = Vec::new();

    for line in contents.lines() {
        if line.to_lowercase().contains(&query) {
            results.push(line);
        }
    }
    results*/

    contents
        .lines()
        .filter(|x| x.to_lowercase().contains(&query))
        .collect()
}

pub struct Config {
    pub query: String,
    pub filename: String,
    pub case_sensitive: bool,
}

impl Config {
    // pub fn new(args: &[String]) -> Result<Config, &'static str> {

    pub fn new(mut args: std::env::Args) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }

        // We needed clone here because we have a slice with String elements in the parameter args, but the new function doesn’t own args.
        // To return ownership of a Config instance, we had to clone the values from the query and filename fields of Config so the Config instance can own its values.
        // let query = args[1].clone();
        // let filename = args[2].clone();

        // The standard library documentation for the env::args function shows that the type of the iterator it returns is std::env::Args.
        // We’ve updated the signature of the Config::new function so the parameter args has the type std::env::Args instead of &[String].
        // Because we’re taking ownership of args and we’ll be mutating args by iterating over it, we can add the mut keyword into the specification of the args parameter to make it mutable.
        let query = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn't get a query string"),
        };

        let filename = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn't get a file name"),
        };

        let case_sensitive = std::env::var("CASE_INSENSITIVE").is_err();

        println!("Cmdline args : {:?}", args);
        println!("Seaching for {}", query);
        println!("In file {}", filename);

        Ok(Config {
            query: query,
            filename: filename,
            case_sensitive,
        })
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";
        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}
