# split-string
A simple C++17 class to iterate over pieces of a string using ranged for loops.

It iterates over `string_view` containers only. It could be more generic by accepting iterator pairs, but I don't need it to be, and I don't like dealing with iterator pairs. 🤷🏻

```cpp
#include <split_string.hpp>

int main () {
  for (auto line : split_string("some\nsource\ntext")) {
    std::cout << "line: " << line << '\n';
  }
  // line: some
  // line: source
  // line: text

  for (auto entry : split_string(L"a, b, c", L", ")) {
    std::wcout << "value: " << entry << '\n';
  }
  // value: a
  // value: b
  // value: c
}
```

## Install
Copy [`include/split_string.hpp`](./include/split_string.hpp) into your project or add the repository as a submodule and add `$THIS_REPO/include` to your include path.

Or with CMake do:
```cmake
add_subdirectory(path/to/cpp-split-string)
target_link_directories(your-target PRIVATE split-string)
```

## API
### `auto splitter = split_string(string_view input, string_view separator)`
Create an iterable value for the given input string. `separator` can be anything that `std::is_convertible<>` to a `string_view.`

This is a templated function that will accept any kind of `std::basic_string_view<CharT>`. The `separator` and `input` must use the same character type. Use `auto` to avoid naming the return type. The full signature is:

```cpp
template<typename CharT>
split_string(std::basic_string_view<CharT> input, std::basic_string_view<CharT> separator);

template<typename CharT, typename SepT, typename = typename std::enable_if<
  std::is_convertible_v<SepT, value_type>>::type>
split_string(std::basic_string_view<CharT> input, SepT separator);
```

### `split_string<CharT>::iterator begin = splitter.begin()`
Get the iterator for the first character in the string.

### `split_string<CharT>::iterator end = splitter.end()`
Get the iterator for the end of the string.

### `split_string<CharT>::reverse_iterator begin = splitter.rbegin()`
Get the reverse iterator for the entire remaining string.

### `split_string<CharT>::reverse_iterator end = splitter.rend()`
Get the reverse iterator for the start of the string.

### `auto reverse_splitter = rsplit_string(string_view input, string_view separator)`
Create an iterable value that proxies its `begin()` and `end()` calls to the reverse iterator of `split_string`.

This way you can do reverse iteration in a ranged for loop, and not fiddle around with `rbegin()` and `rend()`:
```cpp
for (auto line : rsplit_string("some\nsource\ntext")) {
  std::cout << "line: " << line << '\n';
}
// line: text
// line: source
// line: some
```

### `split_string<AnyT>::reverse_iterator begin = reverse_splitter.begin()`
Get the reverse iterator for the entire remaining string.

### `split_string<AnyT>::reverse_iterator end = reverse_splitter.end()`
Get the reverse iterator for the start of the string.

## License
[MIT](./LICENSE-MIT.md) or [Apache-2.0](./LICENSE-Apache.md) at your option.
