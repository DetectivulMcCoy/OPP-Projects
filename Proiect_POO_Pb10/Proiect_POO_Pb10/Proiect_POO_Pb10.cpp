
#include <iostream>
using namespace std;
class ListaDubluInlantuita;
class Nod
{
	float valoare;           ///valoarea
	Nod* backN;              ///legatura la stanga
	Nod* nextN;              ///legatura la dreapta
	Nod() { backN = NULL; nextN = NULL; } ///Constructor
	Nod(float valoare);
	Nod(float valoare, Nod* backN, Nod* nextN);
	Nod(const Nod& fromNod); ///Constructor de copiere
	~Nod() { backN = NULL; nextN = NULL; }; ///Destructor
	friend class ListaDubluInlantuita;
	friend ListaDubluInlantuita operator+ (const ListaDubluInlantuita& list1, const ListaDubluInlantuita& list2);
	friend ostream& operator<< (ostream& outList, const ListaDubluInlantuita& listaCurenta);
};

Nod::Nod(float valoare)
{
	this->valoare = valoare;
	this->backN = NULL;
	this->nextN = NULL;
}

Nod::Nod(float valoare, Nod* backN, Nod* nextN)
{
	this->valoare = valoare;
	this->backN = backN;
	this->nextN = nextN;
}

Nod::Nod(const Nod& fromNod)
{
	valoare = fromNod.valoare;
	backN = fromNod.backN;
	nextN = fromNod.nextN;
}

class ListaDubluInlantuita
{
	Nod* prim;      ///primul nod al listei
	Nod* ultim;     ///ultimul nod al listei
	void inserareInceput(float valoare);
	void inserareSfarsit(float valoare);
	void golireLista();
public:
	ListaDubluInlantuita(); ///Constructor
	ListaDubluInlantuita(const ListaDubluInlantuita& dinLista); ///Constructor de copiere
	~ListaDubluInlantuita(); ///Destructor
	void inserareInPozitie(float valoare, int poz);
	void stergerePozitie(int pozitieDeSters);
	ListaDubluInlantuita& operator= (const ListaDubluInlantuita& listaCurenta);
	friend ListaDubluInlantuita operator+ (const ListaDubluInlantuita& list1, const ListaDubluInlantuita& list2);
	friend ostream& operator<< (ostream& out, const ListaDubluInlantuita& listaCurenta);
	friend istream& operator>> (istream& input, ListaDubluInlantuita& listaCurenta);
};


ListaDubluInlantuita::ListaDubluInlantuita()
{
	prim = NULL;
	ultim = NULL;
}

ListaDubluInlantuita::ListaDubluInlantuita(const ListaDubluInlantuita& dinLista)
{
	prim = NULL;
	int pozitiaCurenta = 0;
	Nod* nodCurent = dinLista.prim;
	while (nodCurent != NULL)
	{
		inserareInPozitie(nodCurent->valoare, pozitiaCurenta);
		pozitiaCurenta++;
		nodCurent = nodCurent->nextN;
	}
}

ListaDubluInlantuita::~ListaDubluInlantuita()
{
	golireLista();
}

void ListaDubluInlantuita::golireLista()
{
	Nod* current;
	while (prim != NULL)
	{
		current = prim;
		prim = prim->nextN;
		delete (current);
	}

}

void ListaDubluInlantuita::inserareInceput(float valoare)
{
	if (prim == NULL)
	{
		prim = new Nod(valoare);
		prim->nextN = NULL;
		prim->backN = NULL;
		ultim = prim;
	}
	else
	{
		Nod* nou = new Nod(valoare);
		nou->nextN = prim;
		prim->backN = nou;
		prim = nou;
		prim->backN = NULL;
	}
}

void ListaDubluInlantuita::inserareSfarsit(float valoare)
{
	if (prim == NULL) ///daca lista e vida
	{
		prim = new Nod(valoare);
		prim->nextN = NULL;
		prim->backN = NULL;
		ultim = prim;
	}
	else
	{
		Nod* curent = new Nod(valoare);
		ultim->nextN = curent;
		curent->backN = ultim;
		ultim = curent;
		ultim->nextN = NULL;
	}
}

void ListaDubluInlantuita::inserareInPozitie(float valoare, int poz)
{   ///consideram ca prima pozitie este 0
	///daca pozitia depaseste lungimea listei vom introduce elementul la sfarsit
	///daca pozitia este negativa vom introduce elementul la inceput

	/*if ( poz < 0 )
	{
		cout<<"Introduceti pozitia mai mare sau egal cu zero!";
		return;
	}*/
	Nod* curent;
	curent = prim;
	while (curent != NULL && poz > 0)
	{
		poz--;
		curent = curent->nextN;
	}

	if (curent == NULL)
	{
		inserareSfarsit(valoare);
		return;
	}

	if (curent != prim)
	{
		Nod* nou = new Nod(valoare);
		nou->nextN = curent;
		(curent->backN)->nextN = nou;
		nou->backN = curent->backN;
		curent->backN = nou;
		return;
	}
	else
	{
		inserareInceput(valoare);
		return;
	}
}

void ListaDubluInlantuita::stergerePozitie(int pozitieDeSters)
{
	Nod* curent = prim;

	if (pozitieDeSters < 0)
	{
		//cout<<"Introduceti pozitia mai mare sau egal cu zero!\n";
		return;
	}
	while (curent != NULL && pozitieDeSters > 0)
	{
		pozitieDeSters--;
		curent = curent->nextN;
	}
	/// In acest caz nu putem sterge nimic
	if (curent == NULL)
	{
		return;
	}
	/// In cazul in care curent este egal cu prim stergem primul element
	else if (curent == prim)
	{
		/// caz special daca este unicul element al listei
		if (prim == ultim)
		{
			prim = NULL;
			ultim = NULL;
		}
		else
		{
			prim = prim->nextN;
			prim->backN = NULL;
			delete curent;
		}
	}
	else if (curent == ultim)
	{
		ultim = ultim->backN;
		ultim->nextN = NULL;
		delete curent;
	}
	else
	{
		Nod* backN = curent->backN;
		Nod* nextN = curent->nextN;
		backN->nextN = nextN;
		nextN->backN = backN;
		delete curent;
	}
}

ListaDubluInlantuita& ListaDubluInlantuita::operator= (const ListaDubluInlantuita& listaCurenta)
{
	golireLista();

	int pozitiaCurenta = 0;
	Nod* nodCurent = listaCurenta.prim;
	while (nodCurent != NULL)
	{
		inserareInPozitie(nodCurent->valoare, pozitiaCurenta);
		pozitiaCurenta++;
		nodCurent = nodCurent->nextN;
	}
	return (*this);
}

ListaDubluInlantuita operator+ (const ListaDubluInlantuita& lista1, const ListaDubluInlantuita& lista2)
{
	ListaDubluInlantuita listaObtinuta;
	if (lista1.prim == NULL)
	{
		listaObtinuta = lista2;
	}
	else
	{
		listaObtinuta = lista1;
		Nod* nodCurent = lista2.prim;
		while (nodCurent != NULL)
		{
			listaObtinuta.inserareSfarsit(nodCurent->valoare);
			nodCurent = nodCurent->nextN;
		}
	}
	return listaObtinuta;
	/// varianta cu inserareInPozitie
/*    ListaDubluInlantuita listaObtinuta;
	int pozitiaCurenta = 0;
	Nod *nodCurent = lista1.prim;
	while (nodCurent != NULL)
	{
		listaObtinuta.inserareInPozitie(nodCurent->valoare, pozitiaCurenta);
		pozitiaCurenta++;
		nodCurent = nodCurent->nextN;
	}
	nodCurent = lista2.prim;
	while (nodCurent != NULL)
	{
		listaObtinuta.inserareInPozitie(nodCurent->valoare, pozitiaCurenta);
		pozitiaCurenta++;
		nodCurent=nodCurent->nextN;
	}
	return listaObtinuta;*/
}

ostream& operator<< (ostream& out, const ListaDubluInlantuita& listaCurenta)
{
	Nod* curent;
	curent = listaCurenta.prim;
	if (curent == NULL)
		out << "Lista este vida.";
	else
		while (curent != NULL)
		{
			out << curent->valoare << " ";
			curent = curent->nextN;
		}
	out << endl;
	curent = listaCurenta.ultim;
	if (curent == NULL)
		out << "Lista este vida.";
	else
		while (curent != NULL)
		{
			out << curent->valoare << " ";
			curent = curent->backN;
		}
	return out;
}

istream& operator>> (istream& input, ListaDubluInlantuita& listaCurenta)
{
	int i, dim;
	float valoare;
	cout << "Nr elemente: ";
	input >> dim;
	listaCurenta.golireLista();
	for (i = 0; i < dim; i++)
	{
		cout << "Valoarea elementului de pe pozitia " << i << ": ";
		input >> valoare;
		listaCurenta.inserareInPozitie(valoare, i);
	}
	return input;
}

class Vector {
private:
	int n; //dimensiunea vectorului
	ListaDubluInlantuita* t; //pointer catre zona de memorie alocata dinamic
public:
	Vector(int n); //Constructor
	Vector(const Vector& v); //Constructor de copiere
	~Vector(); //Destructor
	void citire();
	void afisare();
};

Vector::Vector(int n)
{
	this->n = n;
	this->t = new ListaDubluInlantuita[n];
	//cout<<"Apel constructor cu parametri"<<endl;
}
Vector::Vector(const Vector& v)
{
	int i;
	this->n = v.n;
	this->t = new ListaDubluInlantuita[n];
	for (i = 0; i < n; i++)
		this->t[i] = v.t[i];
	//cout<<"Apel constructor de copiere"<<endl;
}
Vector::~Vector()
{
	delete[]t;
	//cout<<"Apel destructor"<<endl;
}

void Vector::citire()
{
	cout << "Introduceti listele:" << endl;
	for (int i = 0; i < n; i++)
		cin >> t[i];
}
void Vector::afisare() {
	for (int i = 0; i < n; i++)
		cout << t[i] << endl;

	cout << endl;
}

int main()
{
	ListaDubluInlantuita lista1;

	//Citire folosind operatorul >>
	cin >> lista1;

	//Afisare folosind operatorul <<
	cout << "Lista inainte de inserare:\n" << lista1 << endl;

	//Inserare elemente in lista
	lista1.inserareInPozitie(98, 0);
	lista1.inserareInPozitie(96, 1);
	lista1.inserareInPozitie(97, 1);

	//Afisare folosind operatorul <<
	cout << "Lista dupa inserare:\n" << lista1 << endl;

	// Stergere elemente
	lista1.stergerePozitie(3);
	//cout << lista1 << endl;
	lista1.stergerePozitie(1);
	//cout << lista1 << endl;
	lista1.stergerePozitie(0);

	cout << "Lista dupa stergere:\n" << lista1 << endl;

	//Construim o lista noua folosind constructorul de copiere
	ListaDubluInlantuita lista2 = lista1;
	//Afisare copie creata
	cout << "Lista creata cu constructor copiere:\n" << lista2 << endl;

	ListaDubluInlantuita lista3;
	// Operator =
	lista3 = lista2;
	cout << "Lista dupa operator =\n" << lista3 << endl;

	// Operator +
	cout << "Suma:\n" << lista1 + lista2 << endl;

	lista2.inserareInPozitie(333, 1);
	cout << "Suma:\n" << lista2 + lista3 << endl;

	cin >> lista3;
	cout << "Suma:\n" << lista3 + lista2 << endl;

	// citirea informa?iilor complete a n obiecte, memorarea ?i afisarea acestora
	// citire dimensiune
	cout << "Citirea informatiilor complete a n obiecte si afisarea acestora\n";
	int n;
	cout << "Numarul de liste: ";
	cin >> n;
	Vector v(n);

	v.citire();
	cout << "Afisarea listelor\n";
	v.afisare();

	return 0;
}
