#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "iostream"
#include "fstream"
#include "MyClass.C"
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>

// Utilizando el espacio de nombres std
using namespace std;


pair<string, vector<string>> splitString(const char* input) {
    // Copiar la cadena de entrada en una cadena modificable
    char* inputCopy = strdup(input);

    string firstWord;
    vector<string> words;

    // Tokenizar la cadena por espacios
    char* token = strtok(inputCopy, " ");
    while (token != nullptr) {
        string word(token);
        words.push_back(word);

        // Verificar si la palabra contiene un punto
        size_t dotPos = word.find('.');
        if (dotPos != string::npos) {
            if (firstWord.empty()) {
                // Solo asignar la primera palabra antes del punto si no se ha asignado previamente
                firstWord = word.substr(0, dotPos);
            }
        }

        token = strtok(nullptr, " ");
    }

    // Liberar la memoria asignada por strdup
    free(inputCopy);

    return make_pair(firstWord, words);
}

void TTreeToCsv_copy( 	const char *  	filename = "../Events/run_01/tag_1_delphes_events.root",
                        const char *  	treename = "Delphes") 	
{
    // Crear una cadena de árboles y agregar el archivo de entrada
    TChain *ch = new TChain(treename, "");
    ch->Add(filename);
    TTree *Delphes = (TTree*)ch;

    // Crear una instancia de la clase MyClass para acceder a las ramas del árbol
    MyClass t(Delphes);

    // Dibujar el tamaño del jet en un histograma
    t.fChain->Draw("Jet_size >> his");
    TH1F *his = (TH1F*)gPad->GetPrimitive("his");

    // Obtener el número de entradas y el tamaño estimado del array
    Int_t nentries = t.fChain->GetEntries();
    Int_t lefn = floor(his->GetMean());

/*
    // Imprimir separadores y estadísticas
    cout << string(100, '*') << endl;
    cout << " Eventos : " << nentries << endl << " Entradas : " << lefn * nentries << endl;

    // Abrir el archivo de salida fuera del bucle
    ofstream salida("outputEta_Phi.csv");
    salida << "Jet_Eta" << " " << "Jet_Phi" << " " << "Particle_Eta" << " " << "Particle_Phi" << endl;

    // Dividir el número de entradas para mostrar el progreso en porcentaje
    Int_t nTen = nentries / 10;
    Int_t k = 0;
    Int_t nbytes = 0, nb = 0;

    // Recorrer todas las entradas del árbol
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        Long64_t ientry = t.LoadTree(jentry);
        if (ientry < 0)
            break;

        nb = t.fChain->GetEntry(jentry);
        nbytes += nb;

        if (jentry % nTen == 0)
            cout << 10 * (jentry / nTen) << "%-" << flush;

        if (jentry == nentries - 1)
            cout << "100%" << endl << "El archivo acaba de ser escrito de forma correcta!" << endl << string(100, '*') << endl;

        // Imprimir todos los elementos de los arrays Jet_Eta y Jet_Phi
        for (Int_t i = 0; i < lefn; ++i)
        {
            salida << t.Jet_Eta[i] << " " << t.Jet_Phi[i] << " " << t.Particle_Eta[i] << " " << t.Particle_Phi[i] << endl;
        }
    }
*/    
}
