use {
    hyper::{
        // Following functions are used by Hyper to handle a `Request`
        // and returning a `Response` in an asynchronous manner by using a Future
        service::{make_service_fn, service_fn},
        // Miscellaneous types from Hyper for working with HTTP.
        Body,
        Client,
        Request,
        Response,
        Server,
        Uri,
    },
    std::net::SocketAddr,
};

async fn serve_req(_req: Request<Body>) -> Result<Response<Body>, hyper::Error> {
    // Always return successfully with a response containing a body with
    // a friendly greeting ;)
    println!("Get request at {:?}", _req.uri());

    // Ok(Response::new(Body::from("Hello world")))  
    
    let url_str = "http://www.rust-lang.org/en-us";
    let url = url_str.parse::<Uri>().expect("failed to parse URL");

    // Client::get returns a hyper::client::ResponseFuture, which implements Future<Output = Result<Response<Body>>> (or Future<Item = Response<Body>, Error = Error> in futures 0.1 terms). 
    // When we .await that future, an HTTP request is sent out, the current task is suspended, and the task is queued to be continued once a response has become available.
    let new = Client::new().get(url).await?;

    // Return the result of the request directly to the user
    println!("request finished-- returning response");
    Ok(res)
}

async fn run_server(addr: SocketAddr) {

    println!("Listening on HTTP:// {}", addr);

    // Create a server bound on the provided address
    let serv_future = Server::bind(&addr)
        // Serve requests using our `async serve_req` function.
        // `serve` takes a type which implements the `MakeService` trait.
        // `make_service_fn` converts a closure into a type which
        // implements the `MakeService` trait. That closure must return a
        // type that implements the `Service` trait, and `service_fn`
        // converts a request-response function into a type that implements
        // the `Service` trait.
    .serve(make_service_fn(|_| async {
        Ok::<_, hyper::Error>(service_fn(serve_req))
    }));

    // Wait for the server to complete serving or exit with an error.
    // If an error occurred, print it to stderr.
    if let Err(e) = serve_future.await {
        eprintln!("server error: {}", e);
    }
}
#[tokio::main]
async fn main() {
    println!("Start server");

    let addr = SocketAddr::from(([127.0.0.1], 3000));

    // Call our `run_server` function, which returns a future.
    // As with every `async fn`, for `run_server` to do anything,
    // the returned future needs to be run using `await`;
    run_server(addr).await;

    println!("Exit server");
}
