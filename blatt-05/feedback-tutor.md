Hallo Paul,

hier kommt die Korrektur des aktuellen Übungsblattes. Falls Du irgendwelche
Fragen zu einem Übungsblatt hast, kannst Du mir gerne eine Mail schreiben:
<brosi@cs.uni-freiburg.de>.


# Übungsblatt 5

Gesamtpunktzahl: 12 / 20


## Generelles

Bitte achte doch darauf, keine kompilierten Dateien ins SVN zu committen ;)

## Aufgabe 1 (12/20)

Hier benutzt du leider immer noch globale Variablen, diese hätten jetzt
Membervariablen der Klassen sein sollen (-2). Deine initGame(), setup() und
cleanup()-Methoden hätten die Konstruktoren und Destruktoren der GameOfLife und
TerminalManager-Klassen sein sollen (-2). Sonst passt das und das Spiel
funktioniert auch gut :) Leider fehlen die Tests komplett bzw. testen noch den
Stand von Blatt 04 (-4).
