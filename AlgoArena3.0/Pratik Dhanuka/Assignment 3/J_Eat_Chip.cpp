#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lli = long long int;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr)

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const int MAXN = 200000;
int spf[MAXN + 1];
vector<bool> isPrime(MAXN + 1, true);

void sieve_prime(){
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i * i <= MAXN; i++){
        if(isPrime[i]){
            for(int j = i * i; j <= MAXN; j += i) isPrime[j] = false;
        }
    }
}

void sieve_spf(){
    spf[0] = 0;
    spf[1] = 1;
    for(int i = 2; i <= MAXN; i++) spf[i] = i;
    for(int i = 2; i * i <= MAXN; i++){
        if(spf[i] == i){
            for(int j = i * i; j <= MAXN; j += i)
                if(spf[j] == j) spf[j] = i;
        }
    }
}

vector<pair<int,int>> factorize(int x){
    vector<pair<int,int>> res;
    while(x > 1){
        int p = spf[x], cnt = 0;
        while(x % p == 0){
            x /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    return res;
}

static vector<int> fact, ifact;

long long modpow(long long a, long long b) {
    long long res = 1;
    a %= MOD1;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD1;
        a = (a * a) % MOD1;
        b >>= 1;
    }
    return res;
}

long long modinv(long long q) {
    return modpow(q, MOD1 - 2);
}

void factorials(int n) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = (1LL * fact[i - 1] * i)%MOD1;

    ifact[n] = modinv(fact[n]);
    for (int i = n; i > 0; --i)
        ifact[i - 1] = (1LL * ifact[i] * i) % MOD1;
}

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if ((int)fact.size() <= n) factorials(n);
    return (1LL * fact[n] * ifact[r] % MOD1) * ifact[n - r] % MOD1;
}

void dfs(int s, const vector<vi> &adj, vi &visited) {
    visited[s] = 1;
    for (int v : adj[s]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

void bfs(int s, const vector<vi> &adj, vi &visited) {
    queue<int> q;
    q.push(s);
    visited[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
}

lli exp(lli base, lli exp){
   lli a= 1;
   for(int i = 1;i<=exp;i++){
     a*=base;
   }
   return a;
}
vi dijkstra(int v, const vector<vector<pii>> &adj, int s){
    vi dis(v+1, INT_MAX);
    dis[s] = 0;

    set<pii> d;
    d.emplace(0, s);

    while(!d.empty()){
        int dist = (*d.begin()).first;
        int node = (*d.begin()).second;
        d.erase(d.begin());

        for(auto it : adj[node]){
            int w = it.second;
            int n = it.first;

            if(dist + w < dis[n]){
                if(dis[n] != INT_MAX){
                    pii p = {dis[n], n};
                    d.erase(p);
                }

                dis[n] = dist + w;
                d.emplace(dis[n], n);
            }
        }
    }

    return dis;
}

void solve() {
    int h,w,xa,xb,ya,yb;
    cin>>h>>w>>xa>>ya>>xb>>yb;
    if(xb<=xa){
        cout<<"DRAW\n";
        return;
    }
    int meet= (xa+xb+1)/2;
    if(xb-xa==1&&abs(yb-ya)<=1){
        cout<<"ALICE\n";
        return;
    }
    else if(xb-xa==1){
        cout<<"DRAW\n";
        return;
    }
    if((xb-xa)%2==1){
        if(ya==yb+1||ya==yb-1){
            cout<<"ALICE\n";
        }
        else if(ya>yb){
            int m = max(1, yb-xb+meet);
            if(ya-meet+xa<=m){
                cout<<"ALICE\n";
            }
            else{
                cout<<"DRAW\n";
            }

        }
        else if(ya==yb){
            cout<<"ALICE\n";

        }
        else{
            int m = min(w, yb+xb-meet);
            if(meet-xa+ya>=m){
                cout<<"ALICE\n";
            }
            else{
                cout<<"DRAW\n";
            }
        }
    }
    else{
        if(ya==yb){
            cout<<"BOB\n";
        }
        else if(ya>yb){
            int m = min(w, meet-xa+ya);
            if(yb+xb-meet>=m){
                cout<<"BOB\n";
            }
            else{
                cout<<"DRAW\n";
            }
        }
        else{
            int m = max(1, ya-meet+xa);
            if(yb-xb+meet<=m){
                cout<<"BOB\n";
            }
            else{
                cout<<"DRAW\n";
            }
        }
    }

}

int main() {
    fastio;

    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}