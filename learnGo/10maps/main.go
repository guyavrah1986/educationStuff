// ============================================================================
// ============================================================================
// Maps:
// ====
//
//  1. Creating a new Map using the make command. After that, one can add as
//     many elements to the map as he wishes.
//  2. Accessing a specific element in the map according to its key.
//  3. Deleting an existing element from a map using the built-in delete
//     keyword in golang.
//  4. Deleting a non-existing element (according to its key) from a map does
//     not do anything.
//
// ============================================================================
// ============================================================================
package main

import "fmt"

func main() {
	fmt.Println("Introduction to maps in golang")

	// 1)
	m1 := make(map[string]int)
	m1["key1"] = 100
	m1["key2"] = 200
	fmt.Println("After adding two values, m1 is:", m1)
	fmt.Println("Size of m1 is:", len(m1))

	// 2)
	fmt.Println("m1[key1] is:", m1["key1"])

	// 3)
	delete(m1, "key2")
	fmt.Println("After deleting key2 from a map, m1 is:", m1)

	// 4)
	delete(m1, "key3")

	// adding again the same key2,200 element and one more element
	m1["key2"] = 200
	m1["key3"] = 300

	// 5)
	fmt.Println("Values of m1 map are")
	for k, v := range m1 {
		fmt.Println("key:", k, "value:", v)
	}
}
