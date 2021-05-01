#include "lzw.h"

void print(const Bytes &b) {
  for (char c: b.bytes) {
    printf("%c", c);
  }
}

int main() {
  int dict_maxsz  = 1 << 16;
  int dict_maxidx = dict_maxsz - 1;

  std::unordered_map<Bytes, int> dict(dict_maxsz);
  build_onebidx(dict);

  int nextidx = dict.size();

  std::unordered_map<int, std::unordered_map<Bytes, int>::const_iterator> lookup;
  for (int i = 0; i < 256; ++i) {
    lookup[i] = dict.find(i);
  }

  Bytes w, wk;
  int code;
  if (scanf("%d", &code) != EOF) {
    printf("%c", code);
    w = code;
  }

  while (scanf("%d", &code) != EOF) {
    if (lookup.end() == lookup.find(code)) {
      wk = w + w.bytes[0];
      print(wk);
      lookup[nextidx++] = dict.insert_or_assign(dict.end(), wk, nextidx);
      std::swap(w, wk);
    } else {
      const Bytes& entry = lookup[code]->first;
      print(entry);
      wk = w + entry.bytes[0];
      if (dict.end() == dict.find(wk)) {
        lookup[nextidx++] = dict.insert_or_assign(dict.end(), wk, nextidx);
      }
      w = entry;
    }
  }

  return 0;
}
