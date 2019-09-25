use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;
use std::fs;
use std::thread;
use helloserver::ThreadPool;
use std::time::Duration;

fn handle_connection(mut stream: TcpStream) {

    let mut buff = [0; 512];
    let get = b"Get / HTTP/1.1\r\n\r\n";
    let sleep = b"Get /sleep HTTP/1.1\r\n\r\n";

    stream.read(&mut buff).unwrap();
    println!("Request: {} ", String::from_utf8_lossy(&buff[..]));

    let (status, file)  = if buff.starts_with(get) {
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else if buff.starts_with(sleep){
        thread::sleep(Duration::from_secs(5));
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else {
        ("HTTP/1.1 400 NOT FOUND \r\n\r\n", "404.html")
    };

    let content = fs::read_to_string(file).unwrap();
    let response = format!("{}{}", status, content);

    stream.write(&response.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn main() {
    println!("Starting Hello, world! web service");

    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    let pool = ThreadPool::new(4);

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        println!("Connection built!");
        pool.execute( move || {
            handle_connection(stream);
        })
        // thread::spawn( || {        
        //     handle_connection(stream)    
        // });
    }
}
