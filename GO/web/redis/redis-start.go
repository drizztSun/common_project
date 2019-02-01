package redis

import (
	"fmt"

	"github.com/go-redis/redis"
)

func initClient() (*redis.Client, error) {

	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0})

	ping, err := client.Ping().Result()
	fmt.Println(ping, err)

	if err != nil {
		return nil, err
	}

	return client, nil
}

func Test_redis() {
	/*
		if client, err := init_client(); err != nil {
			fmt.Println(err)
			return
		}*/

	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0})

	ping, err := client.Ping().Result()
	fmt.Println(ping, err)

	if err != nil {
		return
	}

	err = client.Set("key", "value", 0).Err()
	if err != nil {
		panic(err)
	}

	val, err := client.Get("key").Result()
	if err != nil {
		panic(err)
	}

	fmt.Println("key:", val)

	val2, err := client.Get("key2").Result()
	if err == redis.Nil {
		fmt.Println("key2 doesn't exist")
	} else if err != nil {
		panic(err)
	} else {
		fmt.Println("key2 : ", val2)
	}

	/*
		set, err := client.SetNX("key", "value", 10*time.Second).Result()

		// SORT list LIMIT 0 2 ASC
		vals, err := client.Sort("list", redis.Sort{Offset: 0, Count: 2, Order: "ASC"}).Result()

		// ZRANGEBYSCORE zset -inf +inf WITHSCORES LIMIT 0 2
		vals1, err := client.ZRangeByScoreWithScores("zset", redis.ZRangeBy{
			Min:    "-inf",
			Max:    "+inf",
			Offset: 0,
			Count:  2,
		}).Result()

		// ZINTERSTORE out 2 zset1 zset2 WEIGHTS 2 3 AGGREGATE SUM
		vals2, err := client.ZInterStore("out", redis.ZStore{Weights: []int64{2, 3}}, "zset1", "zset2").Result()

		// EVAL "return {KEYS[1],ARGV[1]}" 1 "key" "hello"
		vals3, err := client.Eval("return {KEYS[1],ARGV[1]}", []string{"key"}, "hello").Result()
	*/

	fmt.Println(" --- end --- ")
}
