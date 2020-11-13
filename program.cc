/**
  @mainpage Programa destinat a la creació d'arbres filogenètics.

  <b>Data: </b> 20/05/2020

  <b>Llenguatge: </b> C++

  <b>Versió: </b> 1.0

  <b> Autor: </b> Andrés Eduardo Bercowsky Rama
  @file program.cc

  @brief Aquest és el programa principal
*/
#ifndef NO_DIAGRAM
#include<iostream>
#endif
#include "Cjt_cluster.hh"

using namespace std;

/**
  @brief Programa principal de la pràctica.

  L'objectiu d'aquest programa es treballar amb una serie d'espècies donades per
  construir un arbre filogenetic basant-nos en les igualtats genètiques de les
  espècies.

  En aquest programa, primer de tot llegim un nombre enter que anomenarem k, amb
  el qual procedirem posteriorment a crear els kmers de les especies i el qual
  es mantindrà fixe al llarg de l'execució del programa. Després, procedim a
  llegir una instrucció de les 13 que tenim:

  1. <b>crea_especie:</b> Crea una especie a identificador i gen donats i l'agrega al
  conjunt d'especies. Dóna un error si ja existeix una espècie amb el mateix identificador.

  2. <b>obtener_gen:</b> Donat un identificador, imprimeix el gen d'aquella espècie.
  Dóna un error si l'espècie no existeix.

  3. <b>distancia:</b> Donats dos identificadors d'espècies, imprimeix la distància entre
  ells. Dóna un error si alguna espècie no existeix al conjunt d'espècies.

  4. <b>elimina_especie:</b> Donat un identificador d'espècie, elimina aquella espècie
  del conjunt d'especies. Dóna un error si l'especie no existeix al conjunt.

  5. <b>existe_especie:</b> Donat un identificador, imprimeix si la espècie existeix o no.

  6. <b>lee_cjt_especies:</b> Llegeix un enter n >= 0 i a continuació una seqüència de
  n espècies. Les n espècies tenen identificadors diferents entre si i el contingut
  previ del conjunt es decarta per agregar aquestes noves espècies al conjunt.

  7. <b>imprime_cjt_especies:</b> Imprimeix el conjunt d'espècies.

  8. <b>tabla_distancias:</b> Imprimeix la taula de distàncies de les espècies.

  9. <b>inicializa_clusters:</b> Inicialitza el conjunt de clusters amb el conjut d'espècies
  actual i imprimeix la taula de distàncies entre els clusters.

  10. <b>ejecuta_paso_wpgma:</b> Executa un pas de l'algoritme WPGMA i imprimeix la taula
  de distància dels clusters resultant. Si nº clusters <= 1, imprimeix un error.

  11. <b>imprime_cluster:</b> Donat un identificador, imprimeix el cluster o un error
  si no existeix al conjunt de clusters.

  12. <b>imprime_arbol_filogenetico:</b> Imprimeix l'arbre filogenètic per al conjunt
  d'espècies actual. Aquest arbre és el clúster resultant d'aplicar l'algoritme
  WPGMA. El contingut del conjunt de clusters previ es descarta i s'inicialitza
  amb el conjunt d'espècies actual.

  13. <b>fin:</b> Finalitza l'execució del programa.L'objectiu d'aquest programa es treballar amb una serie d'espècies donades per
  construir un arbre filogenetic basant-nos en les igualtats genètiques de les
  espècies.
*/

int main() {
  Cjt_especies cjt_esp;
  Cjt_cluster cjt_clus;
  Especie esp;
  int k;
  cin >> k;
  esp.inicia_k(k);

  string s;
  cin >> s;

  string idn;
  while (s != "fin") {
    if (s == "crea_especie") {
      Especie e;
      e.leer_especie();
      cout<<"# crea_especie "<<e.consultar_idn()<<" "<<e.consultar_gen()<<endl;
      if (not cjt_esp.crea_especie(e))
        cout << "ERROR: La especie "<<e.consultar_idn()<<" ya existe."<< endl;
    }

    else if (s == "obtener_gen") {
      cin >> idn;
      cout << "# obtener_gen "<< idn<<endl;
      if (cjt_esp.existe_especie(idn)) cout << cjt_esp.obtener_gen(idn) << endl;
      else cout << "ERROR: La especie "<<idn<< " no existe." << endl;
    }

    else if (s == "distancia") {
      string idn2;
      cin >> idn >> idn2;
      cout<<"# distancia "<<idn<<" "<<idn2<<endl;
      bool b_idn = cjt_esp.existe_especie(idn);
      bool b_idn2 = cjt_esp.existe_especie(idn2);
      if (b_idn and b_idn2){
        cout << cjt_esp.distancia_especies(cjt_esp.consultar_especie(idn),
        cjt_esp.consultar_especie(idn2)) << endl;
      }
      else if (not b_idn and not b_idn2)
        cout<<"ERROR: La especie "<<idn<<" y la especie "<<idn2<<" no existen."<<endl;
      else if (not b_idn) cout<<"ERROR: La especie "<<idn<<" no existe."<<endl;
      else cout<<"ERROR: La especie "<<idn2<<" no existe."<<endl;
    }

    else if (s == "elimina_especie") {
      cin >> idn;
      cout<<"# elimina_especie "<<idn<<endl;
      if (not cjt_esp.elimina_especie(idn)) {
        cout << "ERROR: La especie "<<idn<< " no existe." << endl;
      }
    }

    else if (s == "existe_especie") {
      cin >> idn;
      cout<<"# existe_especie "<<idn<<endl;
      if (cjt_esp.existe_especie(idn)) cout << "SI" << endl;
      else cout << "NO" << endl;
    }

    else if (s == "lee_cjt_especies") {
      cout<<"# lee_cjt_especies"<<endl;
      cjt_esp.lee_cjt_especies();
    }

    else if (s == "imprime_cjt_especies") {
      cout<<"# imprime_cjt_especies"<<endl;
      cjt_esp.imprime_cjt_especies();
    }

    else if (s == "tabla_distancias") {
      cout<<"# tabla_distancias"<<endl;
      cjt_esp.tabla_distancias();
    }

    else if (s == "inicializa_clusters") {
      cout<<"# inicializa_clusters"<<endl;
      cjt_clus.inicializa_cluster(cjt_esp);
      cjt_clus.imprime_tabla_dist();
    }

    else if (s == "ejecuta_paso_wpgma") {
      cout<<"# ejecuta_paso_wpgma"<<endl;
      if (cjt_clus.mida_cjt_cluster() > 1) {
        cjt_clus.ejecuta_paso_wpgma();
        cjt_clus.imprime_tabla_dist();
      }
      else cout<<"ERROR: num_clusters <= 1"<<endl;
    }

    else if (s == "imprime_cluster") {
      cin >> idn;
      cout<<"# imprime_cluster "<<idn<<endl;
      if (not cjt_clus.existeix_cluster(idn))
        cout<<"ERROR: El cluster "<<idn<<" no existe."<<endl;
      else {
        cjt_clus.imprime_cluster(cjt_clus.obte_cluster(idn));
        cout << endl;
      }
    }

    else if (s == "imprime_arbol_filogenetico") {
      cout<<"# imprime_arbol_filogenetico"<<endl;
      cjt_clus.inicializa_cluster(cjt_esp);
      cjt_clus.imprime_arbol_filogenetico();
    }
    cout << endl;
    cin >> s;
  }
 }
