#include "../include/token.hh"

token::token(const size_t line, const tokenType type)
    : _line(line), _type(type) {}

size_t token::line() const { return _line; }
tokenType token::type() const { return _type; }

std::string token::toStr() const {
  return "Line: " + std::to_string(_line) +
         ", Type: " + std::to_string(static_cast<uint8_t>(_type));
}