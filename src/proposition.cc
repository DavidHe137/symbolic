/**
 * proposition.cc
 *
 * Copyright 2018. All Rights Reserved.
 *
 * Created: November 28, 2018
 * Authors: Toki Migimatsu
 */

#include "symbolic/proposition.h"

#include <sstream>  // std::stringstream

namespace symbolic {



std::string PropositionBase::to_string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const symbolic::PropositionBase& P) {
  os << P.name() << "(";
  std::string separator;
  for (const Object& arg : P.arguments()) {
    os << separator << arg;
    if (separator.empty()) separator = ", ";
  }
  os << ")";
  return os;
}

}  // namespace symbolic

namespace std {

size_t hash<symbolic::PropositionBase>::operator()(
    const symbolic::PropositionBase& prop) const noexcept {
  size_t seed = hash<string>{}(prop.name());
  for (const symbolic::Object& arg : prop.arguments()) {
    seed ^= hash<string>{}(arg.name()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

};  // namespace std
