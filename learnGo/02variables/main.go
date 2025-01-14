package main

import "fmt"

// Global variables definition is possible only with
// the explict type declaration:
var num3 int = 17

// Global variable with capital letter means it can be
// used outside of this "file"
var Pnum5 = 23

// num4 := 17 --> won't compile!!

func main() {
	fmt.Println("variables example start")

	// bool type
	var isToPrint bool = true
	fmt.Println(isToPrint)
	fmt.Printf("The type of variable isToPrint is:%T \n", isToPrint)

	// unsigned int
	var i1 uint8 = 255 // try values < 0 OR > 255 and there will be a compilation error (lexer)
	fmt.Println(i1)
	fmt.Printf("The type of variable i1 is:%T \n", i1)

	// String
	var str1 string = "str1"
	fmt.Println(str1)
	fmt.Printf("The type of variable str1 is:%T \n", str1)

	// floating point - note the granularity of percision
	var f32 float32 = 32.1234567890
	fmt.Println(f32)
	fmt.Printf("The type of variable f32 is:%T \n", f32)

	// floating point - note the granularity of percision
	var f64 float64 = 32.1234567890
	fmt.Println(f64)
	fmt.Printf("The type of variable f64 is:%T \n", f64)

	// default values for the different data types
	var i2 int
	fmt.Println(i2)
	fmt.Printf("The type of variable i2 is:%T \n", i2)

	var str2 string
	fmt.Println(str2)
	fmt.Printf("The type of variable str2 is:%T \n", str2)

	// Implicit type
	var num1 = 12
	fmt.Println(num1)
	fmt.Printf("The type of variable num1 is:%T \n", num1)

	num2 := 15
	fmt.Println(num2)
	fmt.Printf("The type of variable num2 is:%T \n", num2)

	fmt.Println("num3 is:", num3)
}
