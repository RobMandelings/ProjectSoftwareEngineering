# Project Software Engineering: Metro Antwerpen
Simulatie van het metrosysteem in Antwerpen.

# Uitleg:
Hieronder vindt u het Class Diagram van het project in .svg formaat. Het bevat alle classes met hun member variabelen.
Daaronder vindt u de TODO/OUTDATED sectie van het project, waarbij OUTDATED wilt zeggen dat het over oudere delen van het project gaat.

## Class Diagram (zonder methods) NEW:
[![Screenshot-from-2020-04-23-16-41-27.png](https://svgshare.com/i/KPX.svg)](https://svgshare.com/i/KPX.svg)

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

### 3.2 Automatische simulatie (DONE)
* Doel: automatische simulatie - gegeven tijd
* Preconditie: Schema metronet
* Succesvol einde: simulatie eindigt.
* Stappen:
    1. WHILE huidige tijd < eind tijd

        1.1 FOR elke tram in het metronet

            1.1.1 voer use case 3.1 uit op de tram

Voor invoerformaat zie Appendix A opgave.

## EXTRA - na evaluatie 1: (DONE)
* Documentation (DONE)
* Good variable names (DONE)
* (Optional) more input/output tests (DONE)
* Contracten (DONE)

## REQUIREMENTS/ENSURES: (DONE)
* MetroNet.cpp:
    * constructor:
        * REQUIREMENT: name can't be empty string
    * getName():
        * ENSURE: return can't be empty string
    * getTram(int line):
        * REQUIREMENT: line >= 0
    * getStation(const char* name):
        * REQUIREMENT: name can't be empty
    * addTram(Tram* tram):
        * REQUIREMENT: tram is not NULL
    * addStation(Station* station):
        * REQUIREMENT: station is not NULL
    * addLine(Line* line):
        * REQUIREMENT: line is not NULL
    * getLine(int line)
        * REQUIREMENT: line >= 0
        
* Station.cpp:
    * getName():
        * ENSURE: return can't be empty string
    * setName(const string& name):
        * REQUIREMENT: name can't be empty string
    * getLine(int line):
        * REQUIREMENT: line >= 0
    * addLine(Line* line):
        * REQUIREMENT: line is not NULL

* Line.cpp:
    * Line(int line, LineNode* firstNode):
        * REQUIREMENT: line >= 0
        * REQUIREMENT: firstNode is not NULL
    * getFirstNode():
        * ENSURE: return is not NULL
    * setLine(int line):
        * REQUIREMENT: line >= 0
    * insertNode(LineNode* lineNode):
        * REQUIREMENT: lineNode is not NULL
        * ENSURE: m_firstNode can't be NULL
    * disableNodeForStation(Station* station):
        * REQUIREMENT: station is not NULL
        * ENSURE: lineNode.m_underConstruction = true
    * getNodeForStation(Station* station):
        * REQUIREMENT: station is not NULL
        * ENSURE: return lineNode is not NULL

* LineNode.cpp
    * LineNode(int lineIndex, Station* station):
        * REQUIREMENT: lineIndex >= 0
        * REQUIREMENT: station is not NULL
        * ENSURE: properly initialized
    * LineNode(int lineIndex, Station* station, LineNode* previousNode, LineNode* nextNode):
        * REQUIREMENT: lineIndex >= 0
        * REQUIREMENT: station is not NULL
        * REQUIREMENT: previousNode is not NULL
        * REQUIREMENT: nextNode is not NULL
        * ENSURE: properly initialized
    * getStation():
        * ENSURE: return is not NULL
    * setPreviousNode(LineNode* PreviousNode):
        * REQUIREMENT: PreviousNode is not NULL
    * setNextNode(LineNode* NextNode):
        * REQUIREMENT: NextNode is not NULL
        
* Tram.cpp:
    * Tram(int line, int speed, int amountOfSeats, LineNode* beginNode):
        * REQUIREMENT: line >= 0
        * REQUIREMENT: speed >= 0
        * REQUIREMENT: amountOfSeats >= 0
        * REQUIREMENT: beginNode is not NULL
        * ENSURE: properly initialised
    * getBeginNode():
        * ENSURE: return is not NULL
    * getCurrentNode():
        * ENSURE: return is not NULL
    * getTramLine():
        * ENSURE: return >= 0
    * getSpeed():
        * ENSURE: return >= 0
    * getAmountOfSeats():
        * ENSURE: return >= 0
    * setTramLine(int tramLine):
        * REQUIREMENT: tramLine >= 0
    * setSpeed(int speed):
        * REQUIREMENT: speed >= 0
    * setAmountOfSeats(int amountOfSeats):
        * REQUIREMENT: amountOfSeats >= 0
    * updateLocation(): 
        * ENSURE: m_currentNode is not NULL
        
## TODO - 7/04 (DONE):
* Verder werken nieuwe functionaliteit
* Nieuwe functionaliteit (types) testen
* (Eventueel) lengte normale tram aanpassen
* Class Diagram aanpassen

## TODO BEFORE 30/04 (DONE):
* Grafische impressie op basis van summary
* Tests/Doc
* Class Diagram afmaken
        

## Class Diagram (zonder methods) OUTDATED:

[![Screenshot-from-2020-03-06-18-27-11.png](https://i.postimg.cc/QMt04rH3/Screenshot-from-2020-03-06-18-27-11.png)](https://postimg.cc/68krqgrj)