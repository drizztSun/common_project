async Task Main()
{
    Thread.CurrentThread.ManagedThreadId.Dump("1");

    await MakeTeaAsync();
}

/*
asyc Task<...> 
is a key word to async function, then the function is going to become a package/object not function and returning a Task.
based on the 'await' call, the function will be split into couple pieces of task, loically, which will be called in different async threads, in async pool.

Compiler will handle async function like below.
(1) there is no function, back a Task object generated.
(2) Task object has a lot of task, state member, created and split by 'await' usage in that function
(3) There is 'MoveNext' function, only function to run in the 'Task' object, to execute thise task, state, on the code we designed in the function.
(4) 'MoveNext' code will create 'stateMachine', 'awaiter', etc to control the tasks and state running with 'Async runtime' itself
(5) at the end of 'MoveNext', when differnt 'tasks' and 'phased/parts' finished, it will return 'res'.


The whole async is built on concept and component, like Async/Await/Task/State mechine/Async Thread pool.

When we call Task.await(), code will go check status of the asymc object. 

if there is result ready, return the result.

if there is no result ready, it will set the current asyc object await, to a event and give control to async mode. 
(Async mode thread pool helps this async)
Async mode threads will execute next await task in async model queue, 
Since current task has been hang and await, executor will notify this await object, if what it is waiting for is ready. 
then the task will becoming to be await, (means ready to run, so wait to be called) 

*/
async Task taskRunning() {

    // part 1
    Thread.CurrentThread.ManagedThreadId.Dump("1");
    var client = new HttpClient();

    Thread.CurrentThread.ManagedThreadId.Dump("2");
    var task = client.GetStringAsync("https://www.google.com");
    Thread.CurrentThread.ManagedThreadId.Dump("3");

    var a = 0;
    for (int i = 0; i < 1000_000_000; i++) {
        a += 1;
    }

    Thread.CurrentThread.ManagedThreadId.Dump("4");

    /*
        // IL 
        // await is gonna check awaiter is completed
        // if it not, it is gonna call AwaitUnsafeOnCompleted
        // build the stateMachine and save into the RAM.

        // in 'if', it use num to control and if await is not completed, it is gonna create a stateMachine,
        // and set num == 0, then set awaiter into asyc model AwaitUnsafeOnCompleted func.
        // then return 
        
        // when the network task is done, 
        // Runtime will call 'MoveNext'. because of num == 0, it will execute TaskWaiter logic.
        // In the 'Else', 

        func MoveNext() {
            if num != 0{
                
                TaskAwaiter<String> await;

                <client>5_1 = new HttpClient()
                await = <client>5__1.GetStringAsync("https://www.google/com").GetAwaiter();
                if (!await.IsCompleted()) 
                {
                    num = (<>1_state = 0)
                    <>u_1 = awaiter;
                    <Main>d__0 stateMachine = this;
                    <>t__builder.AwaitUnsafeOnCompleted(ref awaiter, ref stateMachine);
                    return;
                }
            } else {
                awaiter = <>u_1
                <>u_1 = default(TaskAwaiter<string>);
                num = (<>1_state=1)
            }
            
            // after await
            <>s__6 = awaiter.GetResult();
            <page>5__4 = <>s__6;
            <>s__6 = null;
            Console.WriteLine("Hello world")

        }

    */

    // await split the function into two part. below code could be called in same or differnt thread.
    var page = await task;
    //part 2
    Thread.CurrentThread.ManagedThreadId.Dump("5");
    Console.WriteLine("Hello World");
}


async Task<string> MakeTeaAsync() 
{

    var boilWater = BoilWaterAsync();

    "take the cup out".Dump();

    var a = 0;
    for (int i = 0; i < 1000_000_000; i++) {
        a += 1;
    }

    var water = await boilWater;

    var tea = $"pour {water} in cups".Dump();
}

async Task<string> BoilWaterAsync() 
{
    "Start the kettle".Dump();

    "Waiting for the kettle".Dump();

    await Task.Delay(3000);

    "Kettle finished boiling".Dump();

    return "Water";
}

string BoilWater() 
{
    "Start the Kettle".Dump();
    
    // wait 200 ms to get the result, Boiled water. because boiling water wastes time
    "Waiting for the kettle".Dump();
    Task.Delay(200).GetAwaiter().GetResult();

    "Kettle finish boiling".Dump();

    return "Water";
}

string MakeTea() 
{

    var water = BoilWater();

    // BoilWater is sync call. it will execute 200 ms, before we prepare cups and tea
    // boil water and cups and tea could be doing in paralleel.
    // before Async mode, we can use two thread to work on this one. but creating thread is too much burden for system
    // Async threads can take over this, by swtiching to active await task when call await
    
    "take the cups out".Dump();

    "put the tea into cups".Dump();

    var tea = $"pour {water} in cups".Dump();

    return tea;
}