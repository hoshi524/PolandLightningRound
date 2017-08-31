#include <bits/stdc++.h>
using namespace std;

constexpr double TIME_LIMIT = 2000;
constexpr int MAX_S = 1 << 9;
int S, SS;
char M[MAX_S][MAX_S];

double get_time() {
  unsigned long long a, d;
  __asm__ volatile("rdtsc" : "=a"(a), "=d"(d));
  return (d << 32 | a) / 2500000.0;
}

unsigned get_random() {
  static unsigned y = 2463534242;
  return y ^= (y ^= (y ^= y << 13) >> 17) << 5;
}

double get_random_double() { return (double)get_random() / UINT_MAX; }

bool in(int x, int y) { return 0 <= x && x < S && 0 <= y && y < S; }

struct Cell {
  int x, y, v;
  bool o;

  void change() {
    v = 0;
    if (o) {
      auto check = [&](int x, int y) {
        if (in(x, y)) {
          v += ++M[x][y] > 0 ? 1 : -1;
        }
      };
      check(x + 1, y + 2);
      check(x + 1, y - 2);
      check(x - 1, y + 2);
      check(x - 1, y - 2);
      check(x + 2, y + 1);
      check(x + 2, y - 1);
      check(x - 2, y + 1);
      check(x - 2, y - 1);
    } else {
      auto check = [&](int x, int y) {
        if (in(x, y)) {
          v += --M[x][y] < 0 ? 1 : -1;
        }
      };
      check(x + 1, y + 2);
      check(x + 1, y - 2);
      check(x - 1, y + 2);
      check(x - 1, y - 2);
      check(x + 2, y + 1);
      check(x + 2, y - 1);
      check(x - 2, y + 1);
      check(x - 2, y - 1);
    }
    o = !o;
  }

  void value() {
    v = 0;
    if (o) {
      auto check = [&](int x, int y) {
        if (in(x, y)) {
          v += M[x][y] < 0 ? 1 : -1;
        }
      };
      check(x + 1, y + 2);
      check(x + 1, y - 2);
      check(x - 1, y + 2);
      check(x - 1, y - 2);
      check(x + 2, y + 1);
      check(x + 2, y - 1);
      check(x - 2, y + 1);
      check(x - 2, y - 1);
    } else {
      auto check = [&](int x, int y) {
        if (in(x, y)) {
          v += M[x][y] > 0 ? 1 : -1;
        }
      };
      check(x + 1, y + 2);
      check(x + 1, y - 2);
      check(x - 1, y + 2);
      check(x - 1, y - 2);
      check(x + 2, y + 1);
      check(x + 2, y - 1);
      check(x - 2, y + 1);
      check(x - 2, y - 1);
    }
  }
};

Cell cell[MAX_S][MAX_S];

int score() {
  int x = 0;
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j < S; ++j) {
      x += abs(M[i][j]);
    }
  }
  return x;
}

class KnightsAttacks {
 public:
  vector<string> placeKnights(vector<string> board) {
    const double end = get_time() + TIME_LIMIT;
    S = board.size();
    SS = S * S;
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        M[i][j] = board[i][j] - '0';
      }
    }
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        Cell* c = &cell[i][j];
        c->x = i;
        c->y = j;
        c->o = false;
        c->value();
      }
    }
    auto change = [&](Cell& c) {
      c.change();
      int t = c.o ? -1 : 1, x, y, p;
      auto update = [&](int a, int b) {
        if (in(a, b)) {
          if (cell[a][b].o) {
            cell[a][b].v += (p < 0 ? -1 : 1) + (M[x][y] < 0 ? 1 : -1);
          } else {
            cell[a][b].v += (p > 0 ? -1 : 1) + (M[x][y] > 0 ? 1 : -1);
          }
        }
      };
      x = c.x + 1;
      y = c.y + 2;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
      x = c.x + 1;
      y = c.y - 2;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
      x = c.x - 1;
      y = c.y + 2;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
      x = c.x - 1;
      y = c.y - 2;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
      x = c.x + 2;
      y = c.y + 1;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
      }
      x = c.x + 2;
      y = c.y - 1;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x + 2, y - 1);
        update(x - 2, y - 1);
      }
      x = c.x - 2;
      y = c.y + 1;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y + 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
      x = c.x - 2;
      y = c.y - 1;
      if (in(x, y) && (M[x][y] == t || M[x][y] == 0)) {
        p = M[x][y] - t;
        update(x + 1, y + 2);
        update(x + 1, y - 2);
        update(x - 1, y + 2);
        update(x - 1, y - 2);
        update(x + 2, y - 1);
        update(x - 2, y + 1);
        update(x - 2, y - 1);
      }
    };
    while (true) {
      const double time = -4.0 * (end - get_time()) / TIME_LIMIT;
      if (time > 0) break;
      for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
          if (cell[i][j].v >= time * get_random_double()) {
            change(cell[i][j]);
          }
        }
      }
    }
    vector<string> ret(S, string(S, '.'));
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        if (cell[i][j].o) ret[i][j] = 'K';
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
