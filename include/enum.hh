#if !defined(ENUM_HH_)
#define ENUM_HH_

#include <cstdint>

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
#endif