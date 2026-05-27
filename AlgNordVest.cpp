#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void afisareTabel(vector<vector<int>>& cost,
                   vector<int>& disp,
                   vector<int>& nec)
{
    int m = disp.size(), n = nec.size();
    int suma = 0;

    cout << "\n";
    cout << setw(6) << " ";

    for(int j = 0; j < n; j++)
        cout << setw(6) << "D" << j + 1;

    cout << setw(8) << "Disp\n";

    for(int i = 0; i < m; i++)
    {
        cout << setw(6) << "N" << i + 1;
        for(int j = 0; j < n; j++)
            cout << setw(6) << cost[i][j];
        cout << setw(8) << disp[i] << endl;
    }

    cout << setw(6) << "Nec";
    for(int j = 0; j < n; j++)
    {
        cout << setw(6) << nec[j];
        suma += nec[j];
    }
    cout << setw(8) << suma << endl;
}

void echilibrare(vector<int>& disp,
                 vector<int>& nec,
                 vector<vector<int>>& cost)
{
    int sDisp = 0, sNec = 0;

    for(int x : disp) sDisp += x;
    for(int x : nec) sNec += x;

    cout << "\nSuma Disponibil = " << sDisp;
    cout << "\nSuma Necesar = " << sNec << endl;

    if(sDisp > sNec)
    {
        nec.push_back(sDisp - sNec);
        for(int i = 0; i < cost.size(); i++)
            cost[i].push_back(0);
    }
    else if(sNec > sDisp)
    {
        disp.push_back(sNec - sDisp);
        cost.push_back(vector<int>(nec.size(), 0));
    }

    afisareTabel(cost, disp, nec);
}

void nordVest(vector<vector<int>>& cost,
              vector<int> disp,
              vector<int> nec,
              vector<vector<int>>& sol)
{
    int i = 0, j = 0;
    int iter = 1;

    cout << "\n--- ITERATII NORD-VEST ---\n";

    while(i < disp.size() && j < nec.size())
    {
        cout << "\n========================\n";
        cout << "Iteratia " << iter++ << "\n";

        int x = min(disp[i], nec[j]);
        sol[i][j] = x;

        cout << "Alocare: S" << i + 1 << " -> D" << j + 1
             << " = " << x << "\n";

        disp[i] -= x;
        nec[j] -= x;

        cout << "Disponibil ramas S" << i + 1 << " = " << disp[i] << "\n";
        cout << "Necesar ramas D" << j + 1 << " = " << nec[j] << "\n";

        cout << "\nMatrice solutie partiala:\n";
        for(auto &r : sol)
        {
            for(int v : r)
                cout << setw(6) << v;
            cout << endl;
        }

        if(disp[i] == 0)
            i++;
        else
            j++;
    }
}

int costTotal(vector<vector<int>>& sol,
              vector<vector<int>>& cost)
{
    int total = 0;
    bool prima = true;

    cout << "\nZ = ";

    for(int i = 0; i < sol.size(); i++)
        for(int j = 0; j < sol[0].size(); j++)
            if(sol[i][j] != 0)
            {
                if(!prima) cout << " + ";
                cout << sol[i][j] << " * " << cost[i][j];
                total += sol[i][j] * cost[i][j];
                prima = false;
            }

    cout << endl;
    return total;
}

void degenerare(vector<vector<int>>& sol)
{
    int m = sol.size(), n = sol[0].size(), k = 0;

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(sol[i][j] != 0)
                k++;

    cout << "\nDegenerare:\n";
    cout << "m=" << m << " n=" << n << endl;
    cout << "Celule=" << k << endl;
    cout << "m+n-1=" << m + n - 1 << endl;

    if(k == m + n - 1)
        cout << "Solutie nedegenerata\n";
    else
        cout << "Solutie degenerata\n";
}

int main()
{
    int m, n;
    vector<vector<int>> cost, sol;
    vector<int> disp, nec;

    cout << "Nr surse: ";
    cin >> m;

    cout << "Nr destinatii: ";
    cin >> n;

    cost.resize(m, vector<int>(n));

    cout << "\nCosturi:\n";
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> cost[i][j];

    disp.resize(m);
    cout << "\nDisponibil:\n";
    for(int i = 0; i < m; i++)
        cin >> disp[i];

    nec.resize(n);
    cout << "\nNecesar:\n";
    for(int j = 0; j < n; j++)
        cin >> nec[j];

    afisareTabel(cost, disp, nec);

    echilibrare(disp, nec, cost);

    sol.resize(disp.size(), vector<int>(nec.size(), 0));

    nordVest(cost, disp, nec, sol);

    cout << "\nSOLUTIE FINALA:\n";
    for(auto r : sol)
    {
        for(int x : r)
            cout << setw(6) << x;
        cout << endl;
    }

    int total = costTotal(sol, cost);
    cout << "Cost total = " << total << endl;

    degenerare(sol);

    return 0;
}
