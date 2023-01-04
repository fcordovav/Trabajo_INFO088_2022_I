#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

#define TEST 0

//Main related
vector<char> lectura(char *nombreArchivo);
void runExperiments(vector<char> &T, char *patron, vector<int> &lexic, int n, int m);
void testBusqueda(vector<int> lexic);

//Busqueda Exaustiva
int busquedaExaustiva(vector<char> &T, char *patron);

//Busqueda Lista
int busquedaLista(vector<char> &T, char *patron);

//Busqueda Array
void lexicQuickSort(vector<int> &lexic, int l, int r, vector<char> &T);
int lexicpartition(vector<int> &lexic, int l, int r, vector<char> &T);
bool comparaLexicoT(vector<char> &T,int pos,int pos2);
int busquedaArray(vector<int> &lexic, int n, int m, vector<char> &T, char *P);
bool comparaLexicoP(vector<char> &T,char *P,char *O,int pos);

int main(int argc, char **argv)
{	
	if(argc != 3)
	{
		cout << "Error. Debe ejecutarse como ./tarea nombreArchivo.tipoDeArchivo patron" << endl;
		exit(EXIT_FAILURE);
	}
  char *nombreArchivo = argv[1];
  char *patron = argv[2];

  cout << "_________________________________________________" << endl;
	cout << " Leyendo el archivo... " << endl;
  vector<char> T = lectura(nombreArchivo);
  cout << " lectura finalizada " << endl;

  int nT = T.size(), mP = strlen(patron), i;
  vector<int> lexic;

  if(TEST)
		testBusqueda(lexic);

  //Ordena el texto lexicograficamente en un Array
  cout << "_________________________________________________" << endl;
	cout << " Creando vector de posiciones... " << endl;
  for(i=0;i<nT;i++)
  {
    lexic.push_back(i);
  }
  cout << " vector de posiciones creado " << endl;

  cout << "_________________________________________________" << endl;
	cout << " Ordenando lexicograficamente... " << endl;
  lexicQuickSort(lexic, 0, nT-1, T);
   cout << " posiciones ordenadas lexicograficamente " << endl;
  //Fin de ordenamiento lexicografico

  runExperiments(T, patron, lexic, nT-1, mP-1);
  
  cout << "### Fin Tarea ###" << endl;
	return EXIT_SUCCESS;
}
//Fin main


//Abre el archivo y retorna el texto en un arreglo de chars
vector<char> lectura(char *nombreArchivo)
{
  vector<char> T;
  char letra = 0; 
  
  //Abrimos el archivo
  ifstream archivo(nombreArchivo);
  if(archivo.fail())
  {
    cout << "No se pudo abrir el archivo";
    exit(1);
  }
  
  //Guardamos el archivo en un arreglo de chars
  while (archivo.get(letra))
  {
    T.push_back(letra);
  }
  archivo.close();
  
  //Retornamos el texto
  return T;
}

//Realiza la busqueda exaustiva
int busquedaExaustiva(vector<char> &T, char *patron)
{
  int i, j, rep=0, cont=0;
  int length = strlen(patron);

  for(i=0; i<T.size();i++)
  {
    for(j=0;j<length;j++)
    {
      if(T[i+j] == patron[rep])
      {
        if(rep+1 == length)
        {
          cont++;
          rep=0;
        }
        rep++;
      }
    }
    rep=0;
  }
  return cont;
}

//Realiza la busqueda con Array
void lexicQuickSort(vector<int> &lexic, int l, int r, vector<char> &T)
{
  int p;

  if(l < r)
  {
    p = lexicpartition(lexic, l, r, T);
    lexicQuickSort(lexic, l, p-1, T);
    lexicQuickSort(lexic, p+1, r, T);
  }
}

//particion del Quicksort adaptada a este problema
int lexicpartition(vector<int> &lexic, int l, int r, vector<char> &T)
{
  int p, pv, i;

  p = l;
  pv = lexic[p]; //pivote
  
  for(i=l+1;i<=r;i++)
  {
    if(comparaLexicoT(T, pv, lexic[i]))
    {
      p++;
      swap(lexic[i], lexic[p]);
    }
  }
  swap(lexic[l], lexic[p]);
  
  return p;

}

//Compara el tamaño lexicografico de dos posiciones distintas del texto
bool comparaLexicoT(vector<char> &T,int pos,int pos2)
{
  unsigned int i;
  if(pos<pos2)
  {
    for(i=0;pos2+1<T.size() && i<=(T.size()-pos2) && T[pos2]==T[pos];i++)
    {
      pos++;
      pos2++;
    }
    if(pos2<T.size() && T[pos2]<=T[pos])
    {
      return true;
    }
  }
  else
  {
    for(i=0;pos+1<T.size() && i<=(T.size()-pos) && T[pos2]==T[pos];i++)
    {
      pos++;
      pos2++;
    }
    if(T[pos2]<T[pos])
    {
      return true;
    }
  }
  return false;
}

//Comprueba las posiciones en las que ocurra la ocurrencia del patron y los guarda en un vector.
//Se usa el orden lexicografico para, una vez encontrada la primera ocurrencia, se agreguen las siguientes pociciones lexicograficamente mayores hasta que deje de aparecer el patron,
//de esta forma ya se habran encontrado todas las ocurrencias del patron sin necesidad de recorrer todo el texto. 
int busquedaArray(vector<int> &lexic, int n, int m, vector<char> &T, char *P)
{
  int b,t,s,e,cont=0;
  b = 0;
  t = n;
  while(b<t)
  {
    s = (b+t)/2;
    if(comparaLexicoP(T,P,"mayo",lexic[s]))
      b=s+1;
    else
      t = s;
  }
  e = b - 1;
  t = n;
  while(e < t)
  {
    s = (e+t)/2;
    if(comparaLexicoP(T,P,"igu",lexic[s]))
      e = s + 1;
    else
      t = s - 1;
  }

  for(int i=b;i<e;i++)
  {
    cont++;
  }
  return cont;
}

//Compara el tamaño lexicografico de una posicion del texto con P
bool comparaLexicoP(vector<char> &T,char *P,char *O,int pos)
{
  unsigned int i;
  int cont = 0; // variable contador
  for(i=0;i<strlen(P)-1 && pos+i<T.size() && P[i]==T[pos+i]; i++)
  {
    cont++;
  }
  if(O == "mayo"){
    if(P[cont]>T[pos+cont])
    {
      return true;
    }
  }
  if(O == "igu"){
    if(P[cont]==T[pos+cont])
    {
      return true;
    }
  }
  return false;
}
//Fin de la busqueda con arrray


//Realiza la busqueda con Lista doble
int busquedaLista(vector<char> &T, char *patron)
{
  return 0;
}

//Experimentos para comprobar el rendimiento de las funciones de busqueda
void runExperiments(vector<char> &T, char *patron, vector<int> &lexic, int n, int m)
{
	int nOcc1, /*nOcc2,*/ nOcc3;
	float avgT1, /*avgT2,*/ avgT3;
	clock_t t;
  

	cout << "_________________________________________________" << endl;
  
  //Experimento busqueda exaustiva
	t = clock();
	nOcc1 = busquedaExaustiva(T,patron);
	t = clock() - t;
	avgT1 = (float)t/CLOCKS_PER_SEC;
	avgT1 = (avgT1*1000.0);
	cout << "Búsqueda exaustiva..." << endl;
	cout << "Tiempo promedio de CPU: " << avgT1 << " ms" << endl;
	cout << nOcc1 << " ocurrencias de " << patron << " en el texto" << endl << endl;

  //Experimento busqueda que usa una Lista
	/*t = clock();
  nOcc2 =	busquedaLista(T,patron);
	t = clock() - t;
	avgT2 = (float)t/CLOCKS_PER_SEC;
	avgT2 = (avgT2*1000.0);
	cout << "Búsqueda con lista doblemente enlasada..." << endl;
	cout << "Tiempo promedio de CPU: " << avgT2 << " ms" << endl;
	cout << nOcc2 << " ocurrencias de " << patron << " en el texto" << endl << endl;*/

  //Experimento busqueda que usa un Array
	t = clock();
	nOcc3 = busquedaArray(lexic, n, m, T, patron);
	t = clock() - t;
	avgT3 = (float)t/CLOCKS_PER_SEC;
	avgT3 = (avgT3*1000.0);
	cout << "Búsqueda con array..." << endl;
	cout << "Tiempo promedio de CPU: " << avgT3 << " ms" << endl;
	cout << nOcc3 << " ocurrencias de " << patron << " en el texto" << endl;
}

void testBusqueda(vector<int> lexic)
{
	int i, ocu1, ocu2, ocu3;
  vector<char> T;
  char A[]={"AABAACAADBAAABAABADCDADDADADADCADBBADAABADCADAABADADACDADBAABA"};
  for(i=0;i<strlen(A);i++)
  {
    T.push_back(A[i]);
  }
  
  char P[] = {"AABA"};

  for(i=0;i<T.size();i++)
  {
    lexic.push_back(i);
  }
  lexicQuickSort(lexic, 0, T.size()-1, T);
  
	cout << "_________________________________________________" << endl;
	cout << "  Executing Test " << endl;

	// creamos numeros aleatorios
  ocu1 = busquedaExaustiva(T,P);
  //ocu2 = busquedaLista(v,x);
  ocu3 = busquedaArray(lexic,T.size(), strlen(P) , T, P);
  if (ocu1 /*!= ocu2*/ != ocu3 )
  {
    cout << "ERROR ! para P= ";
    for(i=0;i<strlen(P);i++)cout << P[i] << " ";
    cout << endl;
    cout << "busquedaExaustiva(T,patron) = " << ocu1 << endl;
    cout << "busquedaLista(v,x) = " << ocu2 << endl;
    cout << "busquedaArray(lexic, n, m, T, patron) = " << ocu3 << endl;

    exit(-1);
  }

	cout << "TEST OK !!" << endl;
}
