use std::thread;
use std::vec;
use std::sync::mpsc;

use std::sync::Mutex;
use std::sync::Arc;


trait FnBox {
    fn call_box(self: Box<Self>);
}

impl <F: FnOnce()> FnBox for F {

    fn call_box(self: Box<F>) {
        (*self)()
    }
}


type Job = Box<dyn FnBox + Send + 'static>;

enum Message{
    NewJob(Job),
    Quit,
}

struct ThreadWorker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}

impl ThreadWorker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> ThreadWorker {
        let thread = thread::spawn(move|| {
            loop {
                let message = receiver.lock().unwrap().recv().unwrap();
                
                match message {
                    Message::NewJob(job) => {
                        println!("Woker {} got a job to execute", id);
                        job.call_box();            
                    }
                    Message::Quit => {
                        println!("Worker {} starts to quit!", id);
                        break;
                    }
                }
                
            }
        });
        ThreadWorker{
            id,
            thread: Some(thread),
        }
    }
}

pub struct ThreadPool{
    workers: Vec<ThreadWorker>,
    sender: mpsc::Sender<Message>,
}

struct PoolCreationError;

impl ThreadPool{
    /// Create a new ThreadPool.
    ///
    /// The size is the number of threads in the pool.
    ///
    /// # Panics
    ///
    /// The `new` function will panic if the size is zero.
    pub fn new(size: usize) -> ThreadPool {
    // pub fn new(size: usize) -> Result<ThreadPool, PoolCreationError> {
        assert!(size > 0);
        let mut workers = Vec::with_capacity(size);
        let (sender, receiver) = mpsc::channel();
        let receiver = Arc::new(Mutex::new(receiver));

        for id in 0..size {

            workers.push(ThreadWorker::new(id, Arc::clone(&receiver)));
        }

        ThreadPool{
            workers,
            sender,
        }
    }

    pub fn execute<F>(&self, f: F) 
        where 
            F : FnOnce() + Send + 'static
    {
        let job = Box::new(f);
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}

impl Drop for ThreadPool {
    fn drop(&mut self) {

        for _ in &self.workers {
            self.sender.send(Message::Quit).unwrap();
        }

        for work in &mut self.workers {
            println!("Shut down threading {}", work.id);
            if let Some(w) = work.thread.take() {
                w.join().unwrap();
            }
        }
    }
}
