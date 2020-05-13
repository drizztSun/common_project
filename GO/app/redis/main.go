package main

import (
	"fmt"
	"time"

	redis "github.com/go-redis/redis"
)

func NewRedisClient() *redis.Client {
	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "", // no password set
		DB:       0,  // use default DB
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, err)
	// Output: PONG <nil>

	return client
}

func Test_string() {

	client := NewRedisClient()

	err := client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}
	fmt.Println("key", val)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 does not exist")
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2", val2)
	}
	// Output: key value
	// key2 does not exist

}

func ExampleClient() {
	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "", // no password set
		DB:       0,  // use default DB
	})

	// SET key value EX 10 NX
	set, err := client.SetNX("key", "value", 10*time.Second).Result()

	// SORT list LIMIT 0 2 ASC
	vals, err := client.Sort("list", &redis.Sort{Offset: 0, Count: 2, Order: "ASC"}).Result()

	// ZRANGEBYSCORE zset -inf +inf WITHSCORES LIMIT 0 2
	vals1, err := client.ZRangeByScoreWithScores("zset", &redis.ZRangeBy{
		Min:    "-inf",
		Max:    "+inf",
		Offset: 0,
		Count:  2,
	}).Result()

	// ZINTERSTORE out 2 zset1 zset2 WEIGHTS 2 3 AGGREGATE SUM
	vals2, err := client.ZInterStore("out", &redis.ZStore{
		Keys:    []string{"zset1", "zset2"},
		Weights: []float64{2, 3}}).Result()

	// EVAL "return {KEYS[1],ARGV[1]}" 1 "key" "hello"
	vals3, err := client.Eval("return {KEYS[1],ARGV[1]}", []string{"key"}, "hello").Result()

	// custom command
	res, err := client.Do("set", "key", "value").Result()
}

func main() {

	ExampleClient()
}
