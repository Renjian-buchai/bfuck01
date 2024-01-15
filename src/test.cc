#include <utility>
#include <variant>
#include <vector>

struct unary {
  int _token;
  unary(int token) : _token(token) {}
};

struct scope {
  std::vector<std::variant<scope, unary>> inScope{};
  std::vector<std::variant<scope, unary>>* _prev = nullptr;

  scope() = delete;
  scope(std::vector<std::variant<scope, unary>>* prev) : _prev(prev) {}
  scope(const scope& scope) { this->operator=(scope); }

  scope& operator=(const scope& _scope) {
    _prev = _scope._prev;
    inScope = std::move(_scope.inScope);
    return *this;
  }
};

int main() {
  scope x{nullptr};
  scope y = x;
}