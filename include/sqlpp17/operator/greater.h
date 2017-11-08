#pragma once

/*
Copyright (c) 2017, Roland Bock
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

#include <type_traits>
#include <sqlpp17/operator_fwd.h>

namespace sqlpp
{
  template <typename L, typename R>
  struct greater_t
  {
    L l;
    R r;
  };

  template <typename L, typename R>
  constexpr auto operator>(L l, R r) -> std::enable_if_t<are_value_types_comparable_v<L, R>, greater_t<L, R>>
  {
    return greater_t<L, R>{l, r};
  }

  template <typename L, typename R>
  constexpr auto is_expression_v<greater_t<L, R>> = true;

  template <typename L, typename R>
  struct value_type_of<greater_t<L, R>>
  {
    using type = bool;
  };

  template <typename L, typename R>
  constexpr auto requires_braces_v<greater_t<L, R>> = true;

  template <typename Context, typename L, typename R>
  constexpr decltype(auto) operator<<(Context& context, const greater_t<L, R>& t)
  {
    return context << embrace(t.l) << " = " << embrace(t.r);
  }
}  // namespace sqlpp
