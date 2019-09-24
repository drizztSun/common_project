use std::io::prelude::*;
use std::net::TcpStream;

fn test_network_basic() -> std::io::Result<()> {

    let mut stream = TcpStream::connect("127.0.0.1:7878")?;
    let info = String::from("Testing client, info: hello world!");
    stream.write(&info.as_bytes())?;
    stream.read(&mut [0; 128])?;

    Ok(())
}

pub fn test_network() {

    test_network_basic();
}