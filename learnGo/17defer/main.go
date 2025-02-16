// ============================================================================
// ============================================================================
// Defer:
// -----
// 1.The defer keyword is used to "suspend" an execution of a statement, until
//	the wrapping function that encapsulates the defer statements are done.
//
// ============================================================================
// ============================================================================
package main

import "fmt"

func main() {
	fmt.Println("start of defer example")
	defer fmt.Println("One")
	defer fmt.Println("Two")
	someFuncWithDeferInLoop()
}

func someFuncWithDeferInLoop() {
	for i := 0; i < 5; i++ {
		defer fmt.Println(i)
	}
}
