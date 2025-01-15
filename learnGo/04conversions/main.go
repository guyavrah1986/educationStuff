// =============================================================================
// =============================================================================
// Conversions:
//  1. An anacdote - note that the input string can be delimited by any
//     character. NOTE: If NO 'h' character will be present in the input, the
//     execution of the program will hang.
//  2. Note that the input provided as a string needs to be "trimmed" from
//     spaces.
//
// =============================================================================
// =============================================================================
package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	fmt.Println("start of conversion example")

	reader := bufio.NewReader(os.Stdin)
	/*
		fmt.Println("Please enter some string")
		// 1)
		str1, err := reader.ReadString('h')
		if nil == err {
			fmt.Println("got the following string:", str1)
		} else {
			fmt.Println("error raised:", err)
		}
	*/

	fmt.Println("Please enter some number")
	str1, _ := reader.ReadString('\n')
	n, _ := strconv.ParseInt(strings.TrimSpace(str1), 10, 8)
	fmt.Println("the number provided + 1 is:", n+1)
}
