# C-code

## C projekter der inkluderer Mosquitto MQTT med fx Eclipse som udviklingsmiljø
For at producere Mosquitto MQTT programmer i C og med et udviklingsprogram som fx. Eclipse skal der hentes og bygges et Mosquitto bibliotek <br>

Biblioteket hentes ned lokalt i en mappe vha: <br>
**git clone https://github.com/eclipse/mosquitto**

For at få biblioteket til at virke på CentOS skal der hentes et stykke software der hedder **openssl-devel** <br>
**$ yum install openssl-devel**

Herefter kan biblioteket bygges vha make, så det passer til den maskine programmet skal afvikles på. <br>
Mens man opholder sig i mappen med det nye clonede bibliotek bygges koden med flg. kommando: <br>
**make all WITH_CJSON=no WITH_DOCS=no**

Der er en masse filer i denne mappe der er hentet ned.  <br>
Biblioteket vi er specielt interesseret i ligger i /lib og hedder libmosquitto.so.1 <br>
Der oprettes et symbolsk link inde i mappen hvor libmosquitto.so ligger.  <br>
Filen hedder libmosquitto.so.1 men kan kun opfattes i Eclipes, hvis der bliver oprettet et symbolsk link,  <br>
så kommer filen til at fremstå som libmosquitto.so  <br>
Herefter melder Eclipse ikke fejl på bibliotekets syntax <br>
Opret det symbolske link vha: <br>
**$ ln -s libmosquitto.so.1 libmosquitto.so** <br>


Det nyoprettede bibliotek linkes inde i Eclipse til projektet. <br>
Projectproperties /  C/C++ build / setting/ GCC C linker / libraries. <br>
Indtast "mosquitto" i Libraries og stien hvor libmosquitto.so filen befinder sig i.  <br>
Filen befinder sig i den clodnede mappe fra github under **mosquitto/lib**  <br>

## Mosquitto på Beaglebone eller Pocket Beagle<br>
For at udvikle Mosquitto MQTT programmer der kan compileres / afvikles på Beaglebone skal der ligeledes installeres nogle biblioteker<br>
Log ind på din Beaglebone<br>
I kommandolinjen udfør flg kommandoer:<br>

**$ sudo apt-get update**<br>
**$ sudo apt-get install mosquitto**<br>
**$ sudo apt-get install mosquitto-dev**<br>
**$ sudo apt-get install libmosquitto-dev**<br>

Dernæst skal mosquitto.h kopieres over på Beaglebone fra det tidligere clonede mosquitto bibliotek fra github<br>
Mosquitto.h skal includeres i toppen af et C-projekt<br>
H-filen findes i mappen:<br>
**mosquitto/include**<br>

Læg evt Mosquitto.h i din home mappe på din CentOS, åben et konsolvindue i homemappen og kopier Mosquitto.h på Pocketbeagle vha Secure Copy <br>
**$ scp mosquitto.h debian@beaglebone:/home/debian** <br>
Med denne kommando bliver Mosquitto kopieret fra din home mappe i CentOS over på home mappen på BeagleBone<br>

Der skal selvfølgelig også ligge en C-fil på BeagleBone, denne kan evt også kopieres fra CentOS vha Secure Copy<br>

Der kan nu compileres Mosquitto C-projekter på Beaglebone vha kommandoen: <br>
**$ gcc <filnavn på -c fil> -o <Navn på program> -lmosquitto**<br>

Derefter bliver programmet bygget og er klar til afvikling på BeagleBone<br>

