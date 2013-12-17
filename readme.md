
> "THE BEER-WARE LICENSE" (Revision 42): 
> SW1B2-8> wrote this file. As long as you retain this notice you
> can do whatever you want with this stuff. If we meet some day, and you think
> this stuff is worth it, you can buy me a beer in return - Jonathan Hastrup


Robotten som selv finder vej
====================
Tema: Optimering af st�vsugerrobotten
Projektperiode: 8/10-13 til 18/12-13

Projektgruppe: B2-8
Deltagere: 
  * Bjarke Jepsen
  * Casper M�ller Bartholom�ussen
  * Frederik H�jholt
  * Jonathan Hastrup
  * Martin Viktor
  * Nichlas Lindorf Pedersen
  * Rasmus Lind Vildner Pedersen

Vejledere:
  * Rikke Hagensby Jensen
  * Bente N�rgaard

  
Hvad g�r programmet?
====================
Programmet er i stand til at simulere en traditionel robotst�vsuger, 
og illustrere hvordan den finder vej og orienterer sig i et ukendt milj�.
Det ukendte milj� beskrives/illustreres via en pnm-fil, som ved hj�lp 
af farver kan definere v�gge og eventuelle forhindringer.
Ud over et givent rums st�rrelse, ved den simulerede robotst�vsuger 
intet om det milj� den bev�ger sig ud i, og kortl�gger dens egen 
version af rummet. Programmets robotst�vsuger er i simulationen 
lige n�jagtig 1 pixel stor, og kan kun bev�ge sig �n pixel ad gangen i 
retningerne nord, syd, �st eller vest.


Programmet tager alts� et kort over et rum som input, 
men hvad resulterer dette s� i?
S� snart programmet er f�rdig med at simulere robotst�vsugerens 
rejse igennem det givne rum, vil programmet smide en ny fil ud, 
kaldet map.pnm, ved siden af dens executeable. Map.pnm indeholder
den simulerede robotst�vsugers rute rundt i rummet - ved hj�lp af
nye farver beskrives robottens bev�gelse.
  * R�d fave - robotten har k�rt igennem den givne pixel �n gang
    med dens f�rste bustrofedonbev�gelse
  * Hvert farveskift symboliserer en ny bustrofedonbev�gelse
  * De gr�nne linjer viser hvorfra en bustrofedonbev�gelse er 
    endt, og p�begyndt sin A*-algoritme, hvorfra den g�r sig 
    klar til den n�ste bustrofedonbev�gelse

En n�rmere og mere uddybende beskrivelse af programmet 
kan findes i den tilh�rende rapport.


Compile og k�r
====================
Hurtig gennemgang
--------------------
For at compile og k�re programmet:
  1. Naviger i minGW/terminalen til mappen som indeholder "makefile"
  2. I konsolvinduet tastes "make sim"
  3. Tast "sim kort-navn.pnm"
        Eksempel: "sim maps/60-40.pnm"

For at fjerne de genererede bin�re filer:
  1. "make clean"
  
Lang gennemgang
--------------------
Compilering:
Siden programmet best�r af flere header- og c-filer kr�ver det �n compilering 
for hvert s�t. Ved siden af de mange kilde-filer ligger ogs� en fil kaldet 
"makefile" som automatiserer hele compile-processen! N�r kommandoen "make" bliver 
indtastet vil compileren med det samme finde den p�g�ldende "makefile"-fil, 
hvorefter den vil udf�re de mange instrukser den indeholder.

K�rsel af program:
Efter en fuldf�rt compilering skulle "makefile" gerne have genereret 
4 objekt-filer og 1 executeable. N�r programmet sparkes i gang, kr�ver den
en pnm-fil som et af dens parametre for at kunne starte - den p�kr�vede 
fil er et billede som ved hj�lp af hvid og sort beskriver et rum samt dets
v�gge og eventuelle forhindringer. 

Hvis du ikke f�ler dig i det kreative hj�rne, eller bare ikke gider tegne 
et kort, ligger der i mappen "maps" en r�kke klargjorte eksempel-kort, 
som kan importeres i stedet.

> BEM�RK:
> Hvis du tegner rummet via grafik-programmet GIMP, skal du f�rst �bne den
> den genererede pnm-fil i en tekst-editor og slette den 2. linje af filen
> f�r programmet vil godtage filen.
> Alts�, hvis linje 2 i filen indeholder
>   "# CREATOR: GIMP PNM Filter Version x.x"
> skal denne linje slettes.

> BEM�RK:
> Hvis du tegner rummet via grafik-programmet GIMP, skal du eksportere
> billedet som "ASCII"


Kompatibilitet
====================
Programmet er testet p�, kan k�re og kan 
compileres p� f�lgende platforme:
  * Windows under minGW
  * OS X
  * Linux (ubuntu)

 