/*

Arborii binari de cautare
Proprietati:
- in fiecare nod se va retine o cheie
- pentru fiecare nod, subarborele stang va contine noduri cu chei mai mici
- pentru fiecare nod, subarborele drep va contine noduri cu chei mai mari

	
struct Node {
	int key;
	int freq;
	int subtreeSize;
	Node *left, *right;
};
Node *root;

      11
    /    \
   7     15
  / \    / \
 1   9  13 21

Aplicatii:
- putem insera/sterge valori
- putem cauta valori
- putem gasi elementul de pe pozitia k in multimea de valori (care este evident sortata)

Din pacate aceasta structura nu ne poate garanta o complexitate logaritmica.
Un caz care ar strica complexitatea ar fi inserarea unor valori in ordine descrescatoare (arborele ar deveni lant).

       11
      /
     10
    /
   9 
  /
 8

Din fericire putem rezolva problema, balansand arborele.
- Treap: https://en.wikipedia.org/wiki/Treap
- Red-black tree: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

+
policy-based data structures
https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html

(red-black tree deja impelentat)

*/

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

ifstream fin("elmaj.in");
ofstream fout("elmaj.out");

const int error_message = -1;
const int INSERT = 1;
const int ERASE = 2;
const int QUERY = 3;

struct Query {
	int TYPE;
	int value;
};
vector<Query> Queries;

template<typename T>
using Tree = tree<T, null_type, less_equal<T>,
			rb_tree_tag, tree_order_statistics_node_update>;
Tree<int> DS;
map<int, int> freq;

void Insert(int value) {
	freq[value]++;
	DS.insert(value);
}

void Erase(int value) {
	assert(freq[value] > 0);
	freq[value]--;
	DS.erase(DS.upper_bound(value));
}

int MajorityQuery() {
	int value = *DS.find_by_order(DS.size() / 2);

	if(freq[value] > DS.size() / 2) {
		return value;
	}
	return error_message;
}

int main() {
	int Q;
	fin >> Q;
	Queries = vector<Query> (Q);

	for(auto &q: Queries) {
		int TYPE, value = 0;
		fin >> TYPE;

		assert(TYPE == INSERT || TYPE == ERASE || TYPE == QUERY);

		if(TYPE != QUERY) {
			fin >> value;
		}

		q = {TYPE, value};
	}

	for(const auto &q: Queries) {
		if(q.TYPE == INSERT) {
			Insert(q.value);
		} else if(q.TYPE == ERASE) {
			Erase(q.value);
		} else {
			fout << MajorityQuery() << '\n';
		}
	}
	return 0;
}
