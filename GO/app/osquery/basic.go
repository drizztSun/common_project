package main

import (
	"context"
	"log"
	"runtime"
	"github.com/kolide/osquery-go"
	"github.com/kolide/osquery-go/plugin/table"
)

func path() string {

	var path string = `/var/osquery/osquery.em`

	if runtime.GOOS == "windows" {
		path = `\\.\pipe\osquery.em`
	}

	return path
}
func test_basic_osquery() {

	server, err := osquery.NewExtensionManagerServer("foobar", path())
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

	test_basic_osquery()
}