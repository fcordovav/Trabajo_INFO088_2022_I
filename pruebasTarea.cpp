#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include <list>
using namespace std;

struct nodeDoubleList
{
	int val;
	nodeDoubleList* prev;
	nodeDoubleList* next;
};
typedef struct nodeDoubleList nodoD;

void lexicQuickSort(vector<int> &lexic, int l, int r, char *T);
int lexicpartition(vector<int> &lexic, int l, int r, char *T);
bool comparaLexicoT(char *T,int pos,int pos2);
bool comparaLexicoP(char *T,char *P,char *O,int pos);
int patternMatching(vector<int> &lexi, int n, int m, char *T, char *P);
void appendToListL(nodoD **l, int num);
void printList(nodoD *l);

int main()
{

  //char T[] = {"AABAACAADBAAABAABA"};
  char T[]={"AABAACAADBAAABAABADCDADDADADADCADBBADAABADCADAABADADACDADBAABA"};
  char P[] = {"AABA"};
  int nT = strlen(T), mP = strlen(P), i, cont = 0,b,e;
  nodoD *lexic = NULL;

  for (i=1; i<=10; i++){
		int x = i;
		appendToListL(&lexic, x); // agregamos x por la izquierda
	}
  cout << "lexic = ";
	printList(lexic);

  lexicQuickSort(lexic, 0, nT-1, T);
  e = patternMatching(lexic, nT-1, mP-1, T, P);

  return 0;
}

//Ordena lexicograficamente las pocisiones del texto adaptando Quicksort
void lexicQuickSort(vector<int> &lexic, int l, int r, char *T)
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
int lexicpartition(nodoD &lexic, int l, int r, char *T)
{
  int p, pv, i;
  
  p = l;
  pv = lexic.val; //pivote
  
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
bool comparaLexicoT(char *T,int pos,int pos2)
{
  int a,b;
  a=pos;b=pos2;
  unsigned int i;
  if(pos<pos2)
  {
    for(i=0;pos2+1<strlen(T) && i<=(strlen(T)-pos2) && T[pos2]==T[pos];i++)
    {
      pos++;
      pos2++;
    }
    if(T[pos2]<=T[pos])
    {
      return true;
    }
  }
  else
  {
    for(i=0;pos+1<strlen(T) && i<=(strlen(T)-pos) && T[pos2]==T[pos];i++)
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
int patternMatching(vector<int> &lexic, int n, int m, char *T, char *P)
{
  int b,t,s,e;
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
  cout << b << " " << e << endl;
  int cont = 0;
  for(int i = b; i<e; i++){
    cont = cont + 1;
  }
  return cont;
}


//Compara el tamaño lexicografico de una posicion del texto con P
bool comparaLexicoP(char *T,char *P,char *O,int pos)
{
  unsigned int i;
  int cont = 0; // variable contador
  for(i=0;i<strlen(P)-1 && pos+i<strlen(T) && P[i]==T[pos+i]; i++)
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

//Funciones listas enlazadas
void appendToListL(nodoD **l, int num)
{
	nodoD *nuevo = new nodoD();
	nuevo->val = num;
	if(*l == nullptr)
  {
		*l = nuevo;
	}else{
		nodoD *p = *l;
		while(p->next != nullptr)
    {
			p = p->next;
		}
		p->next = nuevo;
		nuevo->next = NULL;
		nuevo->prev = p;
	}
}

void printList(nodoD *l)
{
	nodoD *p = l;
	//cout << "Lista :" << endl;
	while (p != nullptr)
  {
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}
Node* partition(Node *l, Node *h)
{
    // set pivot as h element
    int x = h->data;
 
    // similar to i = l-1 for array implementation
    Node *i = l->prev;
 
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Node *j = l; j != h; j = j->next)
    {
        if (j->data <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
 
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->data), &(h->data));
    return i;
}
 
/* A recursive implementation
of quicksort for linked list */
void _quickSort(Node* l, Node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        Node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}
 
// The main function to sort a linked list.
// It mainly calls _quickSort()
void quickSort(Node *head)
{
    // Find last node
    Node *h = lastNode(head);
 
    // Call the recursive QuickSort
    _quickSort(head, h);
}
 
// A utility function to print contents of arr
void printList(Node *head)
{
    while (head)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}