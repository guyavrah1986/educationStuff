1) Introduction:
---------------
This folder contains:
a) The source code & binaries (after building them) of the google's protobuf library.
b) Within several places, some example code I used in order to manipulate C++ code that uses the protobuf capabilites.


2) Building process:
--------------------
In order to build the protobuf library I went over this "how-to": 
https://github.com/google/protobuf/blob/master/cmake/README.md
From the CMake section and forth, I chose the Visual Studio option.

Notes:
a) When building the solution in Debug mode there are some compilation errors --> Release mode DOES NOT have them, so I used it.
b) Part of the "output" of the building proccess of the library reside within the "install" folder 
(C:\Users\user\Desktop\Guy\dev\cynet\protobuffExamples\protobuf-cpp-3.5.1\install)

c) One of the "examples app" I used resdies within the "examples" folder of the source code: 
C:\Users\user\Desktop\Guy\dev\cynet\protobuffExamples\protobuf-cpp-3.5.1\protobuf-3.5.1\examples
I also added the "myBuild" folder to place the output of the build to perfrom "out-of-source" build when invoking CMake.

 

