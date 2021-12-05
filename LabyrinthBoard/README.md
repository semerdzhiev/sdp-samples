# Labyrinth Board

This is a simple project, which illustrates how the breadth-first search (BFS) and depth-first search (DFS) algorithms work.
It also illustrates additional techniques, such as working with CMake, writing unit tests with Catch2, etc.

As the project is intended for educational purposes, certain parts of it have been simplified.
For example, in a real world application we would have provided stricter separation between the presentation layer and the program's logic.
Also, at this point, the unit test suite is incomplete.

## Building instructions.

### Visual Studio 2019

To open the project:

1. Start visual studio
2. Choose `File` > `Open` > `Folder...` (`Ctrl`+`Shift`+`Alt`+`O`)
3. Select the folder, which contains the project.

After that you can build the project in the traditional way.

You may want to install the [Test Adapter for Catch2](https://marketplace.visualstudio.com/items?itemName=JohnnyHendriks.ext01) by Johnny Hendriks. It will make it easier to work with Catch2 from within Visual Studio. The GitHub repo for the project [is this one](https://github.com/JohnnyHendriks/TestAdapter_Catch2). You can install the extension from the Visual Studio Marketplace:

1. Start Visual Studio
2. Choose `Extensions` > `Manage Extensions`.
3. The "Manage extensions" window will open. Search for "Catch2" and install the appropriate extension.
4. Restart Visual Studio.

After that you can work with the unit tests from Test Explorer (`Test` > `Test Explorer`).


### Command line

Go to the directory, which contains the project and execute the following:

```bash
mkdir out
cd out
cmake ..
cmake --build .
```

Note that there is a dot at the end of the last command!

In the example above we have named the output directory "out". It is not necessary to use this exact name. You can use another name if you prefer to do so.

To run the tests go to the output directory and run CTest:

```bash
ctest
```
