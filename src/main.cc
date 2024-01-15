#include <cstdint>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <variant>
#include <vector>

enum class tokenType : uint8_t {
  INC,
  DEC,
  LEFT,
  RIGHT,
  OUT,
  IN,
  LOOP,
  ENDLOOP
};

class token {
  const size_t _line;
  const tokenType _type;

 public:
  token(const size_t line, const tokenType type) : _line(line), _type(type) {}

  size_t line() const { return _line; }
  tokenType type() const { return _type; }

  std::string toStr() {
    return "Line: " + std::to_string(_line) +
           ", Type: " + std::to_string(static_cast<uint8_t>(_type));
  }
};

int main(int argc, const char** argv) {
  if (argc != 2) {
    return 1;
  }
  std::string buffer;

  std::ifstream file{1 [argv]};

  std::string source = "";
  while (std::getline(file, buffer)) {
    source += buffer + "\n";
  }

  std::vector<token> tokens;
  {
    size_t line = 1;
    for (auto it = source.begin(); it != source.end(); ++it) {
      switch (*it) {
        case '\n':
          ++line;
          break;

        case '+':
          tokens.push_back({line, tokenType::INC});
          break;

        case '-':
          tokens.push_back({line, tokenType::DEC});
          break;

        case '<':
          tokens.push_back({line, tokenType::LEFT});
          break;

        case '>':
          tokens.push_back({line, tokenType::RIGHT});
          break;

        case '.':
          tokens.push_back({line, tokenType::OUT});
          break;

        case ',':
          tokens.push_back({line, tokenType::IN});
          break;

        case '[':
          tokens.push_back({line, tokenType::LOOP});
          break;

        case ']':
          tokens.push_back({line, tokenType::ENDLOOP});
          break;

        default:
          break;
      }
    }
  }

  // Scoping checks
  {
    size_t counter = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
      if (tokens[i].type() == tokenType::LOOP) {
        ++counter;
      }
      if (tokens[i].type() == tokenType::ENDLOOP) {
        --counter;
      }
    }
    if (counter != 0) {
      std::cerr << "Scope mismatch.\n";
      if (counter > 0)
        std::cout << "There are " << counter
                  << " more loopstarts than loopends";
      else
        std::cout << "There are " << -counter
                  << " more loopends than loopstarts";
      return 1;
    }
  }

  for (auto token : tokens) {
    std::cout << "{" << token.toStr() << "}\n";
  }

  return 0;
}
