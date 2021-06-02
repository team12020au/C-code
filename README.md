# C-code

For at få Mosquitto MQTT til at virke med C-kode og fx et udviklingsprogram som fx. Eclipse skal der hentes og bygges et Mosquitto bibliotek <br>

Biblioteket hentes ned lokalt i en mappe vha: <br>
**git clone https://github.com/eclipse/mosquitto**

For at få biblioteket til at virke på CentOS skal der hentes et stykke software der hedder **openssl-devel** <br>
**$ yum install openssl-devel**

Herefter kan biblioteket bygges vha make, så det passer til den maskine programmet skal afvikles på. <br>
Mens man opholder sig i mappen med det nye clonede bibliotek bygges koden med flg. kommando: <br>
**make all WITH_CJSON=no WITH_DOCS=no**
