#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
ifstream f("dfs.in");
ofstream g("dfs.out");
class Graf
{
    private:
        int Noduri, Muchii;
        vector <vector<int>> ListaAdiacenta;

    public:
        Graf(){}
        Graf(int Noduri)
        {
            this->Noduri = Noduri;
        }
        Graf( int Noduri, int Munchii, vector <vector<int>> ListaAdiacenta)

        {
            this->Noduri = Noduri;
            this->Muchii = Muchii;
            this->ListaAdiacenta= ListaAdiacenta;

        }

        ~Graf()
        {
            this->Noduri = 0;
            this->Muchii = 0;
            this->ListaAdiacenta.clear();
        }

        void SetNoduri(int n)
        {
            Noduri = n;
        }

        int GetNoduri()
        {
            return Noduri;
        }

        void SetMuchii(int m)
        {
            Muchii = m;
        }

        int GetMuchii()
        {
            return Muchii;
        }

        vector<int> codBFS(int s);
        void codDFS(int nod, vector <bool> & vizitat);
        int ComponenteConexe();
        void CodSortareTopo(int grad_intern[]);
        int Cautare(int nod, vector <int> &radacina);
        void Reuniune(int x, int y, vector <int> &radacina);
        vector <int> CodDisjoint(vector <pair<int, pair<int, int>>>operatii);
        vector<int> CodDisjkstra(vector <vector<pair <int, int>>> CosturiMuchii);
        int CodDarb();
        void CodRoyfloyd(int m[101][101]);

};

vector<int> Graf::codBFS(int s)
{
    queue <int> coada;
    vector <int> distanta(Noduri+1,0);
    bool vizitat[Noduri+1] = {false};
    vizitat[s] = true;
    coada.push(s);
    while(coada.size()!= 0)
    {
        for (int nod : ListaAdiacenta[coada.front()])
        {
            if(vizitat[nod]==false)
            {
                vizitat[nod]=true;
                distanta[nod]=distanta[coada.front()]+1;
                coada.push(nod);
            }
        }
        coada.pop();
    }

    return distanta;
}


void Bfs()
{
    int n, m, x, y, s;
    f>>n>>m>>s;
    vector <vector<int>> ListaAdiacenta(n+1);
    vector <int> afisare;
    for(int i= 0; i < m; i++)
    {
        f>>x>>y;
        ListaAdiacenta[x].push_back(y);
    }
    Graf G(n, m, ListaAdiacenta);
    afisare = G.codBFS(s);
    for(int i = 1; i < afisare.size(); i++)
        {
            if(afisare[i]==0 && s != i)
                g<<"-1"<<" ";
            else
                g<<afisare[i]<<" ";
        }
    }


void Graf::codDFS(int nod, vector <bool>& vizitat)
{
    vizitat[nod]=true;
    for(int i : ListaAdiacenta[nod])
        {
            if(vizitat[i]==false)
                codDFS(i, vizitat);
        }
}

int Graf::ComponenteConexe()
{
    vector <bool> vizitat(Noduri+ 1, false);
    int nr = 0;
    for(int i=1; i<=Noduri; i++)
        if(vizitat[i]==false)
    {
        nr++;
        codDFS(i, vizitat);
    }
    return nr;
}
void Dfs()
{
    int n, m, x, y;
    f>>n>>m;
    vector <vector<int>> ListaAdiacenta(n+1);
    for(int i=0; i < m; i++)
    {
        f>>x>>y;
        ListaAdiacenta[x].push_back(y);
        ListaAdiacenta[y].push_back(x);
    }
    Graf G(n, m, ListaAdiacenta);
    g<<G.ComponenteConexe();
}

void Graf::CodSortareTopo(int grad_intern[])
{
    queue <int> coada;
    vector <int> afisare;
    for(int i=1; i<=Noduri; i++)
        if(grad_intern[i]==0)
            coada.push(i);
    while(coada.size()!=0)
    {
        int nod = coada.front();
        afisare.push_back(nod);
        coada.pop();
        for (int i : ListaAdiacenta[nod])
        {
            grad_intern[i]--;
            if(grad_intern[i]==0)
                coada.push(i);
        }
    }

    for(auto i = afisare.begin(); i!=afisare.end(); i++)
        g<<*i<<' ';
}
void SortareTopologica()
{
    int n, m, x, y;
    f>>n>>m;
    int grad_intern[50001]={0};
    vector <vector<int>> ListaAdiacenta(n+1);
    for(int i=0; i < m; i++)
    {
        f>>x>>y;
        ListaAdiacenta[x].push_back(y);
        grad_intern[y]++;
    }
    Graf G(n, m, ListaAdiacenta);
    G.CodSortareTopo(grad_intern);
}

int Graf::Cautare(int nod, vector<int>&radacina)
{
    if(radacina[nod]!=nod)
        radacina[nod]=Cautare(radacina[nod], radacina);
    return radacina[nod];
}

void Graf::Reuniune(int x, int y, vector<int>&radacina)
{
    int radx, rady;
    radx=Cautare(x, radacina);
    rady=Cautare(y, radacina);
    radacina[radx]=rady;
}
vector <int> Graf::CodDisjoint(vector <pair<int, pair<int, int>>>operatii)
{
    vector <int> solutie;
    vector <int> radacina(Noduri+1);
    for(int i=1;i<=Noduri; i++)
        radacina[i]=i;
    for(int i=0; i < operatii.size();i++)
    {
        int op = operatii[i].first;
        int x = operatii[i].second.first;
        int y = operatii[i].second.second;
        if(op==1)
            Reuniune(x, y, radacina);
            else
        {
            if(Cautare(x, radacina)==Cautare(y, radacina))
                solutie.push_back(1);
            else
                solutie.push_back(0);
        }
    }
    return solutie;
}
void Disjoint()
{
    int N, M, op, x, y;
    f>>N>>M;
    Graf G(N);
    vector <pair<int, pair<int, int>>>operatii;

    for(int i=0; i<M; i++)
    {
        f>>op>>x>>y;
        operatii.push_back(make_pair(op, make_pair(x, y)));
    }

    vector<int>afisare=G.CodDisjoint(operatii);

    for(auto i=0; i<afisare.size(); i++)
       {
        if(afisare[i]==1)
            g<<"DA"<<'\n';
        else
            g<<"NU"<<'\n';
       }
}

vector<int> Graf::CodDisjkstra(vector <vector<pair <int, int>>> CosturiMuchii)
{
    vector <int> distanta(Noduri+1, INT_MAX);
    vector <bool> vizitat(Noduri+1, false);
    priority_queue<pair<int, int>> coada;
    distanta[1]=0;
    coada.push(make_pair(0, 1));
    while(!coada.empty())
    {
        int NodCurent = coada.top().second;
        coada.pop();
        if(vizitat[NodCurent]==false)
          {

            vizitat[NodCurent]==true;

            for(auto i : CosturiMuchii[NodCurent])
            {
                int vecin = i.first;
                int cost = i.second;

                if(distanta[NodCurent] + cost <distanta[vecin])
                {
                    distanta[vecin] = distanta[NodCurent] + cost;
                    coada.push(make_pair(-distanta[vecin], vecin));
                }
            }
          }
    }

    for(int i=2; i<=Noduri; i++)
       {
        if(distanta[i]==INT_MAX)
            distanta[i]=0;
       }
    return distanta;
}
void Dijkstra()
{
    int n, m, a, b, c;
    f>>n>>m;
    Graf G(n);
    vector <vector<pair <int, int>>> CosturiMuchii(n + 1);
    for(int i=0; i<m; i++)
    {
        f>>a>>b>>c;
        CosturiMuchii[a].push_back(make_pair(b,c));
    }

    vector <int> afisare = G.CodDisjkstra(CosturiMuchii);

    for(int i=2; i<=n; i++)
        g<<afisare[i]<<' ';
}

int Graf::CodDarb()
{
    int nod_ultim, dist_max = -1;
    vector <int> distanta = codBFS(1);
    for(int i=1; i < distanta.size(); i++)
        if(distanta[i]> dist_max)
    {
        dist_max = distanta[i];
        nod_ultim = i;
    }

    distanta = codBFS(nod_ultim);
    dist_max = -1;

    for(int i=1; i < distanta.size(); i++)
        if(distanta[i]> dist_max)
    {
        dist_max = distanta[i];
    }

    return dist_max;

}

void Darb()
{
    int n, x, y;
    f>>n;
    vector <vector<int>> ListaAdiacenta(n+1);

    for(int i=0; i<n-1; i++)
    {
        f>>x>>y;
        ListaAdiacenta[x].push_back(y);
        ListaAdiacenta[y].push_back(x);
    }

    Graf G(n, n-1, ListaAdiacenta);
    g<<G.CodDarb()+1;
}

void Graf::CodRoyfloyd(int m[101][101])
{
    int i, j, k;
    for(k = 1; k <= Noduri; k++)
        for(i = 1; i <= Noduri; i++)
            for( j = 1; j <= Noduri; j++)
                if(m[i][j]> m[i][k]+m[k][j])
                    m[i][j] = m[i][k]+m[k][j];

}

void Royfloyd()
{
    int i, j, n, m[101][101];
    f>>n;
    Graf G(n);

    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            f>>m[i][j];
            if(m[i][j]==0 && i!=j)
                m[i][j]=1001;
        }
    G.CodRoyfloyd(m);
     for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
                {
                    if(m[i][j]==1001)
                        m[i][j]=0;
                    g<<m[i][j]<<' ';
                }
            g<<'\n';
        }
}
int main()
{
    Dfs();
    f.close();
    g.close();
    return 0;
}
