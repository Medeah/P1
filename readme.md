
> "THE BEER-WARE LICENSE" (Revision 42): 
> SW1B2-8> wrote this file. As long as you retain this notice you
> can do whatever you want with this stuff. If we meet some day, and you think
> this stuff is worth it, you can buy me a beer in return - Jonathan Hastrup


Robotten som selv finder vej
====================
Tema: Optimering af støvsugerrobotten
Projektperiode: 8/10-13 til 18/12-13

Projektgruppe: B2-8
Deltagere: 
  * Bjarke Jepsen
  * Casper Møller Bartholomæussen
  * Frederik Højholt
  * Jonathan Hastrup
  * Martin Viktor
  * Nichlas Lindorf Pedersen
  * Rasmus Lind Vildner Pedersen

Vejledere:
  * Rikke Hagensby Jensen
  * Bente Nørgaard

  
Hvad gør programmet?
====================
Programmet er i stand til at simulere en traditionel robotstøvsuger, 
og illustrere hvordan den finder vej og orienterer sig i et ukendt miljø.
Det ukendte miljø beskrives/illustreres via en pnm-fil, som ved hjælp 
af farver kan definere vægge og eventuelle forhindringer.
Ud over et givent rums størrelse, ved den simulerede robotstøvsuger 
intet om det miljø den bevæger sig ud i, og kortlægger dens egen 
version af rummet. Programmets robotstøvsuger er i simulationen 
lige nøjagtig 1 pixel stor, og kan kun bevæge sig én pixel ad gangen i 
retningerne nord, syd, øst eller vest.


Programmet tager altså et kort over et rum som input, 
men hvad resulterer dette så i?
Så snart programmet er færdig med at simulere robotstøvsugerens 
rejse igennem det givne rum, vil programmet smide en ny fil ud, 
kaldet map.pnm, ved siden af dens executeable. Map.pnm indeholder
den simulerede robotstøvsugers rute rundt i rummet - ved hjælp af
nye farver beskrives robottens bevægelse.
  * Rød fave - robotten har kørt igennem den givne pixel én gang
    med dens første bustrofedonbevægelse
  * Hvert farveskift symboliserer en ny bustrofedonbevægelse
  * De grønne linjer viser hvorfra en bustrofedonbevægelse er 
    endt, og påbegyndt sin A*-algoritme, hvorfra den gør sig 
    klar til den næste bustrofedonbevægelse

En nærmere og mere uddybende beskrivelse af programmet 
kan findes i den tilhørende rapport.


Compile og kør
====================
Hurtig gennemgang
--------------------
For at compile og køre programmet:
  1. Naviger i minGW/terminalen til mappen som indeholder "makefile"
  2. I konsolvinduet tastes "make sim"
  3. Tast "sim kort-navn.pnm"
        Eksempel: "sim maps/60-40.pnm"

For at fjerne de genererede binære filer:
  1. "make clean"
  
Lang gennemgang
--------------------
Compilering:
Siden programmet består af flere header- og c-filer kræver det én compilering 
for hvert sæt. Ved siden af de mange kilde-filer ligger også en fil kaldet 
"makefile" som automatiserer hele compile-processen! Når kommandoen "make" bliver 
indtastet vil compileren med det samme finde den pågældende "makefile"-fil, 
hvorefter den vil udføre de mange instrukser den indeholder.

Kørsel af program:
Efter en fuldført compilering skulle "makefile" gerne have genereret 
4 objekt-filer og 1 executeable. Når programmet sparkes i gang, kræver den
en pnm-fil som et af dens parametre for at kunne starte - den påkrævede 
fil er et billede som ved hjælp af hvid og sort beskriver et rum samt dets
vægge og eventuelle forhindringer. 

Hvis du ikke føler dig i det kreative hjørne, eller bare ikke gider tegne 
et kort, ligger der i mappen "maps" en række klargjorte eksempel-kort, 
som kan importeres i stedet.

> BEMÆRK:
> Hvis du tegner rummet via grafik-programmet GIMP, skal du først åbne den
> den genererede pnm-fil i en tekst-editor og slette den 2. linje af filen
> før programmet vil godtage filen.
> Altså, hvis linje 2 i filen indeholder
>   "# CREATOR: GIMP PNM Filter Version x.x"
> skal denne linje slettes.

> BEMÆRK:
> Hvis du tegner rummet via grafik-programmet GIMP, skal du eksportere
> billedet som "ASCII"


Kompatibilitet
====================
Programmet er testet på, kan køre og kan 
compileres på følgende platforme:
  * Windows under minGW
  * OS X
  * Linux (ubuntu)

 