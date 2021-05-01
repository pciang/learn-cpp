#include <unordered_map>
#include <vector>

struct Bytes {
  std::vector<unsigned char> bytes;

  Bytes() {
    bytes.reserve(4);
  }
  Bytes(const char c) {
    bytes.reserve(4);
    bytes.push_back(c);
  }
  Bytes(const Bytes& other): bytes(other.bytes) {}

  Bytes operator+(const char c) const {
    Bytes result(*this);
    result.bytes.push_back(c);
    return result;
  }

  Bytes& operator+=(const char c) {
    this->bytes.push_back(c);
    return *this;
  }

  bool operator==(const Bytes& other) const {
    return bytes == other.bytes;
  }
};

namespace std {
  template<> struct hash<Bytes> {
    std::size_t operator()(const Bytes& b) const {
      std::size_t
        result = 0UL,
        mask = 0x00000000000000ffUL;
      for (int i = 0, n = b.bytes.size(), rot, antirot; i < n; ++i) {
        rot = (i * 8) & 0x3f;
        result = (result & ~(mask << rot)) ^ ((mask << rot) & (std::size_t(b.bytes[i]) << rot));
      }
      return result;
    }
  };
}

void build_onebidx(std::unordered_map<Bytes, int> &dict) {
  dict.clear();
  for (unsigned char c = 0; ; ++c) {
    dict[c] = c;
    if (c == 255) {
      break;
    }
  }
}
