// ============================================================================
// ============================================================================
// Functions:
// =========
//
// 1.Simple function definition. Note that the definition of the function
//
//	can be AFTER it is used (in the same file).
//
// 2.It is NOT possible to define a function within another function.
// 3.It is possible to return several values from a function.
// 4.It is possible that a function will have an UNKNOWN number of arguments
//
//	of the SAME type.
//
// ============================================================================
// ============================================================================
package main

import "fmt"

func main() {
	fmt.Println("Introduction to functions in golang")
	var x = 15
	var y = 17
	// 1)
	var result = add(x, y)
	fmt.Println("result of adding x + y is", result)

	// 2)
	/*
		func insideFunc() {
			fmt.Println("Inside function")
		}
	*/

	// 3)
	x, y = retTwoValues(x, y)
	fmt.Println("after calling retTwoValues x, y are:", x, y)

	// 4)
	sum := sumNumbers(1, 2, 3, 4, 5)
	fmt.Println("sum of numbers 1-5 is:", sum)
}

func add(x, y int) int {
	return x + y
}

func retTwoValues(x int, y int) (int, int) {
	return x + 1, y + 1
}

func sumNumbers(numbers ...int) int {
	sum := 0
	for _, number := range numbers {
		sum += number
	}

	return sum
}
