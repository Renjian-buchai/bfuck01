#include "../include/tree.hh"

unary::unary(token token) : _token(token) {}

scope::scope(scope* prev) : inScope({}), _prev(prev) {}
// scope::scope(const scope& scope) : inScope({}), _prev(nullptr) { (void)scope;
// }

// scope& scope::operator=(const scope& _scope) {
//   _prev = _scope._prev;
//   // inScope = _scope.inScope;
//   return *this;
// }