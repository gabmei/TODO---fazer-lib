// Minkowski Sum
//
// Given two convex polygons, calculate the convex polygon represented by their sum
// a_i in poly A, b_j in poly B then a_i + b_j in poly A+B
template<typename T>
void reorder_polygon(vector<Point<T>>& P){
  size_t pos = 0;
  for(size_t i = 1; i < P.size(); i++){
    if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) {
      pos = i;
    }
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}
// points ordered ccw
template<typename T>
vector<Point<T>> minkowski(vector<Point<T>> P, vector<Point<T>> Q){
  // the first vertex must be the lowest
  reorder_polygon(P);
  reorder_polygon(Q);
  // we must ensure cyclic indexing
  P.push_back(P[0]);
  P.push_back(P[1]);
  Q.push_back(Q[0]);
  Q.push_back(Q[1]);
  vector<Point<T>> result;
  for(size_t i = 0, j = 0; i < P.size() - 2 || j < Q.size() - 2; ){
    result.push_back(P[i] + Q[j]);
    auto c = cross(P[i + 1] - P[i], Q[j + 1] - Q[j]);
    if(c >= T(0) && i < P.size() - 2) {
      ++i;
    }
    if(c <= T(0) && j < Q.size() - 2) {
      ++j;
    }
  }
  return result;
}