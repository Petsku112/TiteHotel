/*

Hotelli varaus ohjelma.

T�m� ohjelma on kurssin harjoitusty� ja se on tehty osoittamaan C++ ohjelmoinnin perusteiden osaamiseni.
Ohjelma t�ytt�� korkeimman arvosanan vaatimat ominaisuudet.

Ohjelma arpoo alussa parillisen m��r�n hotellihuoneita v�lilt� 40-300, joista puolet (alkupuoli) on yhden hengen ja puolet (loppupuoli) on kahden hengen huoneita,
Ohjelma kysyy k�ytt�j�lt� halutaanko luoda varaus, vaiko tarkastella sellaista.
Jos k�ytt�j� valitsee varauksen luomisen, h�nelle ilmoitetaan vapaat huoneet, sek� mitk� niist� ovat yhden- ja mitk� kahden hengen huoneita, sek� yhden y�n hinnan kussakin huoneessa.
T�m�n j�lkeen k�ytt�j� voi valita yhden- tai kahden hengen huoneen.
Ohjelma kysyy haluaako k�ytt�j� itse p��tt�� huoneen, ohjelma voi my�s arpoa huoneen satunnaisesti.
T�m�n j�lkeen ohjelma kysyy montako y�t� halutaan varata (Maksimiksi p��tetty 11 y�t�).
Seuraavaksi k�ytt�j�� pyydet��n sy�tt�m��n varaajan nimi.
T�m�n j�lkeen varaajalle n�ytet��n varauksen tiedot ja annetaan mahdollisuus perua varaus, tai siirty� maksamaan.
T�ss� kohtaa kone arpoo 0%, 10% tai 20% alennuksen varaukseen, jos alennus on 0% k�ytt�j�lle n�ytet��n varausnumero ja muut varauksen tiedot.
Jos taas alennus on 10% tai 20%, k�ytt�j�� onnitellaan ja saatu alennus ilmoitetaan. T�m�n j�lkeen k�ytt�j�� pyydet��n siirtym��n maksamaan sy�tt�m�ll� 1.
Kun k�ytt�j� sy�tt�� numeron 1, h�nt� kiitet��n varauksesta ja n�ytet��n varausnumero, sek� varauksen tiedot.
T�ss� kohtaa k�ytt�j� voi palata alkuun(1) tai sulkea ohjelman(2)
Jos k�ytt�j� palaa alkuun h�n voi alkaa luomaan uutta varausta (varauksia voi luoda niin kauan kuin huoneita riitt��), kun kaikki huoneet on varattu, ohjelma ilmoittaa hotellin olevan t�ynn�.
tai h�n voi siirty� tarkastelemaan, jo tehtyj� varauksia.
Varauksia voidaan hakea varausnumeron tai varaajan nimen perusteella.
Varausnumerolla n�ytet��n numeroa vastaava varaus ja nimell� listataan kaikki, henkil�n tekem�t varaukset.

Ohjelma tarkistaa aina, ett� k�ytt�j�n sy�t� on kelpuutettava arvo ja pit�� huolen siit�, ett� samaa huonetta ei voi varata useaan kertaan, ja ett� varausnumero on aina eri.




Kurssi: C++ ohjelmoinnin perusteet
Tekij�: Petteri Laukkanen

*/




//Tuodaan ohjelman tarvitsemat kirjastot
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

//M��ritet��n k�ytt��n std nimiavaruus
using namespace std;


//P��ohjelman alku
int main() {



	//Asettaa ohjelman kieleksi suomen, mahdollistaen ��kk�sien tulostuksen
	setlocale(LC_ALL, "finnish");



	int noppa(int, int);                                 //Aliohjelma, joka palauttaa satunnaisen luvun (int, int)=(minimiarvo, maksimiarvo)

	int huoneidenmaara = noppa(4, 4);                      //Arvotaan huoneiden m��r� v�lilt� 40-300.
	int yhdenhengenhuoneet = huoneidenmaara / 2;              //Hotellissa olevien yhden hengen huoneiden m��r�.
	int kahdenhengenhuoneet = huoneidenmaara / 2;             //Hotellissa olevien kahden hengen huoneiden m��r�.
		kahdenhengenhuoneet++;
	int yhdenhengenhuoneettod = yhdenhengenhuoneet;     //Vapaana olevien yhden hengen huoneiden m��r�.
	int kahdenhengenhuoneettod = kahdenhengenhuoneet;   //Vapaana olevien kahde nhengen huoneiden m��r�.
		kahdenhengenhuoneettod--;
	//Muuttujat, joihin tallennetaan v�liaikaisesti k�ynniss�olevan varauksen tiedot.
	//N�in ne on helppo ylikirjoittaa jos k�ytt�j� p��tt�� keskeytt�� varauksen
	int varausnmr = 1;                                  //Varausnumero
	int valikko;                                        //Valikko (1: valikon ensimm�inen vaihtoehto, 2:toinen vaihtoehto, jne.
	int aika;                                           //�iden m��r�
	int hinta;                                          //Hinta (Aluksi huoneen koon ja �iden m��r�n perusteella, mutta kun varaus on lukittu hinnasta poistetaan arvottu alennus)
	int alennus;                                        //Alennus (0:ei alennusta, 1:10% alennus, 2: 20% alennus)
	int huone;                                          //Valittu huone
	int tila;                                           //Huoneen koko (1:yhden hengen huone, 2:kahden hengen huone)
	string nimi;                                        //Varaajan nimi

	bool huoneet[300];                                  /*boolean taulukko, johon merkataan huoneen varauksen tila true / false arvona.
														Esim: huoneet[1]=true << huone 1 on varattu
														huoneet[2]=false << huone 2 on vapaa*/

	bool varausnumerot[99999];                          //Sama kuin bool huoneet, mutta varausnumeroille.
	bool loydetty = false;										//Boolean joka on true jos etsityll� varausnumerolla l�ytyi varaus



	//struct, joka toimii varauspohjana sis�lt�en muuttujat jotka jokainen varaus tarvitsee
	struct varaukset {
		string vnimi;       //Varaajan nimi
		int vhuone;         //Varattu huone
		int vnumero;        //Varausnumero
		int vtila;          //Huoneenkoko
		int vaika;          //�iden m��r�
		int vhinta;         //varauksen lopullinen hinta
	};

	varaukset varaaja[300]; //M��ritell��n taulukko varaaja, jossa on 300 varaukset tyyppist� muuttujaa
	//t�nne voidaan tallentaa "varaukset" structissa esitellyt muuttujat vnimi, vhuone, jne. kullekkin eri varaukselle




	//Varausten tarkasteluun k�ytetyt muuttujat
	string etsittavavaraaja;    //K�ytt�j�n ilmoittama nimi, jonka varauksia halutaan etsi�
	int etsittavanumero;        //K�ytt�j�n ilmoittama varausnumero, jonka perusteella varausta halutaan etsi�


	int varaajat = 0;           //Pit�� kirjaa siit� montako varausta on tehty

	int hintalaskuri(int, int); //Funktio, joka laskee huoneen koon ja �iden perusteella varauksen hinnan
	void viivat();              /*Funktio, jota kutsumalla voidaan tulostaa viivoja, ns. lataus animaationa
	(k�ytet��n lukemisen selvent�miseksi ja annetaan aikaa lukea n�yt�n tekstej� ilman, ett� ohjelma n�ytt�� pys�htyneen.*/
	void cls();                 /*Funktio, joka tulostaa rivej� siten, ett� aiemmat tekstit siirtyv�t n�yt�n ulkopuolelle ja kursori siirtyy vasempaan yl�nurkkaan
	K�ytet��n auttamaan valikon luettavuutta*/


	Sleep(200);                 //Odoitus komento

	//Tulostetaan hotellin nimi ASCII art tyylill�
	cout << R"(  _______ _____ _______ ______   _    _  ____ _______ ______ _       _____ 
 |__   __|_   _|__   __|  ____| | |  | |/ __ \__   __|  ____| |     / ____|
    | |    | |    | |  | |__    | |__| | |  | | | |  | |__  | |    | (___  
    | |    | |    | |  |  __|   |  __  | |  | | | |  |  __| | |     \___ \ 
    | |   _| |_   | |  | |____  | |  | | |__| | | |  | |____| |____ ____) |
    |_|  |_____|  |_|  |______| |_|  |_|\____/  |_|  |______|______|_____/ 
							 Petteri Laukkanen 
                                        )";

	Sleep(10);

	cout << "\n TITE hotellit. Mahdollistamassa Terveen, Iloisen, sek� T�yden El�m�n.\n\n\n\n"; //Hotellin slogan
	Sleep(100);

	viivat(); //aikaisemmin m��ritetty "lataus animaatio", jotta k�ytt�j� ehtii lukea nimen ja sloganin

	Sleep(1000);
Alku:  //M��ritet��n piste "Alku" johon voidaan palata kun varaus on valmis tai k�ytt�j� keskeytt�� varauksen

	int huoneitatod = yhdenhengenhuoneettod + kahdenhengenhuoneettod;   //M��ritet��n varaamattomien huoneiden kokonaism��r� laskemalla yhteen vapaiden yhden ja kahden hengen huoneiden m��r�t.
	//Alempana kuin muut m��ritelm�t, jotta huoneidenm��r� p�ivittyy aina kun palataan alkuun

	cls();  //K�ytet��n aikaisemmin m��ritetty� cls funktiota konsolin "siistimiseen"

	//Tulostetaan ASCII art tyylill� tervetulo toivotus
	cout << R"(  
 _    _                   _   _   _   _             _   _   _           _   _   _   _   _ 
| |  | |                 (_) (_) (_) (_)           (_) (_) (_)         (_) (_) (_) (_) | |
| |__| |  _   _  __   __   __ _    __ _     _ __     __ _   _  __   __   __ _    __ _  | |
|  __  | | | | | \ \ / /  / _` |  / _` |   | '_ \   / _` | | | \ \ / /  / _` |  / _` | | |
| |  | | | |_| |  \ V /  | (_| | | (_| |   | |_) | | (_| | | |  \ V /  | (_| | | (_| | |_|
|_|  |_|  \__, |   \_/    \__,_|  \__,_|   | .__/   \__,_| |_|   \_/    \__,_|  \__,_| (_)
           __/ |                           | |                                            
          |___/                            |_|                                            )";


	//Ilmoitetaan p��valikossa tehtyj�n varauksien m��r�
	cout << "Varauksia: " << varaajat;

	//Kysyt��n k�ytt�j�lt� mit� he haluavat tehd�
	cout << "\n\nHaluaisitteko varata huoneen, vai tarkastella jo tehty� varausta?\n";
	cout << "Uusi varaus: 1  Tarkastele varausta: 2     Jos haluatte poistua, sy�tt�k��: 3\n>>";
	cin >> valikko;

	//Luodaan tai tarkastellaan varauksia k�ytt�j�n sy�tteen mukaan
	switch (valikko) {

	//Varauksenluominen
	case 1:
	Huoneenkoko:
		cls();

		//Jos uuden varauksen numero on suurempi kuin huoneidenm��r�, ilmoitetaan hotellin olevan t�ynn�
		if (varaajat == huoneidenmaara) {
			cout << "Hotellimme on valitettavasti t�ynn�. Voitte kuitenkin viel� tarkastella varauksia";
			Sleep(3000);
			goto Alku;
		}

		//Varaus valikko, joka ilmoittaa k�ytt�j�lle mit� huoneita on vapaana.
		cout << "\nT�ll�hetkell� vapaana on yhteens�: " << huoneitatod << " huonetta.\n";
		if (yhdenhengenhuoneettod > 0 && kahdenhengenhuoneettod < 1) {
			cout << "Kaikki Kahden hengen huoneemme ovat valitettavasti t�ynn�, voitte kuitenkin viel� varata Yhden hengen huoneita.\n";
			cout << "Yhden hengen huoneita on vapaana " << yhdenhengenhuoneettod;
			cout << "\nHinta 100 euroa/y�";
			cout << "\nHaluaisitteko varata kahden hengen huoneen?";
			cout << "\nKyll� 1		En 2 (Palaa alkuun)\n>>";
		}

		else if (yhdenhengenhuoneettod < 1 && kahdenhengenhuoneettod > 0) {
			cout << "Kaikki Yhden hengen huoneemme ovat valitettavasti t�ynn�, voitte kuitenkin viel� varata kahden hengen huoneita.\n";
			cout << "Kahden hengen huoneita on vapaana " << kahdenhengenhuoneettod;
			cout << "\nHinta 150 euroa/y�";
			cout << "\nHaluaisitteko varata yhden hengenhuoneen?";
			cout << "\nKyll� 1		En 2 (Palaa alkuun)";
		}

		else if (kahdenhengenhuoneettod > 0 && yhdenhengenhuoneettod > 0) {
			cout << "Yhden hengen huoneita on " << yhdenhengenhuoneettod << "	(100e/y�\nkahden hengen huoneita on " << kahdenhengenhuoneettod << "	(150e/y�);";
			cout << "\n\nHaluaisitteko varata yhden hengen huoneen: 1 Vaiko kahden hengen huoneen: 2	Poistu: 3\n>>";
		}
	
		cin >> valikko;

		if (yhdenhengenhuoneettod < 1 && valikko==2 || kahdenhengenhuoneettod < 1 && valikko==2) {
			goto Alku;
		}

		switch (valikko) {
		//Yhden hengen huoneen valitseminen
		case 1:
		Arpa1:

			//Kysyt��n k�ytt�j�lt� arvotaanko huoneen numero vai haluavatko he p��tt�� itse
			tila = 1;
			cls();
			cout << "\n\nMik�li haluatte valita huoneenne itse, sy�tt�k��: 1\nVoimme my�s valita huoneen sattumanvaraisesti puolestanne sy�tt�m�ll�: 2	Poistu: 3\n>>";
			cin >> valikko;
			switch (valikko) {

			//Vaihtoehto 1: kerrotaan k�ytt�j�lle huoneet joista voi valita ja tallennetaan sy�te
			case 1:
				cls();
				cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMink� huoneen haluaisitte?\n>>";
				cin >> huone;
				while (huone<1 || huone>yhdenhengenhuoneet) {
					cout << "\n\nSy�tt�m�nne huone ei vastannu yht�k��n vapaista yhden hengen huoneistamme.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMink� huoneen haluaisitte?\n>>";
					cin >> huone;
				}

				//Jos k�ytt�j� sy�tt�� jo varatun huoneen pyydet��n heit� sy�tt�m��n toinen huone
				while (huoneet[huone] == true) {
					cout << "\n\nSy�tt�m�nne huone on valitettavasti jo varattu.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMink� huoneen haluaisitte?\n>>";
					cin >> huone;
				}

				break;

			//Vaihtoehto 2: arvotaan k�ytt�j�lle huone ja varmistetaan ettei sit� ole viel� varattu
			case 2:
				cls();
				huone = noppa(1, yhdenhengenhuoneet);
				while (huoneet[huone] == true) {
					huone = noppa(1, yhdenhengenhuoneet);
				}
				cout << "Huoneenne numero on: " << huone;
				break;

			//Vaihtoehto 3: palataan alkuvalikkoon
			case 3:
				cls();
				cout << "Palataan alkuun.";
				Sleep(2000);
				goto Alku;
				break;

			//Mik�li k�ytt�j�n sy�t� ei ole 1 tai 2 palataan kohtaan "Huoneenkoko"
			default:
				cls();
				cout << "Sy�tt�m�nne luku ei ollut 1 tai 2;";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				goto Huoneenkoko;
				
			}
			break;
			
		//Kahden hengen huoneen valitseminen
		case 2:
		Arpa2:
			tila = 2;
			cls();

			//Kysyt��n k�ytt�j�lt� arvotaanko huoneen numero vai haluavatko he p��tt�� itse
			cout << "\n\nMik�li haluatte valita huoneenne itse, sy�tt�k��: 1\nVoimme my�s valita huoneen sattumanvaraisesti puolestanne sy�tt�m�ll�: 2	Poistu: 3\n>>";
			cin >> valikko;
			switch (valikko) {

			//Vaihtoehto 1: kerrotaan k�ytt�j�lle huoneet joista voi valita ja tallennetaan sy�te
			case 1:
				cls();
				cout << "\n\nVapaat kahden hengen huoneemme ovat numeroilla: " << kahdenhengenhuoneet << " - " << huoneidenmaara << "\nMink� huoneen haluaisitte ? \n >> ";
				cin >> huone;
				while (huone<kahdenhengenhuoneet || huone>huoneidenmaara) {
					cout << "\n\nSy�tt�m�nne huone ei vastannu yht�k��n vapaista kahden hengen huoneistamme.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat kahden hengen huoneemme ovat numeroilla: " << kahdenhengenhuoneet+1 << " - " << huoneidenmaara << "\nMink� huoneen haluaisitte ? \n >> ";
					cin >> huone;
				}

				//Jos k�ytt�j� sy�tt�� jo varatun huoneen pyydet��n heit� sy�tt�m��n toinen huone
				while (huoneet[huone] == true) {
					cout << "\n\nSy�tt�m�nne huone on valitettavasti jo varattu.\n\n";
					cin.clear();
					cin.ignore(100, '\n');
					Sleep(2000);
					cout << "\n\nVapaat yhden hengen huoneemme ovat numeroilla: 1 - " << yhdenhengenhuoneet << "\nMink� huoneen haluaisitte?\n>>";
					cin >> huone;
				}
				break;

			//Vaihtoehto 2: arvotaan k�ytt�j�lle huone ja varmistetaan ettei sit� ole viel� varattu
			case 2:
				cls();
				huone = noppa(kahdenhengenhuoneet, huoneidenmaara);
				while (huoneet[huone] == true) {
					huone = noppa(kahdenhengenhuoneet, huoneidenmaara);
				}
				cout << "Huoneenne numero on: " << huone;
				break;
			//Vaihtoehto 3: Palataan alkuvalikkoon
			case 3:
				cls();
				cout << "Palataan alkuun.";
				Sleep(2000);
				goto Alku;
				break;

			default:
				cls();
				cout << "Sy�tt�m�nne luku ei ollut 1 tai 2;";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				goto Arpa2;
			}
			break;
		case 3:
			cls();
			cout << "Palataan alkuun.";
			Sleep(2000);
			goto Alku;
			break;
		default:
			cls();
			cout << "\nSy�tt�m�nne arvo ei ollut: 1 tai 2\n\n";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			goto Arpa1;
		}
		break;


	//Varauksen tarkastelu
	case 2:
		Tarkastelu:
		cls();
		cout << "Varauksen tarkastelu";
		cout << "\nVoitte hakea varauksia varausnumeron 1 tai varaajan 2 perusteella.\n>>";
		cin >> valikko;
		
		switch (valikko) {
		//Haku varausnumerolla
		case 1:

			cls();
			cout << "Sy�tt�k�� varausnumero\n>> ";
			cin >> etsittavanumero;

			while (cin.fail()) {
				cout << "Sy�tt�m�nne arvo ei ollut numero!";
				cin.clear();
				cin.ignore(100, '\n');
				Sleep(2000);
				cls();
				cout << "Sy�tt�k�� varausnumero\n>> ";
				cin >> etsittavanumero;
			}

			cls();
			for (int etsintalaskuri = 0; etsintalaskuri <= 300; etsintalaskuri++) {
				if (varaaja[etsintalaskuri].vnumero == etsittavanumero) {
					cout << "Varaukset numerolla " << etsittavanumero;
					cout << "\n\nVaraaja: " << varaaja[etsintalaskuri].vnimi;
					cout << "\nHuoneen numero: " << varaaja[etsintalaskuri].vhuone;
					cout << "\nHuoneen koko: " << varaaja[etsintalaskuri].vtila << " hengenhuone";
					cout << "\n�iden m��r�: " << varaaja[etsintalaskuri].vtila << " y�t�";
					cout << "\nHinta: " << varaaja[etsintalaskuri].vhinta << " euroa";
					cout << "\n\n";
					viivat();
					loydetty = true;
					
				}
			}
			
			break;
		//Haku varaajan nimell�
		case 2:
			cls();
			cout << "Sy�tt�k�� varaajan nimi\n>> ";
			cin.clear();
			cin.ignore(100, '\n');
			getline(cin, etsittavavaraaja);
			cout << "Varaukset nimell� " << etsittavavaraaja;
			for (int etsintalaskuri = 0; etsintalaskuri <= 300; etsintalaskuri++) {
				if (varaaja[etsintalaskuri].vnimi == etsittavavaraaja) {
					cout << "\n\nVarausnumero: " << varaaja[etsintalaskuri].vnumero;
					cout << "\nHuoneen numero: " << varaaja[etsintalaskuri].vhuone;
					cout << "\nHuoneen koko: " << varaaja[etsintalaskuri].vtila << " hengenhuone";
					cout << "\n�iden m��r�: " << varaaja[etsintalaskuri].vtila << " y�t�";
					cout << "\nHinta: " << varaaja[etsintalaskuri].vhinta << " euroa";
					cout << "\n\n";
					viivat();
					loydetty = true;

				}
			}
			break;
		default:
			cls();
			cout << "\nSy�tt�m�nne arvo ei ollut: 1 tai 2\n\n";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			cls();
			goto Tarkastelu;

		}
		//Jos varauksia ei l�ydy tulostetaan sopiva teksti riippuen siit�, haettiinko varausta numerolla vai nimell�
		if (loydetty == false) {
			if (valikko == 1) {
				cout << "\nVarausnumerolla "<<etsittavanumero<<" ei valitettavasti l�ytynyt yht�k��n varausta.\n";
			}
			if (valikko == 2) {
				cout << "\nNimell� " << etsittavavaraaja << " ei valitettavasti l�ytynyt varauksia.";
			}
		}
		cout << "\nVoitte palata aloitukseen sy�tt�m�ll� 1\n>>";
		cin >> valikko;
		goto Alku;
		break;

	case 3:
		cls();
		cout << "Kiitoksia asionnistanne kanssamme. Toivotamme teille oikein mukavaa p�iv�njatkoa!\n";
		cout << "Varaus ohjelma sulkeutuu itsest��n 10 sekunnin kuluttua.";
		Sleep(10000);
		return 0;
		break;

	default:
		cls();
		cout << "\nSy�tt�m�nne arvo ei ollut: 1 tai 2\n\n";
		cin.clear();
		cin.ignore(100, '\n');
		Sleep(2000);
		goto Alku;
		break;
	}

	//Kysyt��n k�ytt�j�lt� �iden m��r� ja kerrotaan valitan huone tyypin hinta per y�
	cout << "\n\nKuinka monta y�t� haluaisitte y�py�? (Pisin aika 11 y�t�)\n";
	if (tila == 1) {
		cout << "100e/y�\n>>";
	}
	else if (tila == 2) {
		cout << "150e/y�\n>>";
	}
	cin >> aika;
	while (aika < 1 || aika > 11) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nSy�tt�m�nne �iden m��r� ei ollu v�lill� 1-11.";
		Sleep(2000);
		cls();
		cout << "\n\nKuinka monta y�t� haluaisitte y�py�? (Pisin aika 11 y�t�)\n>>";
		cin >> aika;
	}
	//L�hetet��n huoneen koko ja �iden m��r� funktiolle joka laskee hinnan
	hinta = hintalaskuri(aika, tila);
	cls();
	//Pyydet��n varaajan nimi
	cout << "\n\nSy�tt�k�� viel� varaajan nimi: ";
	cin.clear();
	cin.ignore(100, '\n');
	getline(cin, nimi);



	cls();
	//N�ytet��n varauksen tiedot ja kysyt��n haluaako k�ytt�j� siirty� maksamaan
	cout << "\nVarauksenne tiedot: \n";
	cout << "\nVaraaja: " << nimi;
	cout << "\nHuone:" << huone;
	if (tila == 1) {
		cout << "\nYhden hengen huone";
	}
	else if (tila == 2) {
		cout << "\nKahden hengen huone";
	}
	cout << "\n�iden m��r�: " << aika;
	cout << "\nHinta: " << hinta << " euroa";
	cout << "\n\n1: Maksa      2:Peruuta varaus\n\n";
	cout << "\n>>";
	cin >> valikko;

	switch (valikko) {

	case 1:
		//Arvotaan 0%, 10% tai 20% alennus hintaan ja tallennetaan tiedot varaaja taulukkoon
		alennus = noppa(1, 3);
		if (alennus == 2) {
			cls();
			cout << "Onneksi olkoon!!\n\nOlette saaneet 10% alennuksen varauksestanne!";
			hinta = hinta * 0.9;
			Sleep(2000);
		}
		else if (alennus == 3) {
			cls();
			cout << "Onneksi olkoon!!\n\nOlette saaneet 20% alennuksen varauksestanne!";
			hinta = hinta * 0.8;
			Sleep(2000);
		}
		varausnmr = noppa(10000, 99999);
		while (varausnumerot[varausnmr] == true) {
			varausnmr = noppa(10000, 99999);
		}
		varausnumerot[varausnmr] = true;
		varaaja[varaajat].vhinta = hinta;
		varaaja[varaajat].vaika = aika;
		varaaja[varaajat].vnimi = nimi;
		varaaja[varaajat].vhuone = huone;
		varaaja[varaajat].vnumero = varausnmr;
		varaaja[varaajat].vtila = tila;
		huoneet[varaaja[varaajat].vhuone] = true;
		if (tila == 1) {
			yhdenhengenhuoneettod--;
		}
		else if (tila == 2) {
			kahdenhengenhuoneettod--;
		}
	Tiedot:
		cls();

		//Kiitet��n varauksesta ja n�ytet��n viel� lopulliset tiedot
		cout << "Kiitoksia varauksestanne!\n\nVarausnumeronne on: ";
		cout << varausnmr;
		cout << "\n\n";
		cout << varaaja[varaajat].vnimi << "\n";
		cout << "Huone: " << varaaja[varaajat].vhuone;

		if (tila == 1) {
			cout << "\nYhden hengen huone";
		}
		else if (tila == 2) {
			cout << "\nKahden hengen huone";
		}
		cout << "\n�iden m��r�: " << aika;
		cout << "\nHinta: " << hinta << " euroa";
		varaajat++;


		cout << "\n\nVoitte palata alkuun sy�tt�m�ll� 1 tai poistua ohjelmasta sy�tt�m�ll� 2\n>>";
		cin >> valikko;
		while (cin.fail()) {
			cout << "Sy�tt�m�nne arvo ei ollut numero!";
			cin.clear();
			cin.ignore(100, '\n');
			Sleep(2000);
			cls();
			cout << "\n\nVoitte palata alkuun sy�tt�m�ll� 1 tai poistua ohjelmasta sy�tt�m�ll� 2\n>>";
			cin >> valikko;
		}
		switch (valikko) {
		case 1:
			cout << "Palataan alkuun.";
			Sleep(2000);
			goto Alku;
			break;
		case 2:
			cls();
			cout << "Kiitoksia asionnistanne kanssamme. Toivotamme teille oikein mukavaa p�iv�njatkoa!\n";
			cout << "Varaus ohjelma sulkeutuu itsest��n 10 sekunnin kuluttua.";
			Sleep(10000);
			return 0;
			break;
		default:
			cout << "Sy�tt�m�nne arvo ei ollu 1 tai 2";
			goto Tiedot;
			break;
		}
	case 2:
		cls();
		cout << "Palataan alkuun.";
		Sleep(2000);
		goto Alku;
		break;

	default:
		cout << "Sy�tt�m�nne arvo ei ollu 1 tai 2";
		goto Tiedot;
		break;
	}



}

//Funktio, joka laskee varauksen hinnan (ennen alennusta) �iden m��r�n ja huoneen koon perusteeella
int hintalaskuri(int aika, int tila) {
	if (tila == 1) {
		return aika * 100;
	}
	else if (tila == 2) {
		return aika * 150;
	}
}

//Funktio, joka kutsuttaessa tulostaa viivoja ns. lataus animaationa
void viivat() {
	string valiviivat = "------------------------------------------------------------------------------------------";
	for (int j = 0; j < valiviivat.size(); j++)
	{

		for (int i = 0; i <= 10000000; i++);
		cout << valiviivat[j];

	}
}

//Funktio, joka kutsuttaessa siirt�� konsolin n�kym�� alasp�in siten, ett� se n�ytt�� tyhj�lt�
void cls() {
	cout << "\x1B[2J\x1B[H";
}

//Funktio, joka arpoo luvun annetun minimi ja maximi arvon v�list�
int noppa(int min, int max) {
	srand(time(0));
	return (rand() % ((max - min) + 1)) + min;
}