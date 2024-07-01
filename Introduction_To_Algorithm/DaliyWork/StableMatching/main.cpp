#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class StableMatching {
public:
    StableMatching(int n, vector<vector<int>>& menPreferences, vector<vector<int>>& womenPreferences)
        : num(n), menPrefs(menPreferences), womenPrefs(womenPreferences), menPartner(n, -1), womenPartner(n, -1) {}

    void match() {
        while (!allMenAreEngaged()) {
            for (int i = 0; i < num; ++i) {
                if (menPartner[i] == -1) {
                    int woman = getNextWoman(i);
                    if (womenPartner[woman] == -1) {
                        engage(i, woman);
                    }
                    else {
                        int currentPartner = womenPartner[woman];
                        if (isPreferredByWoman(i, woman, currentPartner)) {

                            disengage(currentPartner);
                            engage(i, woman);
                        }
                    }
                }
               /* cout << "中间：";
                printMatches();
                cout << endl;*/
            }
            
        }
        
    }

    void printMatches() {
        for (int i = 0; i < num; ++i) {
            cout << menPartner[i] + 1 << ' ';
            /*cout << "Man " << i+1 << " is matched with Woman " << menPartner[i]+1 << endl;*/
        }
    }

private:
    int num;
    vector<vector<int>> menPrefs;
    vector<vector<int>> womenPrefs;
    vector<int> menPartner;
    vector<int> womenPartner;

    bool allMenAreEngaged() {
        return find(menPartner.begin(), menPartner.end(), -1) == menPartner.end();
    }

    int getNextWoman(int man) {
        for (int i = 0; i < num; ++i) {
            int woman = menPrefs[man][i];
            if (womenPartner[woman] == -1 || isPreferredByWoman(man, woman, womenPartner[woman])) {
                return woman;
            }
        }
        return -1; // Should not reach here if preferences are valid
    }

    bool isPreferredByWoman(int man1, int woman, int man2) {
        for (int i = 0; i < num; ++i) {
            if (womenPrefs[woman][i] == man1) {
                return true;
            }
            if (womenPrefs[woman][i] == man2) {
                return false;
            }
        }
        return false; // Should not reach here if preferences are valid
    }

    void engage(int man, int woman) {
        menPartner[man] = woman;
        womenPartner[woman] = man;
    }

    void disengage(int man) {
        int woman = menPartner[man];
        menPartner[man] = -1;
        // Update the woman's partner as well if needed
        womenPartner[woman] = -1;
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<int>> menPrefs(n, vector<int>(n));
    vector<vector<int>> womenPrefs(n, vector<int>(n));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            cin >> t;
            menPrefs[i][j] = t - 1;
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            cin >> t;
            womenPrefs[i][j] = t - 1;
        }
    }

    StableMatching stableMatching(n, menPrefs, womenPrefs);
    stableMatching.match();


    stableMatching.printMatches();

    return 0;
}