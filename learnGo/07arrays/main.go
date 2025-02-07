// ============================================================================
// ============================================================================
// Arrays:
// ------
//
//  1. Basic definition of an array. Note that the size of the array (4 in this
//     case) HAVE to be set.
//  2. Just like in Python, len returns the number of values that can be stored
//     in the array.
//  3. Another way to declare and set values to an array.
//  4. If one tries to access an index that is NOT in the array boundaries - an
//     error will raise during "compilation time".
//  5. This example won't compile. An array can not be declared with a size
//     which is held by a variable.
//
// ============================================================================
// ============================================================================
package main

import (
	"fmt"
)

func main() {

	fmt.Println("main - arrays example start")

	// 1)
	var arr1 [4]string
	// var arr1[]string --> won't compile
	arr1[0] = "Apple"
	arr1[2] = "Orange"
	arr1[3] = "Peach"

	// 2)
	fmt.Println("main - the length of arr1 is:", len(arr1))
	fmt.Println("main - the contents of arr1 are:", arr1)

	// 3)
	var arr2 = [3]int{1, 2, 3}
	fmt.Println("main - the length of arr2 is:", len(arr2))
	fmt.Println("main - the contents of arr2 are:", arr2)

	// 4)
	fmt.Println("main - the content of arr2[0] is:", arr2[0])
	// fmt.Println("main - the content of arr2[3] is:", arr2[3])
	// produces the following compilation error:
	// invalid argument: index 3 out of bounds [0:3]

	// 5)
	//var arr3Size int = 2
	//var arr3 [arr3Size]float32

	fmt.Println("main - arrays example end")
}
