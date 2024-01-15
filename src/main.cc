#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "../include/enum.hh"
#include "../include/token.hh"
#include "../include/tree.hh"

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

  using expr = std::variant<scope, unary>;
  std::vector<expr> tree{};
  std::vector<expr>* currScope = &tree;

  for (auto it = tokens.begin(); it != tokens.end(); ++it) {
    if (it->type() != tokenType::LOOP) {
      currScope->push_back(unary{*it});
    }

    if (it->type() == tokenType::LOOP) {
      currScope->push_back(scope{currScope});
      currScope = &(std::get_if<scope>(&*currScope->rbegin())->inScope);
    }
  }

  return 0;
}
