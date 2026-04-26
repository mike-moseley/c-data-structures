# TODO

## hash_map: expose stored key pointer on insert/overwrite

When storing owned pointers as values, there is no way to retrieve and free
the old key pointer when overwriting an existing entry. `insertToHashMap`
silently overwrites the value but the caller cannot recover the old key to
free it, causing a memory leak.

Consider adding a variant or out-parameter that returns the displaced
key/value pointers so the caller can free them.
