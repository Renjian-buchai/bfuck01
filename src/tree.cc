#include "../include/tree.hh"

unary::unary(token token) : _token(token) {}

scope::scope(scope* prev) : _prev(prev) {}
scope::scope(const scope& scope) { (void)scope; }

scope& scope::operator=(const scope& _scope) {
  (void)_scope;
  return *this;
}