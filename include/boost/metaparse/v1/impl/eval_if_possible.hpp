#ifndef BOOST_METAPARSE_V2_IMPL_EVAL_IF_POSSIBLE_HPP
#define BOOST_METAPARSE_V2_IMPL_EVAL_IF_POSSIBLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/has_type.hpp>
#include <boost/metaparse/v1/impl/returns.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class T>
        struct eval_if_possible :
          boost::mpl::eval_if<typename has_type<T>::type, T, returns<T> >
        {};
      }
    }
  }
}

#endif

