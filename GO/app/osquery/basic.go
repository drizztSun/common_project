package main

import (
	"context"
	"log"
	"os"
	"github.com/kolide/osquery-go"
	"github.com/kolide/osquery-go/plugin/table"
)

func test1() {

	//port := 8080
	if len(os.Args) != 2 {
		log.Fatal("Socket Port %s being used", os.Args[0])
	}

	server, err := osquery.NewExtensionManagerServer("foobar", os.Args[1])

	if err != nil {
		log.Fatalf("Error creating server %s \n", err)
	}

	// tableColumns defines the columns that our table will return.
	var tableColumns = []table.ColumnDefinition {
		table.TextColumn("foo"),
		table.TextColumn("baz"),
	}

	// FoobarGenerate will be called whenever the table is queried. It should return
	// a full table scan.
	var fooBarGenerator = func ( context.Context, table.QueryContext) ([]map[string]string, error) {
		return []map[string]string{
			{
				"foo": "bar",
				"baz": "baz",
			},
			{
				"foo": "bar",
				"bar": "baz",
			},
		}, nil
	}

	server.RegisterPlugin(table.NewPlugin("foobar", tableColumns, fooBarGenerator))

	if err := server.Run(); err != nil {
		log.Fatalln(err)
	}

}


func basic() {

	test1()
}