
// setTimer
setTimer(200, () => {
    setTimer(100, () => {
      setTimer(50, () => {
        console.log("I'm the last one");
      });
    });
  });


// promise

function timer(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms))
}

timer(200)
.then(() => return timer(100))
.then(() => return timer(50))
.then(() => console.log("I'm the last one));


async function run() {
    await timer(200);
    await timer(100);
    await timer(50);
    console.log("I'm the last one");
}
