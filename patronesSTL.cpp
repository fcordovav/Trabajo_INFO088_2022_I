#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <cstdio>
using namespace std;

string lectura(char *nombreArchivo);
void printOccurrences(string txt, string pat);
 
void printOccurrences(string txt, string pat)
{
  int cont=0;

  int found = txt.find(pat);
  while (found != string::npos) {
      found = txt.find(pat, found + 1);
      cont++;
  }
  cout << cont << endl;
}
 

int main(int argc, char **argv)
{	
	if(argc != 3)
	{
		cout << "Error. Debe ejecutarse como ./tarea nombreArchivo.tipoDeArchivo patron" << endl;
		exit(EXIT_FAILURE);
	}
  char *nombreArchivo = argv[1];
  string patron = argv[2];

  string T = lectura(nombreArchivo);
  //cout << T.length() << endl;

  printOccurrences(T, patron);
  
  
  
  cout << "### Fin Tarea ###" << endl;
	return EXIT_SUCCESS;
}
//Fin main


//Abre el archivo y retorna el texto en un arreglo de chars
string lectura(char *nombreArchivo)
{
  string T;
  char letra = 0; 
  
  FILE * archivo;
    long medida;
    char * texto;
  archivo = fopen (nombreArchivo, "r"); // "r" significa solo lectura, abajo explicaré los modos

  // Las siguientes tres lineas nos permiten conocer la cantidad de texto
  // que tiene el archivo y guardamos este dato en la variable "medida"
  // este dato se necesita para la funcion fread
  fseek (archivo , 0 , SEEK_END);
  medida = ftell (archivo);
  rewind (archivo);

  // La siguiente linea asigna de forma automatica la memoria del archivo completo
  texto = (char*) malloc (sizeof(char)*medida);

  // Ahora por fin almacenamos el texto del archivo en la variable texto
  fread(texto, medida+1, 1, archivo);
  fclose(archivo);
  //Retornamos el texto
  return texto;
}