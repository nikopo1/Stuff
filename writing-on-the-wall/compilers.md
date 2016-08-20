Compilers
=========

## flex

Useful macros:
* `char *yytext` - atomul curent
* `int yyleng` - lungimea atomului curent
* `REJECT` - respinge match-ul curent, caută altă regulă care potrivește


## bison

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
* Se folosește de regulă extensia `.l`, nu `.lex`, see [these docs][4]. Btw, dacă fișierul se
termină în `.l`, poți să dai direct `make lexer` pentru fișierul `lexer.l`.
* IMHO, nu prea se pune accent pe întoarcerea codurilor lexicale de-aici
* Funcția `main` din laborator nu are return type specificat, lipsește `return 0;` la final.

## Lab02

### General
* După directive `%start` nu poate fi specificat tipul la care se mapează, see [docs][5]
* bison nu suportă declararea mai multor simboluri de start cu directiva `%start`, see [docs][6].
  Nu știu dacă yacc sau altă implementare suportă. Poți declara în schimb în pseudo-simbol de
  start care să multiplexeze între mai multe simboluri de start.
* Aș reformula fraza "Conflictele pot fi fie shift/reduce, fie reduce/reduce." în:
  Conflictele pot fi de două tipuri:
    - reduce/reduce - există două reguli din gramatică care pot fi aplicate în același timp
    - shift/reduce - se poate aplica o regulă care reduce un set de simboluri, dar dacă s-ar avansa
      cu parsarea ar fi aplicabilă altă regulă
  Cred că merită discutat fiecare tip de conflict într-o secțiune separată, cu link la exemplele din
  manualul de bison ([reduce/reduce][7], [shift/reduce][8] - btw, ar trebui puse ca referințe
  pentru că exemplele din lab sunt copy-paste și translate). Apoi, explicat la fiecare tip de
  conflict cum se rezolvă.
* "Exercițiu: Încercați să rezolvați conflictul shift/reduce pentru dangling else folosind reguli
  de precedență." - cred că mai bine ar fi un exercițiu de laborator.
* Cred că ar trebui explicat un pic cum funcționează algoritmul de parsare din bison și stiva de
  parsare. Nu știu dacă asta ar trebui făcut în Lab02 sau Lab03, though. Mie mi s-au părut foarte
  utile explicațiile din [pagina despre algoritm din manual][1].

### Typos & other
* Virgulă între subiect și predicat "Și noi, vom genera tot parsere LALR.".
* Pluralul de la simbol este simboluri, nu simboli
* s/întroarcem/întoarcem/g
* s/Bison nu verifica/Bison nu verifică/g
* s/simbolii următori regulii/simbolurile următoare din regulă/g
* s/urmator/următor/g
* s/neambigua/neambiguă/g
* s/precedența crește în jos/precedența crește odată cu fiecare grup nou definit/g

## Lab03

* s/încât sa poată/încât să poată/g
* s/trebuie sa/trebuie să/g
* s/in/în/g, s/In/În/g
* s/Introducere in CMake/Introducere în CMake/g
* De curiozitate, de ce folosiți CMake în loc de Makefile?


[1]: https://www.gnu.org/software/bison/manual/html_node/Algorithm.html#Algorithm
[2]: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
[3]: http://www.lysator.liu.se/c/ANSI-C-grammar-l.html
[4]: http://pubs.opengroup.org/onlinepubs/009695399/utilities/make.html
[5]: http://dinosaur.compilertools.net/bison/bison_6.html#SEC55]
[6]: https://www.gnu.org/software/bison/manual/html_node/Multiple-start_002dsymbols.html
[7]: https://www.gnu.org/software/bison/manual/html_node/Reduce_002fReduce.html
[8]: https://www.gnu.org/software/bison/manual/html_node/Shift_002fReduce.html

