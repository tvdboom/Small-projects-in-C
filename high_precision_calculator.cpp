// Programmeer methode Marco Trueba van den Boom
// Gebruikte compiler: Bloodshed Dev-C++ 4.9.9.2
// Datum: 7/12/2012
// Dit programma stelt u in staat met grote getallen te werken

#include <iostream>
#include <cmath> //om de macht van k te berekenen

using namespace std;

const int k = 4; //aantal cijfers per cijfervakje
const int MAX = pow(10,k);

class cijfervakje {
	public:
		int getal;
		cijfervakje* vorige;
		cijfervakje* volgende;
}; //cijfervakje

class grootgetal {
	public:
		grootgetal(); //constructor
		void kopieer(grootgetal & gg);
		void print();
		void telop(grootgetal & gg1, grootgetal & gg2);
		void fibonacci(int eengetal);
		void voor(int eengetal);
		void achter(int eengetal);
		void kapotmaken();

	private:
		int aantal;
		cijfervakje* begin;
		cijfervakje* einde;
}; //grootgetal

grootgetal::grootgetal () {
	begin = NULL; //beginwaarden van de pointers en het aantal cijfervakjes
	einde = NULL;
	aantal = 0;
} //grootgetal

//kopieer het ene grootgetal in het andere
void grootgetal::kopieer(grootgetal & gg) {
	cijfervakje *p = gg.einde; //hulppointer
	kapotmaken();
	while (p != NULL) {
		voor(p->getal);
		p = p->vorige;
	} //while
} //kopieer

//voeg een cijfervakje met een gegeven getal voor het grote getal
void grootgetal::voor(int eengetal){
	int hulp;	
	do {
		hulp = eengetal % MAX;
		cijfervakje *p = new cijfervakje; //maak nieuw cijfervakje aan
		p->vorige = NULL;
		if (begin == NULL) //als het getal leeg is...
			einde = p;
		else
			begin->vorige = p;
   	p->volgende = begin;
		begin = p;
		p->getal = hulp;
		eengetal /= MAX;
	} while (eengetal != 0);
} //voor

//voeg een cijfervakje met een gegeven getal achter het grote getal
void grootgetal::achter(int eengetal){
	grootgetal hulp; //hulp grootgetal
	hulp.voor(eengetal);
	cijfervakje *p = einde;
	while (p != NULL) {
		hulp.voor(p->getal);
		p = p->vorige;
	} //while
	kopieer(hulp);
} //achter

void grootgetal::print() { //zet groot getal op scherm
	cijfervakje *p = begin; //hulppointer wijst naar het begin
	if ( p == NULL) //als het getal geen cijfervakjes heeft
		cout << "leeg";
	while (p != NULL) {
		//extra nullen erbij printen tenzij het het eerste vakje is
		if (p->getal < 100 && p != begin)
			cout << '0';
		if (p->getal < 10 && p != begin)
			cout << '0';		
		cout << p->getal << " ";
		p = p->volgende;
	} //for
} //print

//tel twee grote getallen op en slaat het resultaat op in het derde
void grootgetal::telop(grootgetal & gg1, grootgetal & gg2){
	int extra = 0; //extra 1 die opgeteld moet worden
	cijfervakje *p1 = gg1.einde; //hulppointers die naar het einde wijzen
	cijfervakje *p2 = gg2.einde;
	kapotmaken();	
	while (p1 != NULL && p2 != NULL) { //als bijde getallen nog cijfervakjes hebben...
		voor((p1->getal + p2->getal + extra) % MAX);		
		if (p1->getal + p2->getal + extra >= MAX)
			extra = 1; //getal is groter dan 999 dus 1 erbij bij volgend cijfervakje
		else
			extra = 0;
		p1 = p1->vorige; //vorig cijfervakje
		p2 = p2->vorige;
	} //while
	while (p1 != NULL) { //weer hetelfde maar alleen met een grootgetal
		voor((p1->getal + extra) % MAX);
		if (p1->getal + extra >= MAX)
			extra = 1;
		else
			extra = 0;
		p1 = p1->vorige;
	} //while
	while (p2 != NULL) {
		voor((p2->getal + extra) % MAX);
		if (p2->getal + extra >= MAX)
			extra = 1;
		else
			extra = 0;
		p2 = p2->vorige;
	} //while
	if (extra == 1) //de laatste 1 erbij voegen als beide getallen klaar zijn
		voor(1);
} //telop

//zet het n-de fibonaccigetal in het grote getal
void grootgetal::fibonacci(int eengetal){
	double secs = time (NULL); //tijd nu
	int i; //teller
	grootgetal vorige1, vorige2;
	vorige1.voor(1); //vorige 1 en 2 beginnen op 1
	vorige2.voor(1);
	kapotmaken();
	if (eengetal == 1 || eengetal == 2)
		voor(1); //als de 1ste of 2de gevraagd wordt is het antwoord 1
	else {
		for (i=3;i<=eengetal;i++) {
			telop(vorige1,vorige2); //tel de twee vorige getallen op
			vorige2.kopieer(vorige1);
			vorige1.kopieer(*this);
		} //for	
	} //else
	secs = time (NULL) - secs; //tijd nu min verstreken seconden
	cout << endl << "De tijd gebruikt voor het uitrekenen van het getal was ";
	cout << secs << " seconden." << endl;
} //fibonacci

void grootgetal::kapotmaken(){ //verwijder alle cijfervakjes van het grote getal
	cijfervakje *p;	
	while (begin != NULL) {
		p = begin;
		begin = begin->volgende;
		delete p; //vernietig cijfervakje p
	} //while
	einde = NULL;
} //kapotmaken

char invoer() { //invoer van een karakter		
	char kar,faalkar;			
	cin.get(kar);
	while (kar == '\n') //negeer de enters
		cin.get(kar);
	cin.get(faalkar);
	while (faalkar != '\n') //negeer alles na het eerste karakter
		cin.get(faalkar);
	return kar;
} //invoer

int getalinvoer() { //invoer van een getal
	char kar;
	int getal = 0;			
	cin.get(kar);
	while (kar == '\n')
		cin.get(kar);
	while (kar != '\n') {
		if (kar >= '0' && kar <= '9') //negeer alle niet-cijfers
			getal= 10 * getal + kar - '0';	
		cin.get(kar);	
	} //while
	return getal;
} //getalinvoer

int main () {
	cout << endl << endl << "Welkom! Dit programma stelt u in staat met grote ";
	cout << "getallen te rekenen.";	
	cout << endl << endl << "Dit programma is gemaakt door Marco Trueba van den";
	cout << " Boom (studentnummer 1246984) aan de universiteit Leiden in ";
	cout << " opdracht van Dr. Kosters voor het vak Programmeermethode.";
	cout << " Inleverdatum 07-12-2012.\n\nKies een van de letters tussen haakjes om";
	cout << " die optie van het menu te kiezen.\nAlleen het eerste karakter ";
	cout << "wordt ingelezen.\n\nHet getal waarmee je aan het werken bent, staat";
	cout << " boven het menu. Alle opties van het menu zullen met dat getal werken.";
	cout << " Als je optelt, tel je de andere twee getallen op en zet je het ";
	cout << "antwoord en het getal dat boven staat.\n\nOm van getal te veranderen";
	cout << " kies de optie getal van het menu.\n\nDruk op ENTER om verder te gaan.\n\n";
	cin.get();//zorgt ervoor dat het programma pas verder gaat als je op enter drukt.

	int i = 0; //grootgetal 0, 1 of 2 (0 is startwaarde)
	int eengetal;	
	char kar; //ingelezen karakter
	char gebruik = 'A'; //getal dat gebruikt wordt (A is startwaarde)
	char nietgeb1 = 'B', nietgeb2 = 'C'; //niet gebruikte getallen
	bool exit = false; //run het menu ja of nee
	grootgetal gg[3]; //creer 3 objecten van klasse grootgetal
	while (exit == false) {
		//hoofdmenu
		cout << endl << endl << "HOOFDMENU" << endl << "Het getal " << gebruik;
		cout << " wordt nu gebruikt." << endl << endl << "(G)etal" << endl;
		cout << "(P)rint" << endl << "(M)aak" << endl << "(V)oor" << endl;
		cout << "(A)chter" << endl << "(T)elop" << endl << "(F)ibonacci";
		cout << endl << "(K)apotmaken" << endl << "(S)luit" << endl << endl;
		kar = invoer();
		switch (kar) {
			case 'g':
			case 'G':
				cout << "Welk getal wilt u gebruiken: A, B of C?" << endl;
				gebruik = invoer();	
				//als de gebruiker niet a,b,of c kiest...				
				while (!((gebruik >= 'a' && gebruik <= 'c') ||
				(gebruik >= 'A' && gebruik <= 'C'))) {
					cout << "Kies uit A, B of C." << endl;	//foutmelding
					gebruik = invoer();
				} //while
				if (gebruik == 'a' || gebruik == 'A') {
					i = 0;
					nietgeb1 = 'B';
					nietgeb2 = 'C';				
				} else if (gebruik == 'b' || gebruik == 'B') {
					i = 1;
					nietgeb1 = 'A';
					nietgeb2 = 'C';
				} else {
					i = 2;
					nietgeb1 = 'A';
					nietgeb2 = 'B';
				} //if		 
				break;

			case 'p':
			case 'P':
				cout << endl << "Het getal " << gebruik << " is ";
            gg[i].print();			 
				break;

			case 't':
			case 'T':
				gg[i].telop(gg[(i+1)%3], gg[(i+2)%3]);
				cout << endl << "Getal " << nietgeb1 << ": ";
				gg[(i+1)%3].print();
				cout << endl << "Getal " << nietgeb2 << ": ";
				gg[(i+2)%3].print();
				cout << endl << "Som:   ";
				gg[i].print();
				break;
	
			case 'f':
			case 'F':			 
				cout << endl << "Welk fibonaccigetal wilt u in " << gebruik;
				cout << " invoeren?" << endl;
				eengetal = getalinvoer();	
				while (eengetal > 1000000 || eengetal < 1) {
					cout << "Het getal moet tussen 1 en 100000 zijn." << endl;	
					eengetal = getalinvoer();
				} //while           
				gg[i].fibonacci(eengetal);
				cout << endl << gebruik << " is nu het fibonaccigetal ";
				gg[i].print();
				cout << "." << endl;				
				break;

			case 'v':
			case 'V':
				cout << endl << "Welk getal wilt u voor " << gebruik << " invoeren?" << endl;
				eengetal = getalinvoer();	
				while (eengetal > 100000000) { //het mag niet te gek worden
					cout << "Het getal moet kleiner dan 100000000 zijn." << endl;	
					eengetal = getalinvoer();
				} //while
				gg[i].voor(eengetal);
				cout << endl << eengetal << " is succesvol voor " << gebruik;
				cout << " geplaatst!" << endl;       
			   break;

			case 'a':
			case 'A':
				cout << endl << "Welk getal wilt u achter " << gebruik << " invoeren?" << endl;
				eengetal = getalinvoer();	
				while (eengetal > 100000000) {
					cout << "Het getal moet kleiner dan 100000000 zijn." << endl;	
					eengetal = getalinvoer();
				} //while
				gg[i].achter(eengetal);
				cout << endl << eengetal << " is succesvol achter " << gebruik;
				cout << " geplaatst!" << endl;       
			   break;

			case 'm':
			case 'M':			 
				cout << endl << "Welk getal wilt u in plaats van " << gebruik << " ?" << endl;
				eengetal = getalinvoer();	
				while (eengetal >= 100000000) { 
					cout << "Het getal moet kleiner dan 100000000 zijn." << endl;	
					eengetal = getalinvoer();
				} //while
				gg[i].kapotmaken();        
				gg[i].voor(eengetal);
				cout << endl << gebruik << " is nu " << eengetal << "." << endl;
				break;

			case 'k':
			case 'K':			 
				gg[i].kapotmaken();
				cout << endl << gebruik << " is succesvol vernietigd!" << endl;
				break;

			case 's':
			case 'S':
				cout << endl << "Het programma wordt afgesloten." << endl;	 
            exit = true; //het menu runt niet meer (einde programma)
				break;
			} //switch hoofdmenu
	} //while
} //main


