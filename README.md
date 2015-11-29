[![Build Status](https://travis-ci.org/tonytonyjan/libjaro.svg?branch=master)](https://travis-ci.org/tonytonyjan/libjaro)

# Install

```
autoreconf -i
./configure
make
make install
```

# Usage

```c
#include <stdio.h>
#include <jaro.h>

int main(){
  jaro_winkler_distance("martha",  "marhta"); // 0.9611
  return 0;
}
```