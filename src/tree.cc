#include "../include/tree.hh"

unary::unary(token token) : _token(token) {}

scope::scope(std::vector<expr>* prev) : _prev(prev) {}
scope::scope(const scope& scope) { this->operator=(scope); }

scope& scope::operator=(const scope& scope) {
  _prev = scope._prev;
  inScope = std::move(scope.inScope);
}