package main

import "fmt"

func main() {

	fmt.Println("--- sync main ---")

	test_channel()

	test_select()

	test_once()

	test_map_sync()

	test_map_sync_multi()

	test_bufferchannel()
}