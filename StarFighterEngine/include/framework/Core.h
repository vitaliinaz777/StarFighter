#include <stdio.h>

namespace st
{

//a macro
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

}