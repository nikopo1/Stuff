Algoritmul de parsare folosit de Bison

parser stack - conține simbolurile găsit de parser, impreună cu valoarea semantică asociată
shifting - citirea unui token și inserarea lui pe stivă
reducing - aplicarea unei reguli

Regulile se aplică în momentul în care pe stivă există N simboluri care corespund unei anumite
reguli. Când se aplică o regulă, aceste simboluri sunt scoase de pe stivă, iar în locul lor se
inserează un nou simbol, care corespunde părții din stânga a unei reguli.

Exemple pentru limbajul C, [http://www.lysator.liu.se/c/ANSI-C-grammar-y.html][lex] și
[http://www.lysator.liu.se/c/ANSI-C-grammar-l.html][yacc].

[1] https://www.gnu.org/software/bison/manual/html_node/Algorithm.html#Algorithm

CPL Issues:
* Lab01 - se folosește de regulă extensia .l, nu .lex





 * Lab02 - după simbolul start nu poate fi specificat tipul la care se mapează
