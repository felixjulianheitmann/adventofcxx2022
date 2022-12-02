package p1

import (
	"fmt"
	"os"
)

func Puzzle(src_data string) {
	input, err := os.ReadFile(src_data)
	if err != nil {
		panic(err)
	}
	fmt.Println(input)
}
