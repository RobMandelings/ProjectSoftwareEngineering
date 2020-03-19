# Project Software Engineering: Metro Antwerpen
Simulatie van het metrosysteem in Antwerpen.

# TODOs:
## 1. Invoer (DONE)
### 1.1 Wegen en voertuigen inlezen:
* Doel: Schema inlezen - Stations, trams & verbindingen.
* Preconditie: XML-bestand inlezen.
* Succesvol einde: Spoorschema vormen met stations & info.
* Stappen:
    1. Open invoerbestand
    2. WHILE Bestand niet ingelezen
        
        2.1. Herken het soort element (STATION, TRAM)
        
        2.2. Lees verdere informatie voor het element
        
        2.3. IF Verifieer geldige informatie
        
            2.3.1. THEN Voeg element toe aan de simulatie
        
            2.3.1. ELSE Foutboodschap + positioneer op volgende element in het bestand
    3. Verifieer consistentie van de metronet
    4. Sluit invoerbestand
* Uitzonderingen:
Onherkenbaar element, ongeldige info, inconsistent metronet
* Voorbeeld zie voorbeeld.xml

## 2. Uitvoer (DONE)
### 2.1 Simpele uitvoer:
* Doel: Uitvoer info
* Preconditie: schema metronet nodig
* Succesvol einde: ASCII output bestand - info metronet
* Stappen:
    1. Open uitvoerbestand
    2. WHILE Nog banen beschikbaar

        2.1. Schrijf baan-gegevens uit
    3. WHILE Nog voertuigen beschikbaar

        3.1. Schrijf voertuig-gegevens uit
    4. Sluit uitvoerbestand

* Uitzonderingen: geen
* Voorbeeld output:
    ```
    Station A
    <- Station C
    -> Station B
    Spoor 12
    Station B
    <- Station A
    -> Station C
    Spoor 12
    Station C
    <- Station B
    -> Station A
    Spoor 12

    Tram 12 in Station A, 32 zitplaatsen
    ```
    Voorbeeld bij voorbeeld.xml.

## 3 Simulatie (DONE)
### 3.1 Rijden van trams
* Doel: Simuleren van rijdende tram
* Preconditie: grondplan
* Succesvol einde: nieuwe locatie tram - output
* Stappen:
    1. Voer verplaatsing uit
    2. Overzicht
* Uitzonderingen: geen
* Voorbeeld:
    ```
    Tram 12 reed van station A naar station B.
    ```
    Voorbeeld bij voorbeeld.xml.

### 3.2 Automatische simulatie
* Doel: automatische simulatie - gegeven tijd
* Preconditie: Schema metronet
* Succesvol einde: simulatie eindigt.
* Stappen:
    1. WHILE huidige tijd < eind tijd

        1.1 FOR elke tram in het metronet

            1.1.1 voer use case 3.1 uit op de tram

Voor invoerformaat zie Appendix A opgave.

## EXTRA:
* Documentation
* Good variable names
* (Optional) more output tests
* Contracten & input/output tests

## Class Diagram (zonder methods):

[![Screenshot-from-2020-03-06-18-27-11.png](https://i.postimg.cc/QMt04rH3/Screenshot-from-2020-03-06-18-27-11.png)](https://postimg.cc/68krqgrj)
