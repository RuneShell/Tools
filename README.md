# Tools



### C++

<details>
<summary><strong>Debug Everything</strong></summary>
<div style="margin-left: 30px;">

example code:
```cpp
int a = 3;
const char* c = "Hello ";
std::string s = "World!";
std::vector<std::vector<int>> v{ {5, 6, 7}, {8, 9} };

_Debug(a, c, s, v); // Dynamic arguments
```
example result:
```
[ C:\...file_absolute_location...\test.cpp :: main() :: Line 12 ]
    int [a] = 3
    char const * __ptr64 [c] = Hello
    std::basic_string [s] = World!
    std::vector [v] = [[5, 6, 7], [8, 9]]
```

</div>
</details>


