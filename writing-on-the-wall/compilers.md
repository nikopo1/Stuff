Compilers
=========

## Algoritmul de parsare folosit de Bison

parser stack - conține simbolurile găsit de parser, impreună cu valoarea semantică asociată
shifting - citirea unui token și inserarea lui pe stivă
reducing - aplicarea unei reguli

Regulile se aplică în momentul în care pe stivă există N simboluri care corespund unei anumite
reguli. Când se aplică o regulă, aceste simboluri sunt scoase de pe stivă, iar în locul lor se
inserează un nou simbol, care corespunde părții din stânga a unei reguli. Taken from [docs][1].


Exemple pentru limbajul C, [lex][2] și [yacc][3].


CPL Issues
==========

## Lab01
* Se folosește de regulă extensia .l, nu .lex, see [these docs][4]

## Lab02
* După simbolul start nu poate fi specificat tipul la care se mapează, see [docs][5]

[1]: https://www.gnu.org/software/bison/manual/html_node/Algorithm.html#Algorithm
[2]: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
[3]: http://www.lysator.liu.se/c/ANSI-C-grammar-l.html
[4]: http://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html
[5]: http://dinosaur.compilertools.net/bison/bison_6.html#SEC55]

