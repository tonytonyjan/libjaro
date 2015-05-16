# Install

```
mkdir build
cd build
cmake ..
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