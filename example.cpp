#include <split_string.hpp>
#include <iostream>

int main () {
  std::cout << "split on \\n\n";
  {
    std::wstring_view input = L"abc\ndef\nghi\njkl";
    for (auto line : split_string(input, L"\n")) {
      std::wcout << "line: " << line << '\n';
    }
  }

  std::cout << "\nreverse iterating, split on \\r\\n\n";
  {
    std::string_view input = "abc\ndef\r\nghi\njkl";
    for (auto line : rsplit_string(input, "\r\n")) {
      std::cout << "line: " << line << '\n';
    }
  }
}
