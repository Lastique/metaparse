# boost::metaparse performance

Parsers work at compile-time, thus their performance affects compilation speed.
This section shows measurements of compilation time using Metaparse. The
measurements were done on a Linux laptop with an 1.6 GHz Atom processor and 1 GB
memory. The measurements were done using GCC 4.6.1 with `-std=c++0x` and no
optimalisation. Compilation speed was measured using the `time` utility.

To measure a non-trivial parser, the `printf` example program were used for
measurements. Here is a list of the `printf` calls and their compilation speed
(`user` output of `time`):

<table cellpadding='0' cellspacing='0'>
  <tr>
    <th>type-safe `printf` call</th>
    <th style='text-align:center'>Compilation speed (s)</th>
  </tr>
  <tr>
    <td>No compile-time parsing (just the includes and an empty `main`)</td>
    <td style='text-align:center'>3.51</td>
  </tr>
  <tr>
    <td>`printf<BOOST_METAPARSE_STRING("%f")>(1.0)`</td>
    <td style='text-align:center'>4.95</td>
  </tr>
  <tr>
    <td>`printf<BOOST_METAPARSE_STRING("%f%f")>(1.0, 2.0)`</td>
    <td style='text-align:center'>5.26</td>
  </tr>
  <tr>
    <td>`printf<BOOST_METAPARSE_STRING("%f%f%f")>(1.0, 2.0, 3.0)`</td>
    <td style='text-align:center'>5.50</td>
  </tr>
  <tr>
    <td>`printf<BOOST_METAPARSE_STRING("%f%f%f%f")>(1.0, 2.0, 3.0, 4.0)`</td>
    <td style='text-align:center'>5.82</td>
  </tr>
  <tr>
    <td>`printf<BOOST_METAPARSE_STRING("%f%f%f%f%f")>(1.0, 2.0, 3.0, 4.0, 5.0)`</td>
    <td style='text-align:center'>6.07</td>
  </tr>
</table>

Further measurements can be found in the following paper:

Zoltán Porkoláb, Ábel Sinkovics: <br />
*Domain-specific Language Integration with Compile-time Parser Generator
Library* <br />
In Eelco Visser, Jaakko Järvi, editors, Proceedings of the ninth
international conference on Generative programming and component
engineering (GPCE 2010). ACM, October 2010, pp. 137-146.


<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](index.html)

