#pragma once

/*
Copyright (c) 2016, Roland Bock
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <tuple>
#include <sqlpp17/clause_fwd.h>
#include <sqlpp17/detail/list_printer.h>
#include <sqlpp17/type_traits.h>
#include <sqlpp17/wrapped_static_assert.h>

namespace sqlpp
{
  namespace clause
  {
    struct update_set
    {
    };
  }

  template <typename... Assignments>
  struct update_set_t
  {
    std::tuple<Assignments...> _assignments;
  };

  template <typename... Assignments>
  constexpr auto clause_tag<update_set_t<Assignments...>> = clause::update_set{};

  template <typename... Assignments, typename Statement>
  class clause_base<update_set_t<Assignments...>, Statement>
  {
  public:
    template <typename OtherStatement>
    clause_base(const clause_base<update_set_t<Assignments...>, OtherStatement>& s) : _assignments(s._assignments)
    {
    }

    clause_base(const update_set_t<Assignments...>& f) : _assignments(f._assignments)
    {
    }

    std::tuple<Assignments...> _assignments;
  };

#warning : It would be nice to have a noop here in case everything is optional and not to be used

  template <typename Context, typename... Assignments, typename Statement>
  decltype(auto) operator<<(Context& context, const clause_base<update_set_t<Assignments...>, Statement>& t)
  {
    auto print = detail::list_printer<Context>{context, ", "};
    context << " SET ";
    (..., print(std::get<Assignments>(t._assignments)));
    return context;
  }
}
