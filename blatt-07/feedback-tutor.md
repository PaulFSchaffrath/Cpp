Hallo Paul,

hier kommt die Korrektur des aktuellen Übungsblattes. Falls Du irgendwelche
Fragen zu einem Übungsblatt hast, kannst Du mir gerne eine Mail schreiben:
<brosi@cs.uni-freiburg.de>.


# Übungsblatt 7

Gesamtpunktzahl: 19 / 20


## Generelles

Hm, ich kann deinen Code bei mir problemlos mit -O3 kompilieren. Hast du `make
clean` ausgeführt, bevor du neu kompiliert hast?

Ich hab bzgl. deiner Fehlermeldung etwas recherchiert - das scheint ein
Apple-Problem zu sein, und man scheint diese Warnung getrost ignorieren zu
können :)

## Aufgabe 1 (15/15)

Das sieht gut aus!

## Aufgabe 2 (4/5)

Auch hier läuft alles so, wie es soll, allerdings hat dein Code ein
Speicherleck: du gibst den Speicher, den du in Zeile 21 allozierst, nicht
wieder frei. Das kannst du direkt ind er Schleife machen, die Strings werden in
deine Strings ja reinkopiert (-1).
