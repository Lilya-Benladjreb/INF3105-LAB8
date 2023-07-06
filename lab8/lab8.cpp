/* Squelette pour la tâche 4.
 * Lab8 -- Dictionnaires et Arbres binaires de recherche
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab8/
 *
 */
#include <iostream>
#include "arbreavl.h"
#include "arbremap.h"
using namespace std;

class IP4{
  unsigned char nombre[4] = {0, 0, 0, 0};
public:
  bool operator < (const IP4&) const;
  bool operator == (const IP4&) const;
  friend istream& operator >> (istream& is, IP4& ip4);
  friend ostream& operator << (ostream& os, IP4& ip4);
};

int main(){
    // Déclarer quelque chose ici.
    // Indice : il faut associer un nom de fichier à un ensemble d'adresses IP.
    // Cela ressemble à l'imbrication : Tableau<Liste<int> > tab;
    ArbreMap<string, ArbreAVL<IP4>> dictionnaire;
    
    while(cin && !cin.eof()){
        IP4 ip;
        std::string date, method, file;
        cin >> ip >> date >> method >> file >> std::ws;
        // Faire quelque chose ici.
        dictionnaire[file].inserer(ip);
    }
    
    // Avant tâche 6:
    cout << dictionnaire["/INF3105/diapos/04-tabgen.pdf"].taille() << endl;
    cout << dictionnaire["/INF3105/diapos/07-listes.pdf"].taille() << endl;
    cout << dictionnaire["/INF3105/diapos/08-arbresmap.pdf"].taille() << endl;
    
    // Après tâche 6: Itérer sur clés du dictionnaires qui sont les noms de fichier.
    // Pour chacun nom, afficher la taille de l'ensemble d'adresses IPs.
    ArbreMap<string, ArbreAVL<IP4>>::Iterateur iter = dictionnaire.debut();
    while(iter) {
        cout << iter.cle() << " : " << iter.valeur().taille() << endl;
        ++iter;
    }

   return 0;
}

bool IP4::operator < (const IP4& o) const{
    for(int i=0;i<4;i++)
        if(nombre[i] < o.nombre[i]) return true;
        else if(nombre[i] > o.nombre[i]) return false;
    return false;
}
bool IP4::operator == (const IP4& o) const{
    for(int i=0;i<4;i++)
        if(nombre[i] != o.nombre[i]) return false;
    return true;
}

istream& operator >> (istream& is, IP4& ip4){
    int a=0, b=0, c=0, d=0;
    char p1=0, p2=0, p3=0;
    is >> a >> p1
       >> b >> p2
       >> c >> p3
       >> d;
    ip4.nombre[0] = a;
    ip4.nombre[1] = b;
    ip4.nombre[2] = c;
    ip4.nombre[3] = d;
    return is;
}

ostream& operator << (ostream& os, IP4& ip4){
    os << (int) ip4.nombre[0] << '.'
       << (int) ip4.nombre[1] << '.'
       << (int) ip4.nombre[2] << '.'
       << (int) ip4.nombre[3];
    return os;
}

