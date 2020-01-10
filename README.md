# Linfo  
Pieni järjestelmäinfo skripti Linuxille, joka on kirjoitettu C++:lla.  
Sinun täytyy muokata config.h tiedostoa ennen, kuin rakennat linfon.  

config.h tiedostossa sinun täytyy lisätä nämä seuraavat tiedot  
 - OS_NAME -> Jakelun nimi (esim. "Debian GNU/Linux")  
 - OS_RMODEL -> Jakelumuoto (esim. "fixed" tai "rolling")  
 - SHOW_PKGS on valinnainen siksi, koska se vaatii pkgutils ohjelman (Jos haluat lisätä tämän niin arvoksi pitää tulla "k")  

Kun olet konfiguroinut config.h tiedoston, niin sitten sinun pitää rakentaa ja asentaa linfo.  
 - Rakenna 'make'  
 - Asenna 'make install'  

Tehnyt: Patrik Nyström (Alpakka31)