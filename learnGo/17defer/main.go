// ============================================================================
// ============================================================================
// Defer:
// -----
// 1.The defer keyword is used to "suspend" an execution of a statement, until
//
//	the wrapping function that encapsulates the defer statements are done.
//
// 2.One common usages in defer is to use it in conjunction with recover, thus
//
//	it enables to facilitate sort of exception handling.
//
// 3.Enables RAII "semantics" to ensure resource de-allocation.
//
// ============================================================================
// ============================================================================
package main

import (
	"fmt"
	"sync"
)

func safeDivide(a, b int) {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered from panic:", r)
		}
	}()

	fmt.Println(a / b) // If b == 0, panic occurs
}

var mu sync.Mutex

func criticalSection() {
	fmt.Println("criticalSection - start")
	mu.Lock()
	defer mu.Unlock() // Ensures the lock is always released

	// Critical code...
	fmt.Println("criticalSection - end")
}

func main() {
	fmt.Println("start of defer example")
	defer fmt.Println("One")
	defer fmt.Println("Two")
	someFuncWithDeferInLoop()

	// 2)
	safeDivide(1, 0)

	// 3)
	criticalSection()
}

func someFuncWithDeferInLoop() {
	for i := 0; i < 5; i++ {
		defer fmt.Println(i)
	}
}
