// Programmeer methode Robbie Brooijmans en Marco Trueba van den Boom. Gebruikte
// compiler: Bloodshed Dev-C++ 4.9.9.2
// Codeert en decodeert bestanden

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void keerom (int getal, double & groot2,ofstream & output) { //draai getal om
	while (getal > 0) {
		output << getal % 10;
		groot2++;
		getal /= 10;
	} //while
} //keerom

void coderen (string input, string output) {
	int totregels = 0,i = 0; //teller van de hoeveelheid regels en karakters
	double groot1 = 1, groot2 = 0; //grote van de invoer- en uitvoerbestand
	double comp; //compressierate
	char prekar, kar; //de karakters die je leest
	ifstream invoer (input.c_str(), ios::in);
	ofstream uitvoer (output.c_str(), ios::out);
	kar = invoer.get ();
	
	while (!invoer.eof ()) {
		if (prekar != kar || kar == '\n'){ //als karakter enter of niet vorige dan...
			if (kar == '\n')
				totregels++;
			if (i > 1)
				keerom (i,groot2,uitvoer);
			if ((kar >= '0' && kar <= '9') || kar == '\\') {
				//als karakter een cijfer of een backslash dan...
				uitvoer.put ('\\');
				groot2++; // grootte uitvoerfile +1
			}	//if		
			uitvoer.put (kar);
			groot2++;			
			i = 0;
		} //if
		i++;
		prekar = kar;
		kar = invoer.get ();
		groot1++; //grootte invoerfile +1;
	} //while

	invoer.close (); //sluit de invoerfile
	uitvoer.close (); //sluit de uitvoerfile
	comp = (groot2 / groot1) * 100; //compressierate berekenen	
	comp= (int) comp + 0,5; //compressierate afronden
	cout << endl << endl;	
	cout << "Totaal aantal regels van het gecodeerde bestand: " << totregels;
	cout << endl << "De behaalde compressierate is: " << comp << "%." << endl;
}

void decoderen (string input, string output) {
	int kar1, prekar1 = 0, prekar2, prekar3; 
	//om de kars te onthouden bij omzetting naar getallen
	int i = 0; //teller om het aantal nullen te onthouden	
	char kar, prekar, preprekar, prepreprekar; //de karakters die je leest
	//kar = de huidige karakter, prekar de vorige etc.
	ifstream invoer (input.c_str(), ios::in);
	ofstream uitvoer (output.c_str(), ios::out);
	kar = invoer.get ();
	
	while (! invoer.eof ()) { 
		if (((prekar >= '0') && (prekar <= '9')) && ((prepreprekar == '\\') ||
		 (((preprekar < '0') || (preprekar > '9')) && preprekar != '\\')))  {
		// als de vorige karakter een cijfer is en die daarvoor een cijfer en die
		// daarvoor dan een \, zodat dat cijfer een uitvoercijfer is en niet een 
		// telcijfer. Of als de karakter voor het vorige cijfer een letter is. 
			prekar1 = (prekar - '0') ;	
			// dat is om van de vorige karakter, wat een cijfer is, om te zetten in 
			// in een getal
			if(prekar1 == 0)
				i++;	// dit is om nullen te onthouden, die anders wegvallen
			while (((kar >= '0') && (kar <= '9')) && (! invoer.eof())) {
				if (kar == '0')	//idem
					i++;kar1 = (kar - '0') ;
				prekar1 = (prekar1 * 10) + kar1;
				kar = invoer.get (); //als het huidige karakter een cijfer is dan 
				//het samengevoegd worden met de vorige karakter.
			} //while
			prekar2 = prekar1 % 10; //om vorige karakter om te draaien
			prekar1 = prekar1/ 10;
			prekar3 = prekar2;
			while(prekar1 >= 1) {
				prekar2 = prekar1 % 10;
				prekar1 /= 10;		
				prekar3 = (prekar3 * 10) + prekar2;
			} //while
			while (i > 0) {
				prekar3 = prekar3*10;
				i--;//de nullen toevoegen
			} //while		
			while (prekar3 != 1) {
				uitvoer.put (preprekar);
				prekar3--;	//het vorige karakter uitschrijven							
			} //while
		} //if			
		if (((kar >= '0') || (kar <= '9')) && (prekar == '\\') && (preprekar != '\\'))
			uitvoer.put (kar); 
		if (((kar < '0') || (kar > '9')) && (kar != '\\'))
			uitvoer.put (kar);
		if (kar == '\\' && prekar == '\\' && preprekar == '\\')
			prekar = 0;
		prepreprekar = preprekar;
		preprekar = prekar;
		prekar = kar;
		kar = invoer.get ();
	} //while
	invoer.close (); 
	uitvoer.close ();
} //void


int main () {

	cout << endl << endl << "Welkom! Dit programma codeert en decodeert het door u ";
	cout << "gekozen bestand en toont naderhand de compressierate en het aantal ";
	cout << "regels van het gecodeerde bestand." << endl << endl << "Dit programma";
	cout << " is gemaakt door Robbie Brooijmans (studentnummer 1288288) en Marco";
	cout << " Trueba van den Boom (studentnummer 1246984) aan de universiteit Leiden";
	cout << " in opdracht van Dhr. Koster voor het vak Programmeermethode. Inleverdatum";
	cout << " 12-10-2012." << endl << endl << "Druk op ENTER om verder te gaan.";

	cin.get();//zorgt ervoor dat het programma pas verder gaat als je op enter drukt.

	char coddec; //kiezen voor coderen/decoderen
	bool geopend = false; //is het bestand geopend of niet
	string wat;
	//de namen van de input- en outputfiles
	string input, output;

	cout <<endl << endl << "Wilt u coderen of decoderen?" << endl << "Optie c";
	cout << " :Coderen." << endl << "Optie d: Decoderen" << endl << endl << "Optie: ";
	cin >> coddec;	
	while (coddec != 'c' && coddec !='C' && coddec != 'd' && coddec != 'D') {
	// check of de gebruiker c of d heeft getypt	
		cout << "U hebt een verkeerde waarde ingevoerd. Kies uit c of d!" << endl;
		cout << endl << "Optie: ";
		cin >> coddec;
	}
	if (coddec == 'c' || coddec == 'C')
		wat = "coderen";
	else 
		wat = "decoderen";

	//Invoer bestand
	cout << endl << endl << "Voer de directory en de bestandsnaam van de file ";
	cout << "die u wilt " << wat << "." << endl << "Bijv. C:/homefolder/filenaam.txt";
	cout << endl << "Als het bestand zich in dezelfde map als het programma ";
	cout << " bevindt hoeft u alleen de naam van het bestand in te voeren.";
	cout << endl << endl << "Invoerfile: ";
	while (!geopend) { // terwijl het bestand niet geopend is
		cin >> input;
		ifstream invoer (input.c_str(), ios::in);
		if (!invoer.is_open()) { // als het openen niet lukt
			cout << endl << "Het bestand kan niet worden geopend. Probeer het ";
			cout << "opnieuw en let op typfouten!" << endl << endl << "Invoerfile: ";
			cin.get ();
		}
		else
			geopend = true;
	}

	//Uitvoer bestand
	cout << endl << "Voer nu op dezelfde manier de naam in van het ";
	cout << "uitvoerbestand." << endl << endl << "Uitvoerfile: ";
	do {	
		cin >> output;
		if (output == input) { // invoer en uitvoer mogen niet hetzelfde bestand zijn
			cout << endl <<"U heeft dezelfde uitvoerfile als invoerfile gebruikt.";
			cout << " Dit is niet toegestaan! Wees eens origineler!" << endl;
			cout << endl << "Uitvoerfile: ";
		}
	} while (output == input);	
	
	//nu gaat het echte werk beginnen
	if (coddec == 'c' || coddec == 'C')
		coderen(input,output);
	else 
		decoderen(input, output);

	cout << endl <<  endl << "Druk op ENTER om af te sluiten." << endl;
	cin.ignore ();
	// is in windows nodig, omdat de console daar anders meteen word afgesloten
	cin.get ();
	
	return 0;
} //main
