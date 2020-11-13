#include "Cjt_especies.hh"

Cjt_especies::Cjt_especies() {

}

bool Cjt_especies::crea_especie(Especie e) {
  map<string, Especie>::iterator it = mesp.find(e.consultar_idn());
  if (it != mesp.end()) return false;
  else {
    string s = e.consultar_idn();
    mesp.insert(make_pair(e.consultar_idn(), e));
    for (map<string, Especie>::iterator it = mesp.begin(); it != mesp.end(); it++) {
      if (it->first < s) distancies[it->first][s] = e.distancia(it->second);
      else if (it->first > s) distancies[s][it->first] = e.distancia(it->second);
    }
  }
  return true;
}

bool Cjt_especies::elimina_especie(string idn) {
  if (mesp.erase(idn) == 0) return false;
  mesp.erase(idn);
  distancies.erase(idn);
  map<string,Especie>::const_iterator it = mesp.begin();
  while (it != mesp.end() and it->first < idn) {
    distancies[(it->first)].erase(idn);
    it++;
  }
  return true;
}

void Cjt_especies::principi() {
  itt = mesp.begin();
}

bool Cjt_especies::fi_itt() {
  return itt == mesp.end();
}

int Cjt_especies::mida_mesp() const {
  return mesp.size();
}

bool Cjt_especies::existe_especie(string idn) const {
  map<string, Especie>::const_iterator it = mesp.find(idn);
  if (it != mesp.end()) return true;
  return false;
}

Especie Cjt_especies::consultar_especie(string idn) const {
  map<string, Especie>::const_iterator it = mesp.find(idn);
  return it->second;
}

double Cjt_especies::distancia_especies(Especie a, Especie b) {
  string idn_a = a.consultar_idn();
  string idn_b = b.consultar_idn();
  if (idn_a < idn_b) return distancies[idn_a][idn_b];
  return distancies[idn_b][idn_a];
}

string Cjt_especies::obtener_gen(string idn) const {
  map<string, Especie>::const_iterator it = mesp.find(idn);
  return it->second.consultar_gen();
}

Especie Cjt_especies::consultar_esp_itt() {
  Especie e = itt->second;
  itt++;
  return e;
}

void Cjt_especies::lee_cjt_especies() {
  mesp.clear();
  distancies.clear();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    Especie e;
    e.leer_especie();
    crea_especie(e);
  }
}

void Cjt_especies::tabla_distancias() {
  for (map<string, Especie>::const_iterator it1 = mesp.begin(); it1 != mesp.end(); it1++) {
    cout << it1->first << ":";
    for (map<string, double>::const_iterator it2 = distancies[it1->first].begin(); it2 != distancies[it1->first].end(); it2++)
      cout <<" "<< it2->first << " (" << it2->second <<")";
    cout << endl;
  }
}

void Cjt_especies::imprime_cjt_especies() const {
  for (map<string, Especie>::const_iterator it = mesp.begin(); it != mesp.end(); it++) {
    (it->second).imprime_especie();
  }
}
