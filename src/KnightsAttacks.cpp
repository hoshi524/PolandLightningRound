#include <bits/stdc++.h>
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

int to(int x, int y) { return (x << 9) + y; }

bool in(const int p) {
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
      auto check = [&](int p) {
        if (in(p)) v += M[p] < 0 ? 1 : -1;
      };
      check(p + MAX_S + 2);
      check(p + MAX_S - 2);
      check(p - MAX_S + 2);
      check(p - MAX_S - 2);
      check(p + 2 * MAX_S + 1);
      check(p + 2 * MAX_S - 1);
      check(p - 2 * MAX_S + 1);
      check(p - 2 * MAX_S - 1);
    } else {
      auto check = [&](int p) {
        if (in(p)) v += M[p] > 0 ? 1 : -1;
      };
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

template <int t, typename Check, typename Change>
void change(int p, Check check, Change change) {
  cell[p].o = !cell[p].o;
  cell[p].v = -cell[p].v;
  int x, v;
  x = p + MAX_S + 2;
  if (in(x)) {
    change(x);
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
    change(x);
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
    change(x);
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
    change(x);
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
    change(x);
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
    change(x);
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
    change(x);
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
    change(x);
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
template <typename Check>
void change(int p, Check check) {
  if (cell[p].o) {
    change<1>(p, check, [](int p) { ++M[p]; });
  } else {
    change<-1>(p, check, [](int p) { --M[p]; });
  }
}

template <int t, typename Check, typename Change>
void change_(int p, Check check, Change change) {
  cell[p].o = !cell[p].o;
  cell[p].v = -cell[p].v;
  int x, v;
  x = p + MAX_S + 2;
  change(x);
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
  x = p + MAX_S - 2;
  change(x);
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
  x = p - MAX_S + 2;
  change(x);
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
  x = p - MAX_S - 2;
  change(x);
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
  x = p + 2 * MAX_S + 1;
  change(x);
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
  x = p + 2 * MAX_S - 1;
  change(x);
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
  x = p - 2 * MAX_S + 1;
  change(x);
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
  x = p - 2 * MAX_S - 1;
  change(x);
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
template <typename Check>
void change_(int p, Check check) {
  if (cell[p].o) {
    change_<1>(p, check, [](int p) { ++M[p]; });
  } else {
    change_<-1>(p, check, [](int p) { --M[p]; });
  }
}

class KnightsAttacks {
 public:
  vector<string> placeKnights(vector<string> board) {
    const double end = get_time() + TIME_LIMIT;
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
    auto check_ = [](int n, int a, int b) {
      if (cell[n].o) {
        cell[n].v += (a < 0 ? -1 : 1) + (b < 0 ? 1 : -1);
      } else {
        cell[n].v += (a > 0 ? -1 : 1) + (b > 0 ? 1 : -1);
      }
    };
    auto check = [](int n, int a, int b) {
      if (in(n)) {
        if (cell[n].o) {
          cell[n].v += (a < 0 ? -1 : 1) + (b < 0 ? 1 : -1);
        } else {
          cell[n].v += (a > 0 ? -1 : 1) + (b > 0 ? 1 : -1);
        }
      }
    };
    while (true) {
      const double time = -2.0 * (end - get_time()) / TIME_LIMIT;
      if (time > 0) break;
      for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
          int p = to(i, j);
          if (cell[p].v > time - 0.8 &&
              cell[p].v >
                  time * get_random_double() - 0.8 + get_random_double()) {
            if (4 <= i && i < S - 4 && 4 <= j && j < S - 4) {
              change_(p, check_);
            } else if (2 <= i && i < S - 2 && 2 <= j && j < S - 2) {
              change_(p, check);
            } else {
              change(p, check);
            }
          }
        }
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
