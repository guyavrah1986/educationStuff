// =============================================================================
// =============================================================================
// User input:
// -----------
//  1. Note that "public" identifier/members are Captial letters camel case:
//     os.Stdin, buffio.NewReader
//  2. The "comma, err" syntax - is a philosophy applied in the golang that
//     claims that errors that might occur during the program execution should
//     also be treated as variable, therefor, instead of using try-catch syntax
//     you simply add the 2nd (or last) variable that will be intercepted from
//     some function call, so that IF and error took place during the function
//     call - when it returns it will be NOT null.
//  3. It is also possible, if needed, to ignore the "correct" outcome of the
//     function and only treat the error.
//  4. If you sure you wish to ignore the error, the "error" variable can be
//     indicated as _. Note, however, that it is NOT a normal variable!
//
// =============================================================================
// =============================================================================
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	fmt.Println("start of user input example")
	fmt.Println("please enter some input string#1")

	// 1)
	reader := bufio.NewReader(os.Stdin)

	// 2)
	input, err := reader.ReadString('\n')
	fmt.Println("input from user:", input)
	fmt.Printf("type of err input is:%T\n", input)
	fmt.Printf("type of err variable is:%T\n", err)

	// 3)
	fmt.Println("please enter some input string#2")
	_, err = reader.ReadString('\n')
	fmt.Println("after second input from user error is:", err)

	// 4)
	fmt.Println("please enter some input string#3")
	input, _ = reader.ReadString('\n')
	fmt.Println("after third input from user input is:", input)
	// fmt.Println("after third input from user _ is:", _) --> _ is NOT a variable
}
