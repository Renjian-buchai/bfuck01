#if !defined(TOKEN_HH_)
#define TOKEN_HH_

#include <string>

#include "../include/enum.hh"

class token {
  const size_t _line;
  const tokenType _type;

 public:
  token(const size_t line, const tokenType type);

  size_t line() const;
  tokenType type() const;

  std::string toStr() const;
};

#endif