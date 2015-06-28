# change_error_message

## Synopsis

```cpp
template <class P, class Msg>
struct change_error_message;
```

This is a [parser combinator](parser_combinator.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`P`</td>
    <td>[parser](parser.html)</td>
  </tr>
  <tr>
    <td>`Msg`</td>
    <td>[parsing error message](parsing_error_message.html)</td>
  </tr>
</table>

## Description

It applies `P` on the input. When `P` succeeds, `change_error_message` returns
the result `P` returns, otherwise `change_error_message` rejects the input and
the reson will be `Msg`.

## Header

```cpp
#include <boost/metaparse/change_error_message.hpp>
```

## Expression semantics

For any `p` parser and `m` parsing error message, `s` compile-time string and
`pos` source position

```cpp
change_error_message<p, msg>::apply<s, pos>
```

is equivalent to `p::apply<s, pos>` when `p` accepts the input.
It is equivalent to `fail<msg>::apply<s, pos>` otherwise.

## Example

```cpp
#include <boost/metaparse/change_error_message.hpp>
#include <boost/metaparse/any1.hpp>
#include <boost/metaparse/letter.hpp>
#include <boost/metaparse/keyword.hpp>
#include <boost/metaparse/last_of.hpp>
#include <boost/metaparse/token.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/get_message.hpp>
#include <boost/metaparse/define_error.hpp>

#include <type_traits>

using namespace boost::metaparse;

BOOST_METAPARSE_DEFINE_ERROR(name_expected, "Name expected");

using keyword_name = token<keyword<BOOST_STRING("name")>>;
using name_token = token<any1<letter>>;

using name_parser =
  last_of<keyword_name, change_error_message<name_token, name_expected>>;

static_assert(
  !is_error<name_parser::apply<BOOST_STRING("name Bela"), start>>::type::value,
  "name_parser should accept \"name <a name>\""
);

static_assert(
  is_error<name_parser::apply<BOOST_STRING("name ?"), start>>::type::value,
  "name_parser should reject input when name is a question mark"
);

static_assert(
  std::is_same<
    get_message<name_parser::apply<BOOST_STRING("name ?"), start>>::type,
    name_expected
  >::type::value,
  "the error message should be the one specified by change_error_message"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

