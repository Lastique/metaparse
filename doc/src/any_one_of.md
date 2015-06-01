# any_one_of

## Synopsis

```cpp
template <class P1, class P2, /* ... */, class Pn>
struct any_one_of1;
```

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`P1` .. `Pn`</td>
    <td>[parser](parser.html)s</td>
  </tr>
</table>

This is a [parser combinator](parser_combinator.html).

## Description

It applies the `P1` ... `Pn` parsers repeatedly as long as any of them accepts
the input. In each iteration the parsers are tried in order and the first one
accepting the input is used. The result is a sequence of the individual parsing
results.

When none of the `P1` ... `Pn` parsers accept the input in the first iteration,
`any_one_of` accepts the input and the result of parsing is an empty sequence.

The maximum number of accepted parsers is defined by the
`BOOST_LIMIT_ONE_OF_SIZE` macro. Its default value is 20.

## Header

```cpp
#include <boost/metaparse/any_one_of.hpp>
```

## Expression semantics

For any `p1`, ..., `pn` parsers

```cpp
any_one_of<p1, /* ... */, pn>
```

is equivalent to

```cpp
any<one_of<p1, /* ... */, pn>>
```

## Example

```cpp
#include <boost/metaparse/any_one_of.hpp>
#include <boost/metaparse/lit_c.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/get_result.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/char.hpp>

using namespace boost::metaparse;

using as_and_bs = any_one_of<lit_c<'a'>, lit_c<'b'>>;

static_assert(
  boost::mpl::equal<
    get_result<as_and_bs::apply<BOOST_STRING("abaab"), start>>::type,
    boost::mpl::vector<
      boost::mpl::char_<'a'>,
      boost::mpl::char_<'b'>,
      boost::mpl::char_<'a'>,
      boost::mpl::char_<'a'>,
      boost::mpl::char_<'b'>
    >
  >::type::value,
  "the result of parsing should be the list of results"
);

static_assert(
  boost::mpl::equal<
    get_result<as_and_bs::apply<BOOST_STRING("x"), start>>::type,
    boost::mpl::vector<>
  >::type::value,
  "any_one_of should accept the input when it"
  " can't parse anything with digit_val"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


