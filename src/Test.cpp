#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

constexpr double TIME_LIMIT = 9800;
constexpr int MAX_S = 1 << 9;
constexpr int MAX_SS = MAX_S * MAX_S;
int S;
char M[MAX_SS];

double get_time() {
  unsigned long long a, d;
  __asm__ volatile("rdtsc" : "=a"(a), "=d"(d));
  return (d << 32 | a) / 2800000.0;
}

unsigned get_random() {
  static unsigned y = 2463534242;
  return y ^= (y ^= (y ^= y << 13) >> 17) << 5;
}

double get_random_double() { return (double)get_random() / UINT_MAX; }

inline int to(int x, int y) { return (x << 9) + y; }

inline bool in(int p) {
  int x = p >> 9;
  int y = p & (MAX_S - 1);
  return 0 <= x && x < S && 0 <= y && y < S;
}

struct Cell {
  char v;
  bool o;

  void value(int p) {
    v = 0;
    if (o) {
      auto check = [&](int p) { if (in(p)) v += M[p] < 0 ? 1 : -1; };
      check(p + MAX_S + 2);
      check(p + MAX_S - 2);
      check(p - MAX_S + 2);
      check(p - MAX_S - 2);
      check(p + 2 * MAX_S + 1);
      check(p + 2 * MAX_S - 1);
      check(p - 2 * MAX_S + 1);
      check(p - 2 * MAX_S - 1);
    } else {
      auto check = [&](int p) { if (in(p)) v += M[p] > 0 ? 1 : -1; };
      check(p + MAX_S + 2);
      check(p + MAX_S - 2);
      check(p - MAX_S + 2);
      check(p - MAX_S - 2);
      check(p + 2 * MAX_S + 1);
      check(p + 2 * MAX_S - 1);
      check(p - 2 * MAX_S + 1);
      check(p - 2 * MAX_S - 1);
    }
  }
};

Cell cell[MAX_SS];

template <int t, typename Check, typename In>
void change(int p, Check check, In in) {
  cell[p].o = !cell[p].o;
  cell[p].v = -cell[p].v;
  int x, v;
  x = p + MAX_S + 2;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p + MAX_S - 2;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p - MAX_S + 2;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p - MAX_S - 2;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p + 2 * MAX_S + 1;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
    }
  }
  x = p + 2 * MAX_S - 1;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p - 2 * MAX_S + 1;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
  x = p - 2 * MAX_S - 1;
  if (in(x)) {
    M[x] += t;
    if (M[x] == t || M[x] == 0) {
      v = M[x] - t;
      check(x + MAX_S + 2, v, M[x]);
      check(x + MAX_S - 2, v, M[x]);
      check(x - MAX_S + 2, v, M[x]);
      check(x - MAX_S - 2, v, M[x]);
      check(x + 2 * MAX_S - 1, v, M[x]);
      check(x - 2 * MAX_S + 1, v, M[x]);
      check(x - 2 * MAX_S - 1, v, M[x]);
    }
  }
}
template <typename Check, typename In>
inline void change(int p, Check check, In in) {
  if (cell[p].o) {
    change<1>(p, check, in);
  } else {
    change<-1>(p, check, in);
  }
}

void change(int p) {
  auto check_ = [](int n, int a, int b) {
    if (cell[n].o) {
      cell[n].v += (a < 0 ? -1 : 1) + (b < 0 ? 1 : -1);
    } else {
      cell[n].v += (a > 0 ? -1 : 1) + (b > 0 ? 1 : -1);
    }
  };
  auto check = [&](int n, int a, int b) {
    if (in(n)) check_(n, a, b);
  };
  int x = p >> 9;
  int y = p & (MAX_S - 1);
  auto a = [](int x){return true;};
  auto b = [](int x){return in(x);};
  if (4 <= x && x < S - 4 && 4 <= y && y < S - 4) {
    change(p, check_, a);
  } else if (2 <= x && x < S - 2 && 2 <= y && y < S - 2) {
    change(p, check,  a);
  } else {
    change(p, check,  b);
  }
}

class KnightsAttacks {
 public:
  vector<string> placeKnights(vector<string> board) {
    const double start = get_time();
    const double end = start + TIME_LIMIT;
    S = board.size();
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        M[to(i, j)] = board[i][j] - '0';
      }
    }
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        int p = to(i, j);
        cell[p].o = false;
        cell[p].value(p);
      }
    }
    constexpr int batch = 10;
    constexpr int ln = 1 << 12;
    int log_[ln];
    for (int i = 0; i < ln; ++i) {
      log_[i] = -0.6 / batch * (1 << 28) * log((i + 0.5) / ln);
    }
    while (end > get_time()) {
    start:
      constexpr int k = 16;
      int a, ae, b, be;
      if (S < k) {
        a = 0;
        ae = S;
        b = 0;
        be = S;
      } else {
        a = get_random() % (S - k + 1);
        ae = a + k;
        b = get_random() % (S - k + 1);
        be = b + k;
      }
      static int path[0x1000];
      int pi = 0, bi = 0, v = 0;
      for (int t = 0; t < batch; ++t) {
        for (int i = a; i < ae; ++i) {
          for (int j = b; j < be; ++j) {
            int p = to(i, j);
            if (cell[p].v >= 0 ||
                (cell[p].v > -6 &&
                 (-cell[p].v << 28) <= log_[get_random() & (ln - 1)] * (batch - t))) {
              v += cell[p].v;
              change(p);
              path[pi++] = p;
              if (v > 0) goto start;
              if (v == 0) bi = pi;
            }
          }
        }
      }
      for (int i = pi - 1; i >= bi; --i) {
        change(path[i]);
      }
    }
    vector<string> ret(S, string(S, '.'));
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        if (cell[to(i, j)].o) ret[i][j] = 'K';
      }
    }
    return ret;
  }
};

// -------8<------- end of solution submitted to the website -------8<-------
int main() {
  KnightsAttacks ka;
  int S;
  cin >> S;
  vector<string> board(S);
  for (int i = 0; i < board.size(); ++i) cin >> board[i];

  vector<string> ret = ka.placeKnights(board);
  cout << ret.size() << endl;
  for (int i = 0; i < (int)ret.size(); ++i) cout << ret[i] << endl;
  cout.flush();
}
