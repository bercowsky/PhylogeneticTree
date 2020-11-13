#include "Cjt_cluster.hh"

Cjt_cluster::Cjt_cluster() {}

/*Cjt_cluster::Cjt_cluster(const Cjt_especies& cjt_esp) {

}*/

void Cjt_cluster::inicializa_cluster(Cjt_especies cjt_esp) {
  mclust.clear();
  distancies.clear();
  int sz = cjt_esp.mida_mesp();

  if (sz > 0) {

    //Inicialitza mclust
    cjt_esp.principi();
    while (not cjt_esp.fi_itt()) {
      Especie e = cjt_esp.consultar_esp_itt();
      string idn = e.consultar_idn();
      pair<string, double> p = make_pair(idn, 0);
      Cluster c(p);
      mclust[idn] = c;
    }

    cjt_esp.principi();
    //Actualitzar taula distancies
    bool primero = true;
    for (map<string, Cluster>::iterator it = mclust.begin(); it != mclust.end(); it++) {
      map<string, Cluster>::iterator it2 = it;
      it2++;
      if (it2 == mclust.end()) distancies[it->first];
      while (it2 != mclust.end()) {
        if (it != it2) {
          Especie a = cjt_esp.consultar_especie(it->first);
          Especie b = cjt_esp.consultar_especie(it2->first);
          if (primero) {
            menor.first = a.consultar_idn();
            menor.second = b.consultar_idn();
            primero = false;
          }
          distancies[it->first][it2->first] = cjt_esp.distancia_especies(a, b);
          if (cjt_esp.distancia_especies(a, b) < cjt_esp.distancia_especies(cjt_esp.consultar_especie(menor.first),
          cjt_esp.consultar_especie(menor.second))) {
            menor.first = a.consultar_idn();
            menor.second = b.consultar_idn();
          }
        }
        it2++;
      }
    }
  }
}

void Cjt_cluster::ejecuta_paso_wpgma() {
  if (mclust.size() > 1) {
    map<string, map<string, double> >::const_iterator it1 = distancies.begin();
    string ident = menor.first + menor.second;

    pair<string, double> p = make_pair(ident, distancies[menor.first][menor.second]/2);
    BinTree<pair<string, double> > c(p, mclust[menor.first], mclust[menor.second]);

    while (it1 != distancies.end()) {
      double d;
      if (it1->first != ident) {
        if ((it1->first < menor.first) and (it1->first < menor.second))
          d = (distancies[it1->first][menor.first]+distancies[it1->first][menor.second])/2;
        else if ((it1->first < menor.first) and (it1->first > menor.second))
          d = (distancies[it1->first][menor.first]+distancies[menor.second][it1->first])/2;
        else if ((it1->first > menor.first) and (it1->first < menor.second))
          d = (distancies[menor.first][it1->first]+distancies[it1->first][menor.second])/2;
        else d = (distancies[menor.first][it1->first]+distancies[menor.second][it1->first])/2;

        if (it1->first < ident) distancies[it1->first].insert(make_pair(ident, d));
        else distancies[ident].insert(make_pair(it1->first, d));
      }
      it1++;
    }

    it1 = distancies.begin();
    while (it1 != distancies.end()) {
      distancies[it1->first].erase(menor.first);
      distancies[it1->first].erase(menor.second);
      it1++;
    }

    distancies.erase(menor.first);
    distancies.erase(menor.second);
    mclust.erase(menor.first);
    mclust.erase(menor.second);

    mclust[ident] = c;

    if (mclust.size() > 1) calcular_menor();
  }
}

void Cjt_cluster::calcular_menor() {
  map<string, map<string, double> >::const_iterator it1 = distancies.begin();
  map<string, double>::const_iterator it2 = (it1->second).begin();
  menor = make_pair(it1->first, it2->first);
  double dist_min = distancies[it1->first][it2->first];

  while (it1 != distancies.end()) {
    it2 = (it1->second).begin();
    while (it2 != (it1->second).end()) {
      if (dist_min > it2->second) {
        dist_min = it2->second;
        menor.first = it1->first;
        menor.second = it2->first;
      }
      it2++;
    }
    it1++;
  }
}

int Cjt_cluster::mida_cjt_cluster() {
  return mclust.size();
}

Cluster Cjt_cluster::obte_cluster(string idn) {
  return mclust[idn];
}

bool Cjt_cluster::existeix_cluster(string idn) const {
  map<string, Cluster>::const_iterator it = mclust.find(idn);
  return it != mclust.end();
}

void Cjt_cluster::imprime_tabla_dist() {
  for (map<string, Cluster>::const_iterator it1 = mclust.begin(); it1 != mclust.end(); it1++) {
    cout << it1->first << ":";
    for (map<string, double>::const_iterator it2 = distancies[it1->first].begin(); it2 != distancies[it1->first].end(); it2++)
      cout <<" "<< it2->first << " (" << it2->second <<")";
    cout << endl;
  }
}

void Cjt_cluster::imprime_cluster(const Cluster& c) {
  if (c.left().empty() and c.right().empty()) {
    cout << "["<<c.value().first<<"]";
  }
  else {
    cout <<"[("<<c.value().first<<", "<<c.value().second<<") ";
    if (not c.left().empty()) imprime_cluster(c.left());
    if (not c.right().empty()) imprime_cluster(c.right());
    cout << "]";
  }
}

void Cjt_cluster::imprime_arbol_filogenetico() {
  if (mclust.size() >= 1) {
    while (mclust.size() > 1) ejecuta_paso_wpgma();
    imprime_cluster(mclust.begin()->second);
    cout << endl;
  }
  else cout<<"ERROR: El conjunto de clusters es vacio."<<endl;
}
