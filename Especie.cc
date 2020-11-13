#include "Especie.hh"

int Especie::k = 0;

void Especie::hacer_kmer() {
  int size = gen.size();
  for (int i = 0; i < size-k+1; i++) {
    string s = "";
    for (int j = i; j < i+k; j++) {
      s += gen[j];
    }
    kmer[s] += 1;
  }
}

Especie::Especie() {
  idn = "";
  gen = "";
}


void Especie::inicia_k(int k) {
  Especie::k = k;
}

map<string,int> Especie::consultar_kmer() {
  return kmer;
}

string Especie::consultar_idn() {
  return idn;
}

string Especie::consultar_gen() const{
  return gen;
}

double Especie::distancia(Especie esp) {
  int unio = 0;
  int interseccio = 0;
  map<string,int> kmer2 = esp.consultar_kmer();
  map<string,int>::const_iterator it1 = kmer.begin();
  map<string,int>::const_iterator it2 = kmer2.begin();
  while (it1 != kmer.end() and it2 != kmer2.end()) {
    if (it1->first == it2->first) {
      if (it1->second >= it2->second) {
        unio += it1->second;
        interseccio += it2->second;
      }
      else {
        unio += it2->second;
        interseccio += it1->second;
      }
      it1++; it2++;
    }
    else if (it1->first > it2->first) {
      unio += it2->second;
      it2++;
    }
    else {
      unio += it1->second;
      it1++;
    }
  }

  while (it1 != kmer.end()) {
    unio += it1->second;
    it1++;
  }

  while (it2 != kmer2.end()) {
    unio += it2->second;
    it2++;
  }
  double dist = (double)interseccio/unio;
  return (1-dist) * 100;
}

void Especie::leer_especie() {
  cin >> idn >> gen;
  hacer_kmer();
}

void Especie::imprime_especie() const {
  cout << idn << " " << gen << endl;
}
