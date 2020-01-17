##Recipe Manager

#### Dies ist ein Rezeptmanager entwickelt in der Programmiersprache C. 

##### Auslesen von Rezepten
Der Rezeptmanager bezieht seine Daten aus einem über die Kommandozeile übergebenen Pfad.
Die Struktur der Datei ist fest vorgeschrieben und kann bei Abweichungen zu undefiniertem Verhalten führen.
Der Aufbau der Datei gliedert sich wie folgt:
``<Name des Rezepts>;<AnzahlZutat1>|<Einheit1>|<Name1>#<Anweisungen>`` 
Die Werte für ``Anzahl`` und ``Einheit`` sind optional und werden bei "leeren" Eingaben zu einem Whitespace konvertiert.

##### Hinzufügen von Rezepten
Rezepte können über das Kommando ``a`` im Programm angelegt werden. Dabei werden  folgende Schritte durchgeführt:
* Eingabe des Rezeptnamens
* Eingabe der Anzahl an Zutaten
* Eingabe des Namens, der Anzahl und der Einheit der Zutaten
* Eingabe der Zubereitungsanweisung

Nach der erfolgreichen Eingabe werden die Rezepte in der Textdatei abgelegt.

##### Bearbeiten von Rezepten
Rezepte können über das Kommando ``e`` bearbeitet werden. Nach der Eingabe des Indexes wird überprüft
ein Rezept mit diesem Index vorhande ist. Trifft dies zu, wird die Eingabe eines Rezepts und dessen Zutaten durchgeführt 
(siehe Punk ``Hinzufügen von Rezepten`). Nach der erfolgreichen Eingabe der Daten wird das Rezept mit dem
übergebenen Index mit dem neuen Rezept ersetzt.

##### Beenden des Programms
Wird die Bearbeitung der Rezepte nicht mehr gewünscht, wird die Option angeboten das Programm mit dem Kommando
``q`` zu Beenden. Die Option wird nicht nur im "Hauptmenü" angeboten, sondern auch in den Zwischenschritten im Programm.