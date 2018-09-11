# cynet
Code used and related to the SW developer position in Cynet

# Cynet home task
Holds C# code for the server and C++ code for the client

1) Prerequeities:
-----------------
a) Download andf install the desired (preferably most updated) .NET core SDK and Run time support (this step is "similar" to install JDK and JRE):
- .NET Core SDK:     https://www.microsoft.com/net/download/Windows/build
- .NET Core Runtime: https://www.microsoft.com/net/download/Windows/run

2) Building and running the executable (DLL):
---------------------------------------------
In order to build and run the executable via the command line do the following:
a) Build the solution in Visual studio in Release mode !!!
Note that the: Project --> Properties --> Application has the 
- Target framework: .NET core 2.0 (or any other target you use)
- Output type: Console application

b) Publish the DLL: In order to be able to run the executable on any other machine, which offcourse, supports proper .NET framework do the following:
- Right click on the Project --> Publish
- Verify that the Target framework and other settings are as desired.
- The output files will be placed in the folder mention in the previous step (usually bin\Release\PublishOutput)

c) Run the "published" DLL:
- C:\Path\To\DLL > dotnet server.dll <ip_address> <port_number>