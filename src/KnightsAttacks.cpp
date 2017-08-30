#include <bits/stdc++.h>
using namespace std;

constexpr double TIME_LIMIT = 9000;
constexpr int MAX_S = 500;
int S, SS, M[MAX_S][MAX_S];

double get_time() {
  unsigned long long a, d;
  __asm__ volatile("rdtsc" : "=a"(a), "=d"(d));
  return (d << 32 | a) / 2500000.0;
}

struct Cell {
  int x, y, v;
  bool o;

  void change() {
    auto change = [&](int x, int y) {
      if (0 <= x && x < S && 0 <= y && y < S) M[x][y] += o ? 1 : -1;
    };
    change(x + 1, y + 2);
    change(x + 1, y - 2);
    change(x - 1, y + 2);
    change(x - 1, y - 2);
    change(x + 2, y + 1);
    change(x + 2, y - 1);
    change(x - 2, y + 1);
    change(x - 2, y - 1);
    o = !o;
    v = -v;
  }

  void value() {
    v = 0;
    auto check = [&](int x, int y) {
      if (0 <= x && x < S && 0 <= y && y < S) v += o ^ (M[x][y] > 0) ? 1 : -1;
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
};

Cell cell[MAX_S][MAX_S];

class KnightsAttacks {
 public:
  vector<string> placeKnights(vector<string> board) {
    double end = get_time() + TIME_LIMIT;
    S = board.size();
    SS = S * S;
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        M[i][j] = board[i][j] - '0';
      }
    }
    static Cell* buf[MAX_S * MAX_S];
    for (int i = 0; i < S; ++i) {
      for (int j = 0; j < S; ++j) {
        Cell* c = &cell[i][j];
        c->x = i;
        c->y = j;
        c->o = false;
        c->value();
        buf[i * S + j] = c;
      }
    }
    auto compare = [](const Cell* a, const Cell* b) { return a->v > b->v; };
    sort(buf, buf + SS, compare);
    while (buf[0]->v > 0 && end > get_time()) {
      for (int i = 0; i < SS && buf[i]->v >= -2; ++i) {
        buf[i]->change();
        static int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
        static int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
        for (int j = 0; j < 8; ++j) {
          int x = buf[i]->x + dx[j];
          int y = buf[i]->y + dy[j];
          if ((buf[i]->o && M[x][y] == 0) || (!buf[i]->o && M[x][y] == 1)) {
            for (int k = 0; k < 8; ++k) {
              int x = buf[i]->x + dx[j] + dx[k];
              int y = buf[i]->y + dy[j] + dy[k];
              if (0 <= x && x < S && 0 <= y && y < S) cell[x][y].value();
            }
          }
        }
      }
      sort(buf, buf + SS, compare);
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
