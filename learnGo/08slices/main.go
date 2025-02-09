// ============================================================================
// ============================================================================
// Slices:
// ------
//
//  0. This way the slice0 defined is technically nil. It is still possible
//     to append to it. The main difference from slice1 is that initially it
//     saves some amount of memory which is not used till it is appended.
//  1. In contrast to arrays, a slice can be declared without explicitly set
//     its size (length).
//  2. It is also possible to declare and set values into the slice object.
//  3. The append method can be used to add elements to the slice at the end.
//  4. All sort of "slicing" options are avialble, similarly to Python's
//  5. It is NOT possible to add an element to a slice which is NOT of the same
//     type as in the slice definition.
//  6. Adding an element to a slice with some given size (length) is NOT
//     possible in this form.
//  7. You can use the append method to add elements to a slice with a given
//     size, even if it means that the append will have to increase the size of
//     the slice to accommodate the "new" values.
//  8. An example to usage in built-in function sort that is possible on slice
//     and NOT on an array.
//  9. Remove an element from a specific index of the slice.
//     10.Another way to declare a slice using the make function.
//     11.Even though the slice was created using the make function, at this point
//     it still has space for only 4 elements. Trying to add the 5th - will
//     cause a run-time error.
//     12.In contrast to arrays, for slices there is, for example, the sort
//     built-in "library" with all kind of function to use on slices.
//     13.
//
// ============================================================================
// ============================================================================
package main

import (
	"fmt"
	"sort"
)

func main() {

	fmt.Println("main - slices example start")

	// 0
	var slice0 []string
	fmt.Printf("The length of slice0 is:%T\n", len(slice0))

	// 1)
	var slice1 = []string{}
	fmt.Printf("The type of slice1 is:%T\n", slice1)
	fmt.Printf("The length of slice1 is:%T\n", len(slice1))

	// 2)
	var slice2 = []int{1, 2, 3, 4}
	fmt.Printf("The type of slice2 is:%T\n", slice2)
	fmt.Println("slice2 has the following values:", slice2)

	// 3)
	slice2 = append(slice2, 5, 6)
	fmt.Println("After adding some values, slice2 is now:", slice2)

	// 4)
	var slice3 = slice2[1:3]
	fmt.Println("slice3 has the following values:", slice3)

	// 5)
	// slice3 = append(slice3, "str1")
	// will produce the following compilation error:
	// annot use "str1" (untyped string constant) as int value in argument to append

	// 6)
	//slice3[2] = 4
	// The above line will create the following run-time error:
	// panic: runtime error: index out of range [2] with length 2

	// 7)
	slice3 = append(slice3, 4, 5)
	fmt.Println("slice3 after append-ing elements to it is now:", slice3)

	// 8)
	var slice4 = []int{5, 33, 41, 23, 90, 7}
	fmt.Println("slice4 originally is:", slice4)
	sort.Ints(slice4)
	fmt.Println("slice4 AFTER sorting is:", slice4)

	// 9)
	var indexToRemove int = 2
	slice4 = append(slice4[:indexToRemove], slice4[indexToRemove+1:]...)
	fmt.Println("slice4 AFTER removing element in index:%d is:", indexToRemove, slice4)

	// 10
	highScores := make([]int, 4)
	highScores[0] = 100
	highScores[1] = 200
	highScores[2] = 300
	highScores[3] = 400
	fmt.Println("the highScoreshighScores slice is:", highScores)

	// 11)
	// highScores[4] = 500

	// 12)
	highScores = append(highScores, 500, 600)
	fmt.Println("After appending elements to the highScoreshighScores slice it is:", highScores)

	fmt.Println("Is the highScores slice sorted:", sort.IntsAreSorted(highScores))

	// 13)
	var courses = []string{"C", "C++", "Go", "Java", "Python"}
	fmt.Println("Initial list of courses is:", courses)
	var index = 3
	courses = append(courses[:index], courses[index+1:]...)
	fmt.Println("After removing all courses:", courses)
	fmt.Println("main - slices example end")
}
