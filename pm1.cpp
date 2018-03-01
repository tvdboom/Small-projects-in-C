// Programmeer methode Jop Maarse en Marco Trueba van den Boom. Gebruikte
// compiler: Bloodshed Dev-C++ 4.9.9.2
// Laat de gebruiker zijn/haar geboorte datum invullen. Vervolgens moet de
// gebruiker de dag van de week invullen waarop hij/zij geboren is. Daarna
// krijgt de gebruiker twee rekenvragen die goed moeten worden beantwoord.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void vernvdg(int & tllr, int & nmr) {
	int c = tllr, d = nmr, rest;
	while ( d != 0 ) {
    	rest = c % d; c = d; d = rest;
	}
	if ( c > 1 ) {
		tllr = tllr / c;
		nmr = nmr / c;
	}
} // void

int main() {
	cout << endl << endl << "Welkom! U wordt eerst gevraagd om uw geboortedatum";
	cout << " in te vullen. Daarna moet u de dag van de week waarop u geboren";
	cout << " bent invullen. Als u dit goed doet dan komen er twee rekenvragen.";
	cout << " Als u deze goed beantwoord heeft u de oefening succesvol";
	cout << " volbracht."<< endl << endl << "Dit programma is gemaakt door";
	cout << " Jop Maarse (student nummer 1219448) en Marco Trueba van den Boom";
	cout << " (student nummer 1246984) aan de universiteit Leiden in opdracht" ;
	cout << " van Dhr. Koster voor het vak Programmeermethode. Inleverdatum";
	cout << " 21-09-2012." << endl << endl << "Druk op ENTER om verder te gaan.";
	cout << endl << endl;

	cin.get();//zorgt ervoor dat het programma pas verder gaat als je op enter drukt.
	srand( time(NULL) );//seed voor pseudorandom number generator, die gebruikt de
	// funtie time uit <ctime> om op elk moment een ander willekeurig getal te geven. 
	int jaar, jaarnu, maand, maandnu, dag, dagnu, jaaroud, maandoud, dagoud;
	int mnd[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// maand is nu een array, met het aantal dagen dat elke maand heeft.
	int rand1[2] = {(rand() % 19) + 1, (rand() % 19) + 1}; // genereer random 
	// getal tussen de 1 en de 19. We hebben aangenomen dat wat in de opdracht
	// stond met grenzen inbegrepen was.
	int rand2[2] = {(rand() % 19) + 1, (rand() % 19) + 1};
	int cdagen = 0;
	int noemer, teller;
	int T_1, T_2;
	int i; // gebruiken we in de for loops
	double decimaal, dec;
	char cweek[7] = {'D','m','D','w','d','v','z'};
	char check;
	string antwrd, aansprk, aansprkH, vervgh, vervgw;
	
    
	time_t now;//vraag de tijd en datum op.
	struct tm *local;//splits de tijd en datum in jaar/maand/week/uur enz.
	now = time(0);
	local = localtime(&now);
	jaarnu = local->tm_year + 1900;//tm_year is het aantal jaren na 1900, voor de
	// berekening die later wordt uitegvoerd, moet er hier 1900 bij worden opgeteld.
	maandnu = local->tm_mon + 1;
	dagnu = local->tm_mday;
		
	// jaar invoer
	cout << "Voer je geboortejaar in: ";
	cin >> jaar;
	jaaroud = jaarnu - jaar - 1;

	// jaarcheck
	if (jaaroud < 9) {
		cout << "Sorry, je bent te jong om dit programma te gebruiken." << endl;
		return 1; //  sluit het programma
	} else if (jaaroud > 100) {
		cout << "Sorry, u bent te oud om dit programma te gebruiken." << endl;
		return 1;
	}
	

	// maand invoer
	do {
		cout << "Voer je geboortemaand in: ";
		cin >> maand;
		if (maand <= 0 || maand > 12) { // controleer of maand tussen 1 en 12 zit  
			cout << "Je hebt een verkeerde waarde voor de maand ingevoerd. Probeer";
        	cout << " het opnieuw!" << endl;
        }
	} while (maand <= 0 || maand > 12);
	// als maand niet tussen 1 en 12 zit vraag hij het opnieuw
	maandoud = maandnu - maand - 1;
	if (maandnu > maand)
	// als deze maand groter is dan de vorige dan is de gebruiker 1 jaar ouder
	    jaaroud ++;
	else
		maandoud += 12;  

	// maandcheck
	if (jaaroud == 9 && maand > maandnu) {
		cout << "Sorry, je bent te jong om dit programma te gebruiken." << endl;
		return 1;
	} else if (jaaroud >= 100 && maand < maandnu) {
		cout << "Sorry, u bent te oud om dit programma te gebruiken." << endl;
		return 1; 
	}    
      

	// dag invoer
	if (jaar % 4 == 0)
		mnd[1] += 1;     
	do {
		cout << "Voer je geboortedag in: ";
		cin >> dag;
		if (dag <= 0 || dag > mnd[maand-1]) { // controleer of de dag mogelijk is
			cout << "Je hebt een verkeerde waarde voor de dag ingevoerd.";
        	cout << " Probeer het opnieuw!" << endl;
        } 
    } while (dag <= 0 ||dag > mnd[maand-1]);
	// als de dag niet mogelijk is dan vraag hij het opnieuw


	if ((jaarnu % 4 == 0 && jaarnu % 100 != 0) || jaarnu % 400 == 0)
	//controle op schrikkeljaar
		mnd[1] = 29;    
	else
		mnd[1] = 28; // hij kon ook nog 29 zijn van de dagcheck 	
	dagoud = dagnu - dag;
	if (dagnu >= dag)
		maandoud ++;
	// als deze dag groter is dan de vorige dan is de gebruiker 1 maand ouder
	else
		dagoud = mnd[maandnu] + dagoud;
	if (maandoud >= 12) {
		jaaroud ++;
		maandoud -= 12;                 
	}

	// dagcheck
	if (jaaroud == 9 && maand >= maandnu && dag > dagnu) {
		cout << "Sorry, je bent te jong om dit programma te gebruiken." << endl;
		return 1;
	} else if (jaaroud >= 100 && maand >= maandnu && dag <= dagnu) {
		cout << "Sorry, u bent te oud om dit programma te gebruiken." << endl;
		return 1; 
	} 



    
	if (jaaroud < 18) {
		aansprkH = "Je";
		aansprk = "je";
		vervgh = " hebt ";
		vervgw = "Wil ";
	} else {
		aansprk = "u";
		aansprkH = "U";
		vervgh = " heeft ";
		vervgw = "Wilt ";
	}		

	// dag van de week check
	cout << endl << aansprkH << " bent " << jaaroud << " jaar en " << maandoud;
	cout << " maand(en) oud. Dat is in totaal " << 12 * jaaroud + maandoud;
	cout << " maanden." << endl << endl << "Op welke dag van de week was ";
	cout << dag << "/" << maand << "/" << jaar << "?" << endl;
	cout << "(Vul in: Z, m, D, w, d, v, z)" << endl << endl << "Antwoord: ";
	cin >> check;    // Informatie over zijn leeftijd geven en vragen om de dag
	// van de week waarin de gebruiker geboren is	


	if ((jaar % 4 == 0 && jaar % 100 != 0) || jaar % 400 == 0)
	// controle op schrikkeljaar voor de dagen van de maand
		cmaand[1] = 29;    
	for(i = 0; i < maand -1; i++) // door alle maanden gaan om de dagen op te tellen
		cdagen = cdagen + cmaand[i];
	cdagen = cdagen + dag;
	for (i = 0; i < jaar; i++)	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) 
	// weer schrikkeljaarcontrole deze keer voor de dagen van het jaar
			cdagen = cdagen + 366;
		else
			cdagen = cdagen + 365;
		}
	cdagen = cdagen - 2;
	cdagen = cdagen % 7; // kan de da van de week voor elke datum berekenen,
	// ook voor het jaar 0 en ver in de toekomst.
	if (cweek[cdagen] != check)
		return 1;

	// eerste vraag
	cout << endl << "Dat klopt! Nu beginnen we echt." << endl << endl;
	cout << "De volgende vraag gaat over rekenen." << endl;
	cout << "Kies uit antwoord A, B, C of D" << endl << endl;
	if (jaaroud >= 30) { // als de gebruiker ouder dan 30 is dan komt er een andere vraag
		cout << "Vermenigvuldig de grootste gemene deler van 64 en 88 net zo vaak";
        cout << " totdat u op 1626 uitkomt." << endl << endl << "A: U heeft de";
	    cout << " grootste gemene deler van 64 en 88, 204 maal vermenigvuldigd." << endl;
     	cout << "B: 64 en 88 hebben geen gemene deler." << endl << "C: Door de";
      	cout << " grootste gemene deler van 64 en 88 te vermenigvuldigen met een";
       	cout << " geheel getal zal u nooit op 1626 uitkomen." << endl << "D: 1626 is";
       	cout << "deelbaar door 64, maar niet door 88.";
    } else {
		cout << "Reken uit: 5 * 9 - 9 * 4 + 9" << endl << endl << "A: 16" << endl;
    	cout << "B: 17" << endl << "C: 18" << endl << "D: 19";
     	cout << endl << endl << "Antwoord:  ";
    }	
  	cin >> antwrd;
	if (antwrd != "C" && antwrd != "c")
		return 1;


	// breukvraag
	cout << endl << aansprkH << vervgh << "goed geantwoord!" << endl << endl;
	cout << "Tel deze breuken bij elkaar op. Geef het antwoord weer als een";
	cout << " vereenvoudigde breuk in de vorm a/b." << endl << endl;       
	vernvdg(rand1[0], rand1[1]);
	vernvdg(rand2[0], rand2[1]);
	cout << rand1[0] << "/" << rand1[1] << " + " << rand2[0] << "/" << rand2[1];
	cout << endl << endl; // laat de random breuken zien
	cout << "Voer de teller in: ";
	cin >> teller;
	cout << "Voer de noemer in: ";
	cin >> noemer;
	cout << endl << "Geef nu het antwoord als decimaal getal";
	cout << " (je mag er maximaal 0.1 vanaf zitten): ";
	cin >> decimaal;
	T_1 = (rand1[0] * rand2[1] + rand2[0] * rand1[1]);
	// bereken de noemer van het antwoord	
	T_2 = (rand2[1] * rand1[1]); // bereken de teller van het antwoord
	vernvdg(T_1, T_2); // vereenvoudig het antwoord
	dec = (double) T_1 / T_2; // bereken het decimaal antwoord
	if (teller != T_1 || noemer != T_2 || (decimaal - dec) > 0.1 || (dec - decimaal) > 0.1) {
	// check of het antwoord goed is met een marge van 0.1
		cout << endl << endl << "Sorry, " << aansprk << vervgh;
    	cout << "verkeert geantwoord." << endl << endl;
	} else { 
		cout << endl << endl << aansprkH << vervgh << "goed geantwoord!" << endl;
    	cout << endl << "Deze oefening is nu voorbij. Gefiliciteerd met deze";
      	cout << " enorme overwinning!";
       	cout << endl << endl;
    }   	
    cout << "Druk op ENTER om af te sluiten." << endl;
    cin.ignore(); 
	// is in windows nodig, omdat de console daar anders meteen word afgesloten
	cin.get();
	
	return 0;
}
