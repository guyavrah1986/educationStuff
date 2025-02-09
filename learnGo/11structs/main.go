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
//  2. Note that this property is only accessible within this package. Lower
//     case properties are considered as "private".
//
// ============================================================================
// ============================================================================
package main

import "fmt"

// 1)
type User struct {
	Name     string
	Age      int
	lastName string
}

func main() {
	fmt.Println("Introduction to structs in golang")
	u1 := User{"Roy", 37, "Eldar"}
	u2 := User{"Rotem", 38, "Hasid"}
	fmt.Printf("u1: %+v\n", u1)
	fmt.Printf("u2: %+v\n", u2)
	fmt.Println("u1 name is:", u1.Name)
	fmt.Println("u2 age is:", u2.Age)

	// 2)
	fmt.Println("u2 last name is:", u2.lastName)
}
