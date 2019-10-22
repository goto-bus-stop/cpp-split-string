/**
 * cpp-split-string https://github.com/goto-bus-stop/split-string
 * ⓒ 2019 Renée Kooi <renee@kooi.me>
 * License: MIT or Apache-2.0, see https://github.com/goto-bus-stop/split-string#license
 */

#pragma once
#include <string_view>
#include <cstdio>
#include <type_traits>

template <typename CharT> class split_string {
private:
  using value_type = std::basic_string_view<CharT>;

  value_type input_;
  value_type separator_;

public:
  split_string() = delete;
  split_string(value_type input, value_type separator)
      : input_(input), separator_(separator) {}
  template <
      typename SepT,
      typename = /* SepT must be convertible to string_view */
      typename std::enable_if<std::is_convertible_v<SepT, value_type>>::type>
  split_string(value_type input, SepT separator)
      : input_(input), separator_(separator) {}
  split_string(const split_string&) = default;
  ~split_string() = default;

  /// Iterates over the string, line-by-line, starting at the…start
  class iterator {
  public:
    using difference_type = size_t;
    using value_type = std::basic_string_view<CharT>;
    using iterator_category = std::forward_iterator_tag;

    iterator() = delete;
    iterator(value_type input, value_type separator)
        : input_(input), separator_(separator), end_(input_.find(separator_)) {}
    iterator(const iterator&) = default;
    ~iterator() = default;

  private:
    value_type input_;
    value_type separator_;
    typename value_type::size_type end_;

  public:
    inline value_type operator*() {
      return this->input_.substr(0, this->end_);
    }

    inline bool operator==(iterator other) const {
      return this->input_.data() == other.input_.data() &&
             this->input_.size() == other.input_.size() &&
             this->separator_ == other.separator_;
    }
    inline bool operator!=(iterator other) const {
      return this->input_.data() != other.input_.data() ||
             this->input_.size() != other.input_.size() ||
             this->separator_ != other.separator_;
    }

    /// Advance to the next line.
    inline iterator& operator++() {
      if (this->end_ == value_type::npos) {
        this->input_.remove_prefix(this->input_.size());
      } else {
        this->input_.remove_prefix(this->end_ + this->separator_.size());
        this->end_ = this->input_.find(this->separator_);
      }
      return *this;
    }
  };

  inline iterator begin() { return iterator(this->input_, this->separator_); }
  inline iterator end() {
    return iterator(this->input_.substr(this->input_.size()), this->separator_);
  }

  /// Iterates over the string, line-by-line, starting at the end.
  class reverse_iterator {
  public:
    using difference_type = size_t;
    using value_type = std::basic_string_view<CharT>;
    using iterator_category = std::forward_iterator_tag;

    reverse_iterator() = delete;
    reverse_iterator(value_type input, value_type separator)
        : input_(input), separator_(separator), end_(input_.rfind(separator_)) {}
    reverse_iterator(const reverse_iterator&) = default;
    ~reverse_iterator() = default;

  private:
    value_type input_;
    value_type separator_;
    typename value_type::size_type end_;

  public:
    inline value_type operator*() {
      if (this->end_ == value_type::npos) {
        return this->input_;
      }
      return this->input_.substr(this->end_ + this->separator_.size());
    }

    inline bool operator==(reverse_iterator other) const {
      return this->input_.data() == other.input_.data() &&
             this->input_.size() == other.input_.size() &&
             this->separator_ == other.separator_;
    }
    inline bool operator!=(reverse_iterator other) const {
      return this->input_.data() != other.input_.data() ||
             this->input_.size() != other.input_.size() ||
             this->separator_ != other.separator_;
    }

    /// Advance to the previous line.
    inline reverse_iterator& operator++() {
      if (this->end_ == value_type::npos) {
        this->input_.remove_suffix(this->input_.size());
      } else {
        this->input_.remove_suffix(this->end_ + this->separator_.size());
        this->end_ = this->input_.rfind(this->separator_);
      }
      return *this;
    }
  };

  inline reverse_iterator rbegin() {
    return reverse_iterator(this->input_, this->separator_);
  }
  inline reverse_iterator rend() {
    return reverse_iterator(this->input_.substr(0, 0), this->separator_);
  }
};

template <typename CharT> class rsplit_string {
private:
  using value_type = std::basic_string_view<CharT>;
  split_string<CharT> inner_;

public:
  rsplit_string() = delete;
  rsplit_string(value_type input, value_type separator)
      : inner_(input, separator) {}
  template <
      typename SepT,
      typename = /* SepT must be convertible to string_view */
      typename std::enable_if<std::is_convertible_v<SepT, value_type>>::type>
  rsplit_string(value_type input, SepT separator) : inner_(input, separator) {}
  rsplit_string(const rsplit_string&) = default;
  ~rsplit_string() = default;

  using iterator = typename split_string<CharT>::reverse_iterator;
  inline iterator begin() { return inner_.rbegin(); }
  inline iterator end() { return inner_.rend(); }
};
