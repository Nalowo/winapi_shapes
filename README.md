# winapi_shapes

Draws geometric shapes in the window: `circle`, `ellipse`, `triangle`, `square`, `quadrangle`

Build:
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build .
```

To run the program you should pass the name of the desired figure to the exe file as a parameter
```
./winapi_shaps.exe circle
./winapi_shaps.exe quadrangle
```

Environment:
`g++ 12.2.0 (MinGW)`
`cmake 3.27.1`