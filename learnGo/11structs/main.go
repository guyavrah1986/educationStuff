// ============================================================================
// ============================================================================
// Structs:
// ========
//
//  0. Some notes worth noting about golang before considering structs:
//     - There is no inheritance in Go.
//     - There is no "super"/"child"/"parent" concept as well.
//  1. This is how we define a struct named User. Note that the name of the
//     struct and ALSO each one of its fields start with a capital letter to
//     indicate a "public" like access capabilities.
//
// ============================================================================
// ============================================================================
package main

import "fmt"

// 1)
type User struct {
	Name string
	Age  int
}

func main() {
	fmt.Println("Introduction to structs in golang")
	u1 := User{"Roy", 37}
	u2 := User{"Rotem", 38}
	fmt.Printf("u1: %+v\n", u1)
	fmt.Printf("u2: %+v\n", u2)
	fmt.Println("u1 name is:", u1.Name)
	fmt.Println("u2 age is:", u1.Age)
}
