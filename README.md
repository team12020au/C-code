# C-code

For at producere Mosquitto MQTT programmer i C og med et udviklingsprogram som fx. Eclipse skal der hentes og bygges et Mosquitto bibliotek <br>

Biblioteket hentes ned lokalt i en mappe vha: <br>
**git clone https://github.com/eclipse/mosquitto**

For at få biblioteket til at virke på CentOS skal der hentes et stykke software der hedder **openssl-devel** <br>
**$ yum install openssl-devel**

Herefter kan biblioteket bygges vha make, så det passer til den maskine programmet skal afvikles på. <br>
Mens man opholder sig i mappen med det nye clonede bibliotek bygges koden med flg. kommando: <br>
**make all WITH_CJSON=no WITH_DOCS=no**

Der er en masse filer i denne mappe der er hentet ned. 
Biblioteket vi er specielt interesseret i ligger i /lib og hedder libmosquitto.so.1
Der oprettes et symbolsk link inde i mappen hvor libmosquitto.so ligger. 
Filen hedder libmosquitto.so.1 men kan kun opfattes i Eclipes, hvis der bliver oprettet et symbolsk link, så kommer filen til at fremstå som libmosquitto.so 
Herefter melder Eclipse ikke fejl på bibliotekets syntax
Opret det symbolske link vha: <br>
**$ ln -s libmosquitto.so.1 libmosquitto.so**

![image](https://user-images.githubusercontent.com/84921655/120499053-08943580-c3c0-11eb-92e4-477f0fc34506.png)
