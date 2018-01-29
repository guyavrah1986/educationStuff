// ======================================================================================================================================================================================
/*
*  Function templates:
*  -------------------
* 1) When we define a function template we define a "blue print" for a potential function instantiartion. Nothing is being "created" (compiled) yet.
*
*
*
*/
// ======================================================================================================================================================================================

#pragma once

template <typename T> void foo(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}
