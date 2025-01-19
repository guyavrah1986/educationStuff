// ============================================================================
// ============================================================================
// Pointers:
// ---------
//  1. Defining a pointer to an int type. When it is not set explictly it is set
//     to nil by the compiler.
//  2. The & unary operator takes the address of a variable in memory.
//  3. The * unary operator is used to de-reference the pointer in order to
//     get the value it is pointing to.
//
// ============================================================================
// ============================================================================
package main

import (
	"fmt"
	"reflect"
)

func basicPointersDefinitions() {
	var funcName string = "basicPointersDefinitions - "
	fmt.Println(funcName + "start")

	// 1)
	var ptr *int
	fmt.Println(funcName+"without explict setting it, ptr points to:", ptr)
	fmt.Printf("Size of var ptr (reflect.TypeOf.Size): %d\n", reflect.TypeOf(ptr).Size())

	num1 := 12
	fmt.Println(funcName+"num1 has value of:", num1)
	fmt.Printf("Size of var num1 (reflect.TypeOf.Size): %d\n", reflect.TypeOf(num1).Size())

	// 2)
	var ptr1 *int = &num1

	// 3)
	fmt.Println(funcName+"ptr1 points to value of:", *ptr1)
	fmt.Println(funcName+"address of ptr1 is:", ptr1)
	fmt.Println(funcName + "end")
}

func main() {

	fmt.Println("memory managment example start")
	basicPointersDefinitions()
	fmt.Println("memory managment example end")
}
