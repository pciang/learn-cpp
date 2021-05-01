#include <iostream>

#include "lzw.h"

int main() {
  int dict_maxsz  = 1 << 16;
  int dict_maxidx = dict_maxsz - 1;

  std::unordered_map<Bytes, int> dict(dict_maxsz);
  build_onebidx(dict);

  int nextidx = dict.size();

  Bytes w, wk;
  {
    char c;
    if (!std::cin.eof()) {
      std::cin.read(&c, 1);
      w += c;
    }
  }

  char buffer[1024];
  while (!std::cin.eof()) {
    int bufsz = std::cin
      .read(buffer, sizeof buffer)
      .gcount();

    for (int i = 0; i < bufsz; ++i) {
      wk = w + buffer[i];
      if (dict.end() == dict.find(wk)) {
        dict[wk] = nextidx++;
        printf("%d\n", dict[w]);
        w = buffer[i];
      } else {
        std::swap(w, wk);
      }
    }
  }
  printf("%d\n", dict[w]);

  return 0;
}
