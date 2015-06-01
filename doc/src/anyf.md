# anyf

## Synopsis

```cpp
template <class P>
struct anyf;
```

This is a [parser combinator](parser_combinator.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`P`</td>
    <td>[parser](parser.html)</td>
  </tr>
</table>

## Description

The same as [`any`](any.html), but once `P` rejects the input, `anyf`
checks if `P` consumes any characters before rejecting the input. If so,
`anyf` rejects the input with the same error message this last application of
`P` returned. Otherwise `anyf` accepts the input and gives the same result as
[`any`](any.html).

Here is a diagram showing how `anyf` works by example:

```cpp
using int_token = token<int_>;
using plus_token = token<lit_c<'+'>>;
using plus_int = last_of<plus_token, int_token>;
using sum_op = mpl::lambda<mpl::plus<mpl::_1, mpl::_2>>::type;
```

<p align="center">
  <a href="anyf_diag1.png"><img src="anyf_diag1.png" style="width:70%" /></a>
</p>

## Header

```cpp
#include <boost/metaparse/anyf.hpp>
```

## Expression semantics

For any `p` parser, `s` compile-time string and `pos` source position

```cpp
anyf<p>::apply<s, pos>
```

is equivalent to

```cpp
first_of<any<p>, fail_at_first_char_expected<p> >::apply<s, pos>
```

## Example

```cpp
#include <boost/metaparse/anyf.hpp>
#include <boost/metaparse/lit_c.hpp>
#include <boost/metaparse/last_of.hpp>
#include <boost/metaparse/token.hpp>
#include <boost/metaparse/int_.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/get_result.hpp>
#include <boost/metaparse/is_error.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector_c.hpp>

using namespace boost::metaparse;

using int_token = token<int_>;
using plus_token = token<lit_c<'+'>>;
using plus_int = last_of<plus_token, int_token>;

using ints = anyf<plus_int>;

static_assert(
  boost::mpl::equal<
    boost::mpl::vector_c<int, 13, 3, 21>,
    get_result<
      ints::apply<BOOST_STRING("+ 13 + 3 + 21"), start>
    >::type
  >::type::value,
  "ints should parse the numbers"
);

static_assert(
  is_error<ints::apply<BOOST_STRING("+ 13 + 3 +"), start>>::type::value,
  "when the last number is missing, it should be an error"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

