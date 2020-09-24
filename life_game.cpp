// Programmeer methode Lieke van Son en Marco Trueba van den Boom. Gebruikte
// compiler: Bloodshed Dev-C++ 4.9.9.2
// Life spelen

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

const int MAX = 1000;
const int HVIEW = 30; //hoogte view
const int BVIEW = 70; //breedte view

// Pseudo-random-getal tussen 0 en 999:
long randomgetal ( ) {
	static long getal = 42;
	getal = ( 221 * getal + 1 ) % 10000;
	return getal;
} // randomgetal

class leven {
	public:
		int v; //stapgrote verschuiving van de vieuw
		int gegrnd; //percentage levende cellen bij random
		char karlevend, kardood; //aantal levende en dode cellen	
		leven(); //constructor
		void schoon();
		void tekenlife();
		void random();
		void eengeneratie();
		void parameters();
		void verschuif();
		void gaan();
		void statistiek();
		void glidergun();

	private:
		int x,y;// x,y coordinaat view
		int levend;//aantal levende cellen
		int percentage; // percentage levende cellen
		int generatie; // huidige generatie
		bool wereld[MAX][MAX];
		bool hulpwereld[MAX][MAX];
};

leven::leven () {
	x = 1;
	y = 1;
	gegrnd = 23;
	v = 10;
	levend = 0;
	karlevend = 'x';
	kardood = ' ';
	generatie = 0;
	percentage = 0;
	schoon();
}

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


void leven::parameters() {	//parameters submenu	 
	char kar;
	bool exit = false;			
	while (exit == false) {
		cout << endl << "Kies een van de opties van het submenu." << endl;
		cout << endl << "(V)erschuivingsstapgrootte  (P)ercentage  (K)arakters";
		cout << "  (T)erug naar hoofdmenu" << endl << endl;
		kar = invoer();
		switch (kar) {

		case 'v':
		case 'V':			 
			cout << endl << "Geef de grootte van uw verschuivingsstapgrootte. De ";
			cout << "huidige verschuivingsstapgrootte is " << v << endl;
			do {							
				v = getalinvoer();
				if (v < 1 || v > 500)
					cout << "U moet een getal tussen de 1 en de 500 invullen\n";
			} while (v < 1 || v > 500); //vraag getal opnieuw
			break;

		case 'p':
		case 'P':
			cout << endl << "Welk percentage cellen moet leven onder ";
			cout << "de optie random. Het huidige percentage is ";
			cout << gegrnd << "%" << endl;
			do {							
				gegrnd = getalinvoer();	
				if (gegrnd < 0 || gegrnd > 100)
					cout << "U moet een getal tussen de 0 en de 100 invullen" << endl;
			} while (gegrnd < 0 || gegrnd > 100);
			break;

		case 'k':
		case 'K':			 
			cout << endl << "Welk karakter wilt u voor levende cellen?" << endl;
			karlevend = invoer();
			cout << endl << "Welk karakter wilt u voor dode cellen?" << endl;			
			kardood = invoer();
			break;

		case 't':
		case 'T':			 
			exit = true;
			break;
		} //switch
	} //while
}//parameters

void leven::eengeneratie () { //doe een generatie
	int leventeller;
	int i,j;
	levend = 0;
	for ( j=1;j<MAX-1;j++) {		
		for (i=1;i<MAX-1;i++) { //telt levende buurcellen		
				leventeller = wereld[j-1][i] + wereld[j+1][i] + wereld[j][i-1] +
								wereld[j][i+1] + wereld[j-1][i-1] + wereld[j-1][i+1] 
								+ wereld[j+1][i-1] + wereld[j+1][i+1];
				
				if (leventeller == 3){
					hulpwereld[j][i] = 1;// Overlevend
				} else if (leventeller == 2 && wereld[j][i]) {
				   hulpwereld[j][i] = 1;
				} else {
				 hulpwereld[j][i] = 0; //dood
				}
		} //for
	} //for
	for (j=1;j<MAX-1;j++) {		
		for (i=1;i<MAX-1;i++) {	
			wereld[j][i] = hulpwereld[j][i]; //kopieer de oude wereld in de nieuwe
			levend += wereld[j][i]; //telt levende cellen
		}
	}
	percentage = levend/10000; //bereken percentage levende cellen
	generatie++; //generatie verder
}//eengeneratie


void leven::gaan () {
	int i;
	for (i=1;i<=1000;i++) { //doet 1000 generaties
		eengeneratie();
		tekenlife();
		cout << endl << endl << endl;
	} //for
} //gaan


void leven::glidergun() { //maak een glidergun
	schoon(); //maak het scherm schoon 
	x=1; //positioneer de vieuw linksboven
	y=1;
	//coordinaten glidergun
	wereld[6][2] = true;
	wereld[6][3] = true;
	wereld[7][2] = true;
	wereld[7][3] = true;
	wereld[6][12] = true;
	wereld[7][12] = true;
	wereld[8][12] = true;
	wereld[5][13] = true;
	wereld[4][14] = true;
	wereld[4][15] = true;
	wereld[9][13] = true;
	wereld[10][14] = true;
	wereld[10][15] = true;
	wereld[7][16] = true;
	wereld[7][18] = true;
	wereld[7][19] = true;
	wereld[6][18] = true;
	wereld[8][18] = true;
	wereld[5][17] = true;
	wereld[9][17] = true;
	wereld[4][22] = true;
	wereld[5][22] = true;
	wereld[6][22] = true;
	wereld[4][23] = true;
	wereld[5][23] = true;
	wereld[6][23] = true;
	wereld[3][24] = true;
	wereld[7][24] = true;
	wereld[3][26] = true;
	wereld[2][26] = true;
	wereld[7][26] = true;
	wereld[8][26] = true;
	wereld[4][36] = true;
	wereld[5][36] = true;
	wereld[4][37] = true;
	wereld[5][37] = true;
	
	tekenlife();
} //glidergun


void leven::verschuif() { //verschuif de vieuw
	bool exit = false;
	bool error = false;
	char kar;
	while (exit == false) {
			error = false; //vieuw binnen de randen van de wereld
			cout << "\n(B)oven  (O)nder  (R)echts  (L)inks  (T)erug naar hoofdmenu\n\n";
		kar = invoer ();
		switch (kar) {
		case 'r':
		case 'R':
			if (x+v>=1000) {
				error = true;
			} else {
				x += v;
			}
			break;
		case 'l':
		case 'L':
			if (x-v<=1) {
				error = true;
			} else {
				x -= v;
			}
			break;
		case 'b':
		case 'B':
			if (y-v<=1) {
				error = true;
			} else {
				y -= v;
			}
			break;
		case 'o':
		case 'O':
			if (y+v>=1000) {
				error = true;
			} else {
				y += v;
			}  
			break; 
		case 't':
		case 'T':
			exit = true;
			break; 
	} //switch
		if (error) { //als de vieuw buiten de wereld zou komen
			cout << endl << "Je verschuift jezelf over de rand van de wereld. Verklein je ";
			cout << "stapgrote of ga een andere kant op." << endl << endl;
		} else {
			tekenlife();
		} //if
	} //while
} //verschuif 


void leven::tekenlife () {	//teken de wereld
	int i,j;
		cout << "Life program"<< endl << endl;
		for (j=y;j<HVIEW + y ;j++) {		
			for (i=x;i<BVIEW + x ;i++) {
				if (wereld[j][i])
					cout << karlevend; //print levende cellen
				else
					cout << kardood; //print dode cellen
			} //for
			cout << endl;
		} //for
		// print lijn met informatie
		cout << "Generatie: " << generatie << "    Percentage: ";
		cout << percentage << '%' << "    Levende cellen: " << levend;
		cout << "    X-coordinaat: " << x << "    Y-coordinaat: ";
		cout << y << endl;
} //tekenlife

void leven::schoon() {
	int i,j;
	levend = 0;
	generatie = 0;
	percentage = 0;
	for (j=0;j<MAX;j++)		
		for (i=0;i<MAX;i++)
			wereld[j][i] = false; //maak alle cellen dood
} //schoon

void leven::random() { //vul de vieuw met random aantal levende cellen
	int i,j;
	for (j=y;j<HVIEW + y ;j++)	
		for (i=x;i<BVIEW + x ;i++)
			if (randomgetal() % 100 + 1 <= gegrnd) { //kijk of cel leeft of niet
				wereld [j][i] = true;
				levend++; //tel levende cellen
			} else {
				wereld [j][i] = false;
			}
	percentage = levend/10000; //bereken percentage levende cellen
} //random
				 
void leven::statistiek() { //doet 1000 generaties en slaat gegevens op file
	ofstream uitvoer("statiestiek.txt",ios::out);
	int i;
	for (i=1;i<=1000;i++) {
		eengeneratie();
		tekenlife();
		//print in de file generatienummer en aantal levende cellen
		cout << endl << endl << endl;
		uitvoer << generatie << " " << levend << endl;
	} //for
	uitvoer.close(); //sluit uitvoerfile
}

int main () {
	cout << endl << endl << "Welkom! Dit programma stelt u in staat life te spelen.";
	cout << "\n\nHOOFDMENU" << endl << "Om het hoofdmenu te gebruiken ";
	cout << "kies een van de letters tussen haakjes om";
	cout << " die optie van het menu te kiezen.\nAlleen het eerste karakter ";
	cout << "wordt ingelezen." << endl << endl;
	cout << endl << endl << "Druk op ENTER om verder te gaan.";
	cin.get();//zorgt ervoor dat het programma pas verder gaat als je op enter drukt.

	char kar;
	bool exit = false;
	leven cel; //creer cel van klasse leven
	cel.schoon();
	while (exit == false) {
		cel.tekenlife();
		//hoofdmenu
		cout << endl << "(S)toppen  s(C)hoon  (V)erschuif  (P)arameters  (R)andom";
		cout << "  (G)lidergun  (E)en  g(A)an  s(T)atiestiek" << endl << endl;
		kar = invoer();
		switch (kar) {
			case 'c':
			case 'C':
            cel.schoon();			 
				break;

			case 'r':
			case 'R':	
				cel.schoon();	 
				cel.random();
				break;

			case 'e':
			case 'E':			 
				cel.eengeneratie();
				break;
	
			case 's':
			case 'S':			 
				cout << endl << "Het programma wordt nu afgesloten." << endl << endl;
				exit = true;
				break;

			case 'p':
			case 'P':
			   cel.parameters();
			   break;
			
			case 'v':
			case 'V':
            cel.verschuif();	 
				break;

			case 'g':
			case 'G':			 
				cel.glidergun();
				break;

			case 'a':
			case 'A':
				cel.gaan();
				break;
				
			case 't':
			case 'T':			 
				cel.statistiek();
				break;
			} //switch hoofdmenu
	} //while
} //main


