#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <variant>
#include <vector>

#include "../include/enum.hh"
#include "../include/token.hh"
#include "../include/tree.hh"

int32_t recurse(scope* currScope, size_t& turindex,
                std::vector<int32_t>& turing) {
  using expr = std::variant<scope, unary>;
  std::string buffer;
  for (expr expr : currScope->inScope) {
    if (std::holds_alternative<unary>(expr)) {
      switch (std::get<unary>(expr)._token.type()) {
        case tokenType::INC:
          ++(turing[turindex]);
          break;

        case tokenType::DEC:
          --(turing[turindex]);
          break;

        case tokenType::RIGHT:
          if (turindex >= turing.size() - 1) {
            turing.push_back(0);
          }
          ++turindex;
          break;

        case tokenType::LEFT:
          if (turindex == 0) {
            turing.insert(turing.begin(), 0);
          } else {
            --turindex;
          }
          break;

        case tokenType::OUT:
          std::cout << static_cast<uint8_t>(turing[turindex]);
          // std::cout << static_cast<uint8_t>(0xCC);
          break;

        case tokenType::IN:
          std::getline(std::cin, buffer);
          turing[turindex] = buffer[0];
          std::cin.ignore(std::numeric_limits<std::streamsize>::max());
          break;

        default:
          std::cerr << "Wtf\n"
                       "Terminating due to unexpected token";
          break;
      }
      continue;
    } else {
      if (turing[turindex] == 0) {
        continue;
      }
      while (recurse(&std::get<scope>(expr), turindex, turing)) (void)0;
    }
  }
  return turing[turindex];
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
    for (size_t i = 0; i < tokens.size(); (void)++i) {
      if (tokens[i].type() == tokenType::LOOP) {
        (void)++counter;
      }
      if (tokens[i].type() == tokenType::ENDLOOP) {
        (void)--counter;
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

  scope global{nullptr};
  {
    scope* currScope = &global;

    for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end();
         ++it) {
      switch (it->type()) {
        case tokenType::LOOP:
          currScope->inScope.push_back(scope(currScope));
          currScope = std::get_if<scope>(&*currScope->inScope.rbegin());
          break;

        case tokenType::ENDLOOP:
          if (currScope->_prev) {
            currScope = currScope->_prev;
          } else {
            std::cerr << "End of Uninitiated loop on line: " << it->line();
          }
          break;

        default:
          currScope->inScope.push_back(unary{*it});
          break;
      }
    }
  }

  std::vector<int32_t> turing{0};

  {
    scope* currScope = &global;
    size_t turindex = 0;

    (void)recurse(currScope, turindex, turing);
  }

  return 0;
}
