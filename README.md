# LZW Algorithm

Read more [here](https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch)

```bash
cd lzw-example

make clean && make

./lzw < lzw.cpp | ./uncompress > output.txt

# shouldn't show any difference
diff lzw.cpp output.txt
```
