Hotelli varaus järjestelmä
C++ ohjelmoinnin perusteet harjoitustyö
Petteri Laukkanen
13.12.2022
Hotelli varaus järjestelmä, on C++ kielellä kirjoitettu näyte, kurssin aiheista, sekä C++ kielen osaamisestani.
Kyseinen hotelli varausjärjestelmä sisältää kaikki ominaisuudet jotka vaaditaan korkeimpaan arvosanaan.

Toiminta:
Aluksi ohjelma arpoo parillisen hotelli huoneiden määrän väliltä (40-300), joista puolet (alkupuoli) määritetään yhden hengen ja puolet (loppupuoli) määritetään kahden hengen huoneiksi.
Ohjelma tulostaa hotellin nimen, sekä sloganin ja siirtyy tämän jälkeen pää valikkoon, josta voidaan aloittaa varaamaan huoneita(1), tarkastelemaan varauksia(2) tai sulkea ohjelma(3).
Jokaisessa vaiheessa käyttäjän syöte tarkistetaan, oli syöte sitten tekstiä tai numero, ohjelma pitää huolen siitä, että jos syöte ei ole halutulla numerovälillä tai oikean tyyppinen, käyttäjää pyydetään syöttämään arvo uudelleen.
1.
Varaaminen
Jos käyttäjä valitsee varaamisen, ohjelma kysyy halutaanko varata yhden vaiko kahden hengen huone.
Käyttäjä valitsee huoneen koon. Tämän jälkeen ohjelma kysyy halutaanko huone arpoa vai päättää itse. Jos käyttäjä tahtoo päättää huoneen numeron itse, ohjelma ilmoittaa montako kyseisen kokoista huonetta on vapaana ja millä numero välillä huoneet ovat sim. Huoneita yhteensä: 300  Kahden hengen huoneita on vapaana 150. Huoneet ovat välillä: 151-300.
Jos taas käyttäjä haluaa, että huone arvotaan ohjelma arpoo huoneen ja ilmoittaa tuloksen käyttäjälle.
Tämän jälkeen käyttäjältä kysytään Kuinka moneksi yöksi he haluavat huoneen varata, tähän on asetettu maksimi raja 11 yötä.
Tämän jälkeen käyttäjältä kysytään varaajan nimi.
Kun nimi on syötetty, ohjelma tulostaa varauksen tiedot (Nimi, Huone, Huoneen koko, öiden määrä ja hinta), perään ohjelma pyytää vielä varmistusta käyttäjältä.
Jos käyttäjä tahtoo peruuttaa tilauksen hänet palautetaan etusivulle, mikäli tiedot kuitenkin hyväksytään, ohjelma arpoo käyttäjälle 0%, 10% tai 20% alennuksen sattuman varaisesti.
(Arpominen tapahtuu vasta tässä kohtaa ja edellisessä vaiheessa tiedot hyväksyttäessä näkyy alentamaton hinta. Tällä estetään käyttäjää “huijaamasta” järjestelmää, perumalla varaus niin monta kertaa että saadaan paras alennus.)
Jos arpa onni suosii, onnitellaan käyttäjää alennuksen saamisesta, jos alennusta ei tule siirrytään suoraan tulostamaan varauksen kaikki tiedot. Ohjelma arpoo satunnaisesti varausnumeron väliltä 10000-99999. Tämän jälkeen käyttäjälle ilmoitetaan kaikki varauksen tiedot: Varausnumero, Varaaja, Huone, Huoneen koko, Öiden määrä, sekä hinta (mahdollisesti alennettu).
Kun käyttäjä on valmis, voidaan palata alku valikkoon syöttämällä 1.

Mikäli kaikki yhden tai kahden hengen huoneet varataan, tästä ilmoitetaan käyttäjälle ja tarjotaan vain vapaan huone tyypin varausta. Mikäli myös toinen huone tyyppi täyttyy, ilmoitetaan varaajalle hotellin olevan täynnä. (Varauksia voi kuitenkin silti tarkastella)

2.
Varauksien tarkastelu
Jos käyttäjä haluaa tarkastella varauksia, kysytään halutaanko varausta etsiä Varausnumeron(1) vaiko Varaajan (2) perusteella.
Jos käyttäjä valitsee varausnumerolla haun, pyydetään haluttu varaus numero, ja etsitään sille vastinetta, jos varausnumerolla ei löydy mitään ilmoitetaan ettei varauksia löytyny, muuten tulostetaan löytynyt varaus.
Jos käyttäjä valitsee nimellä hakemisen, pyydetään haluttu nimi ja etsitään kaikki varaukset kyseisellä nimellä. Mikäli varauksia on monta erotetaan ne viivalla.




