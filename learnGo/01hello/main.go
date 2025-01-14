// ============================================================================
// ============================================================================
// NOTES:
//  1. The go.mod file keeps track of all requiered modules (packages) in the
//     project. It automatically adds/removes desired/un-needed packages.
//  2. main is the SOLE entry point for the entire project (just
//     like C/C++/Java) and in CONTRAST to how you can start Python script from
//     "anywhere you wish".
//
// ============================================================================
// ============================================================================
package main

import "fmt"

func main() {
	fmt.Println("hello world with Go")
}
