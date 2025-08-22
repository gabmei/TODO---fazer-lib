// Primitive Root
//
const uint32_t MOD = (119 << 23) + 1;
using Mint = Mod<MOD>;
// r is a primitive root mod M iff r^k == a mod M for every a gcd(M, a) = 1 there exists k
bool primitive_root(int r) {
  int m = MOD - 1;
  for(int i = 2; i * i <= m; ++i) {
    if(m % i == 0) {
      if(bin_exp(Mint(r), i) == 1) return false;
      if(bin_exp(Mint(r), m / i) == 1) return false;
    }
  }
  return true;
}
