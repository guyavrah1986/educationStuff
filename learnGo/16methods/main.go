// ============================================================================
// ============================================================================
// Methods:
// ========
//
// 0.Just like in OO languages, there is the concept of methods (functions that
//
//	belong to some "class/object") in golang.
//
// 1.This is the format to declare a method of some struct ("object").
// 2.When passing an object (struct) to some function, it passes it by value,
//
//	  so actually a copy of it is being sent, thus the original instance is NOT
//		 being modified.
//
// ============================================================================
// ============================================================================
package main

import "fmt"

type MyClass struct {
	Name string
	Val1 int
	Val2 int
}

func (c MyClass) PrintMe() {
	fmt.Println("this instance properties are:", c)
}

func (c MyClass) SetVal1(val int) {
	c.Val1 = val
}

func (c *MyClass) SetVal2(val int) {
	c.Val2 = val
}

func main() {
	fmt.Println("Introduction to methods in golang")
	var obj1 = MyClass{"Guy", 100, 200}

	// 1)
	obj1.PrintMe()

	// 2)
	obj1.SetVal1(200)
	fmt.Println("After setting Val1 of obj1 it is:", obj1)
	obj1.PrintMe()

	// 3)
	obj1.SetVal2(100)
	fmt.Println("After setting Val2 of obj1 it is:", obj1)
}
