#ifndef BOOST_METAPARSE_V2_ACCEPT_WHEN_HPP
#define BOOST_METAPARSE_V2_ACCEPT_WHEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Pred, class Msg>
      struct accept_when
      {
      private:
        struct unchecked
        {
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename boost::mpl::apply<
                Pred,
                typename get_result<boost::mpl::apply<P, S, Pos> >::type
              >::type,
              boost::mpl::apply<P, S, Pos>,
              reject<Msg, Pos>
            >
          {};
        };
      public:
        typedef accept_when type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::apply<
            typename boost::mpl::if_<
              is_error<boost::mpl::apply<P, S, Pos> >,
              P,
              unchecked
            >::type,
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif

