// Divide and Conquer DP
//
ll cost(int l, int r) { /* transition cost for l...r (inclusive)*/ }
// dp[i][j] = min_i{0 <= k <= j}(dp[i - 1][k - 1] + cost(k, j))
// condition for it: opt(i, j) <= opt(i, j + 1)
// special case to check: cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c) a <= b <= c <= d 
// computes dp[i][l]...dp[i][r] (inclusive)
void divide_and_conquer(int e, int l, int r, int opt_l, int opt_r) {
  if(l > r) return;
  int mid = (l + r) / 2;
  pair<ll, int> best = {INF, -1};
  for(int k = opt_l; k <= min(opt_r, mid); ++k) {
    ll cur = (k > 0 ? dp[k - 1][e^1] : 0) + cost(k, mid);
    if(cur < best.first) {
      best = {cur, k};
    }
  }
  dp[mid][e] = best.first;
  divide_and_conquer(e, l, mid - 1, opt_l, best.second);
  divide_and_conquer(e, mid + 1, r, best.second, opt_r);
}
for(int i = 0; i < n; ++i) dp[i][0] = cost(0, i); // initial cost
for(int i = 1; i < k; ++i) divide_and_conquer(i % 2, 0, n - 1, 0, n - 1);

// alternativaly, maintain cost function for [opt_l, r] during recursion
ll add(ll cost, ll x) { /* update cost adding element x */ }
ll remove(ll cost, ll x) { /* remove cost removing element x */ }

// maintain cost [opt_l, r]
void divide_and_conquer(int e, int l, int r, int opt_l, int opt_r, ll cost) {
  if(l > r) return;
  int mid = (l + r) / 2;
  pair<ll, int> best = {-INF, 0};
  for(int k = r; k > mid; --k) {
    cost = remove(cost, a[k]);
  } // cost [k, mid]
  for(int k = opt_l; k <= min(opt_r, mid); ++k) {
    int cur = (k > 0 ? dp[e ^ 1][k - 1] : 0) + cost;
    cost = remove(cost, a[k]);
    if(cur > best.first) {
      best = {cur, k};
    }
  } // cost [min(opt_r, mid) + 1, mid]
  dp[e][mid] = best.first;
  for(int k = min(opt_r, mid); k >= opt_l; --k) {
    cost = add(cost, a[k]);
  }
  cost = remove(cost, a[mid]); // cost [opt_l, mid - 1]
  divide_and_conquer(e, l, mid - 1, opt_l, best.second, cost);
  for(int k = mid; k <= r; ++k) {
    cost = add(cost, a[k]);
  }
  for(int k = opt_l; k < best.second; ++k) {
    cost = remove(cost, a[k]);
  }
  // cost [best.second, r]
  divide_and_conquer(e, mid + 1, r, best.second, opt_r, cost);
  for(int k = best.second - 1; k >= opt_l; --k) {
    cost = add(cost, a[k]);
  }  // restore cost to [opt_l, r]
}