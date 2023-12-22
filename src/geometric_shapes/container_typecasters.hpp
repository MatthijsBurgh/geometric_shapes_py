#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <boost/variant.hpp>

namespace pybind11
{
namespace detail
{

// `boost::variant` as an example -- can be any `std::variant`-like container
template <typename... Ts>
struct type_caster<boost::variant<Ts...>> : variant_caster<boost::variant<Ts...>>
{
};

// Specifies the function used to visit the variant -- `apply_visitor` instead of `visit`
template <>
struct visit_helper<boost::variant>
{
  template <typename... Args>
  static auto call(Args&&... args) -> decltype(boost::apply_visitor(args...))
  {
    return boost::apply_visitor(args...);
  }
};

}  // namespace detail
}  // namespace pybind11
