# c-data-structures

A C90 static library of common data structures, built with CMake and tested with Unity.

## Data Structures

- Singly linked list
- Doubly linked list *(planned)*
- Circular linked list *(planned)*
- Hashmap *(planned)*

## Build

Configure the build system (run after adding/removing source or header files, or after editing `CMakeLists.txt`):

```bash
./update_cmake.sh
```

Build the library:

```bash
cmake --build cmake
```

## Testing

```bash
./tests_build_run.sh
```

Tests live in `test/`. Each test file requires a corresponding block in `CMakeLists.txt` — see the existing `test_example` block as a guide.

## Adding a New Test

1. Create `test/test_foo.c` using `test_example.c` as a starting point.
2. Copy the test block in `CMakeLists.txt`, replacing `test_example` with `test_foo`.
3. Add `test_foo` to the `add_custom_target(tests DEPENDS ...)` line.
4. Re-run `./update_cmake.sh` to reconfigure.

## TODO

- Refactor `findNode` and `removeNode` to use a shared internal helper that returns both the matching node and its previous node, eliminating duplicated traversal logic

## Project Structure

```
.
├── src/            # Implementation files (.c)
├── include/        # Public headers (.h)
├── test/
│   ├── unity/      # Unity test framework
│   └── test_*.c    # Test files
├── bin/            # Compiled output (git-ignored)
│   └── test/       # Test binaries
└── cmake/          # CMake build directory (git-ignored)
```
