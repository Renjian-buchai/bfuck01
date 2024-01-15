#if !defined(TREE_HH_)
#define TREE_HH_

#include <variant>
#include <vector>

#include "../include/enum.hh"
#include "../include/token.hh"

struct scope;
struct unary;
using expr = std::variant<scope, unary>;

struct scope {
  std::vector<expr> inScope{};
  std::vector<expr>* _prev = nullptr;

  scope(std::vector<expr>* prev);
  scope(const scope& scope);
  scope& operator=(const scope& scope);
};

struct unary {
  token _token;
  unary(token token);
};

#endif