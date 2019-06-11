package main

import (
	"fmt"
	"os"
	"os/exec"
	"syscall"
	"runtime"
)

func must(err error) {
	if err != nil{
		panic(err)
	}
}

func run() {
	fmt.Printf("running %v", os.Args[2:])

	cmd := exec.Command("/proc/self/exe", append([]string{"child"}, os.Args[3:]...)...)

	cmd.Stdin = os.Stdin
	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout

	if runtime.GOOS == "linux" {
		cmd.SysProcAttr = &syscall.SysProcAttr{
			//Cloneflags: syscall.CLONE_NEWUTS | syscall.CLONE_NEWPID | syscall.CLONE_NEWNS,
		}
	}

	must(cmd.Run())
}

func child() {
	fmt.Println("running %v as pid %d\n", os.Args[2], os.Getpid())

	cmd := exec.Command(os.Args[2], os.Args[3:]...)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	must(syscall.Chroot("/home/rootfs"))
	must(os.Chdir("/"))
	//must(syscall.Mount("proc", "proc", "proc", 0, ""))
	must(cmd.Run())
}

func basic() {

	switch os.Args[1] {
	case "run":
		run()
	case "child":
		child()
	default:
		panic("what?")
	}
}


func main() {
	fmt.Println("--- Container Starting ---")

	basic()

	fmt.Println("--- Container ending ---")
}