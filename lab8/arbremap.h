/* Squelette pour classe générique ArbreMap<K, V>.
 * Lab8 -- Dictionnaires et Arbres binaires de recherche
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab8/
 *
 */
#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__
#include "arbreavl.h"

template <class K, class V>
class ArbreMap {

  public:
    bool contient(const K&) const;

    void enlever(const K&);
    void vider();
    bool vide() const;

    const V& operator[] (const K&) const;
    V& operator[] (const K&);

  private:
    class Entree{
    public:
        Entree(const K& c) : cle(c), valeur() {}
        K cle;
        V valeur;
        bool operator < (const Entree& e) const { return cle < e.cle; }
    };
    ArbreAVL<Entree> entrees;
public:
    class Iterateur {
    public:
        Iterateur(ArbreMap& a) : iter(a.entrees.debut()) {}
        Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
        operator bool() const {return iter.operator bool();};
        Iterateur& operator++() {++iter; return * this;}
        const K& cle() const {return (*iter).cle;}
        V& valeur() {return (V&) (* iter).valeur;}
    private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };
    Iterateur debut() { return Iterateur(*this); }
    Iterateur fin() { return Iterateur(entrees.fin());}
};

template <class K, class V>
void ArbreMap<K,V>::vider(){
    // À compléter
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    // À compléter
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    // À compléter
    entrees.enlever(c);
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    // Construire un objet Entree avec la cle recherchee
    Entree entree(c);
    // La valeur n’est pas importante, car l’operateur < ne la considere pas
    return entrees.contient(entree);
}


template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    // L’element doit exister!
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    if(!iter){
        // Choix d’implementation : si l’element n’existe pas, on le cree
        entrees.inserer(Entree(c));
        iter = entrees.rechercher(c);
        // Choix alternatif : creation explicite (Ex: TreeMap.put() en Java).
    }
    return entrees[iter].valeur;
}


#endif
