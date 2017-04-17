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

#include <sqlpp17/clause_fwd.h>
#include <sqlpp17/detail/insert_column_printer.h>
#include <sqlpp17/detail/insert_value_printer.h>
#include <sqlpp17/type_traits.h>
#include <sqlpp17/wrapped_static_assert.h>

namespace sqlpp
{
  namespace clause
  {
    struct insert_values
    {
    };
  }

  template <typename... Assignments>
  struct insert_values_t
  {
    std::tuple<Assignments...> _assignments;
  };

  template <typename... Assignments>
  constexpr auto clause_tag<insert_values_t<Assignments...>> = clause::insert_values{};

  template <typename Statement, typename... Assignments>
  class clause_base<insert_values_t<Assignments...>, Statement>
  {
  public:
    template <typename OtherStatement>
    clause_base(const clause_base<insert_values_t<Assignments...>, OtherStatement>& s) : _assignments(s._assignments)
    {
    }

    clause_base(const insert_values_t<Assignments...>& f) : _assignments(f._assignments)
    {
    }

    std::tuple<Assignments...> _assignments;
  };

  template <typename Context, typename Statement, typename... Assignments>
  decltype(auto) operator<<(Context& context, const clause_base<insert_values_t<Assignments...>, Statement>& t)
  {
    // columns
    {
      context << " (";
      auto print = detail::insert_column_printer(context);
      (..., print(std::get<Assignments>(t._assignments)));
      context << ")";
    }

    // values
    {
      context << " VALUES (";
      auto print = detail::insert_value_printer(context);
      (..., print(std::get<Assignments>(t._assignments)));
      context << ')';
    }

    return context;
  }
}
