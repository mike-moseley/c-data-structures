# TODO

## slice:

Implement a `growSliceTo(new_cap)` that grows the cap to a specific size
refactor in miSHa once completed.

## str_slice: string builder wrapper over slice_t

A `str_slice_t` (typedef of `slice_t`) with `element_size = sizeof(char)` for use as a dynamic string/string builder.

### Planned API
- `createStrSlice(size_t initial_len)` — wraps `createSlice(sizeof(char), initial_len)`
- `appendStrSlice(str_slice_t *slice, char c)` — single char append
- `appendStrSliceArr(str_slice_t *slice, char *s)` — bulk append via `strlen` + `memcpy`
- `freeStrSlice(str_slice_t *slice)` — wraps `freeSlice(slice, NULL)` (chars need no individual freeing)

### Open design question
`growSlice` is `static` in `slice.c` so it can't be called from `str_slice.c`.
`appendStrSliceArr` needs capacity for `strlen(s)` chars before it can `memcpy`.
Decide: expose a `reserveSlice(slice_t *, size_t n)` public function, or find another way to ensure capacity from outside `slice.c`.

### Files
New `include/str_slice.h` and `src/str_slice.c`. Remember to add a block in `CMakeLists.txt`.

---

## hash_map: expose stored key pointer on insert/overwrite

When storing owned pointers as values, there is no way to retrieve and free
the old key pointer when overwriting an existing entry. `insertToHashMap`
silently overwrites the value but the caller cannot recover the old key to
free it, causing a memory leak.

Consider adding a variant or out-parameter that returns the displaced
key/value pointers so the caller can free them.
