#include <cstdint>
#include <fstream>
#include <string>
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
 public:
  const size_t _line;
  const tokenType _type;

  token(const size_t line, const tokenType type) : _line(line), _type(type) {}

  size_t line() const { return _line; }
  tokenType _type() const { return _type; }

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
    source += buffer;
  }

  std::vector<token> tokens;
  {
    size_t line;
    for (auto it = source.begin(); it != source.end(); ++it) {
      switch (*it) {
        case '\n':
          line++;
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

  return 0;
}
