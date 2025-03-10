Project 1 - LAN PARTY 2024

Proiectul meu este conceput pentru a gestiona o competiție LanParty, cu generare și procesare de meciuri, determinare câștigători și clasarea echipelor din final.

Structura proiectului

Fișierul pentru date de intrare 'c.in' conține un vector de 5 elemente, cu valoarea 1 sau 0, care descrie dacă un task este realizabil în momentul citirii și rulării checker-ului.

Fișierul pentru date de intrare 'd.in' conține numărul de echipe, iar pentru fiecare echipă definește numărul de players, numele echipei, numele și punctele pentru fiecare player. 

Fișierele pentru date de ieșire 'r.out' trebuie să fie formatate după regulile din checker și să conțină numele echipelor și datele despre echipele câștigătoare.

Checker-ul rulează comanda ./lanParty c.in d.in r.out pentru verificarea corectitudinii algoritmilor.

Proiectul este constituit din mai multe fișiere cu diferite funcționalități:
- lanParty.c -> conține main-ul(cu manipularea fișierelor) prin care se citesc într-o variabilă sarcinile din "c.in" și se execută task-urile corespunzătoare valorii din parametru, dar și funcțiile pentru fiecare task:
    - primulTask -> citește datele de intrare(nume echipe, nume, prenume și puncte jucător) pentru a crea liste de echipe și jucători, apoi scrie în fișierul de ieșire numele echipelor.
    - alDoileaTask -> reduce numărul de echipe la cea mai mare putere a lui 2, mai mică decât numărul inițial de echipe, apoi le scrie în fișierul de ieșire.
    - alTreileaTask -> creează o coadă de meciuri între echipe, determină câștigătorii și învinșii după ce afișează meciul, punându-i în două stive; adaugă punct primului jucător din fiecare echipă, șterge stiva de învinși, repopulează coada și continuă acest ciclu până rămân doar 8 echipe; stochează aceste echipe într-o stivă pentru utilizare ulterioară; numele câștigătorilor pentru fiecare rundă sunt scrise în fișierul de ieșire.
    - alPatruleaTask -> creează un arbore de căutare binar BST pentru sortarea celor 8 echipe rămase în ordine descrescătoare a scorurilor lor; echipele sortate sunt scrise în fișierul de ieșire, apoi arborele este șters.
    - alCincileaTask -> inserează cele 8 echipe finaliste într-un arbore AVL în ordine descrescătoare, apoi scrie echipele de pe nivelul 2 în fișierul de ieșire și șterge arborele.

- stive.c, functii-ajutatoare.c, cozi.c, liste.c, trees.c și stive.h, functii-ajutatoare.h, cozi.h, liste.h, trees.h -> fișiere sursă și bibliotecile aferente cu structuri specifice listelor, cozilor, arborilor, stivelor și funcții ajutătoare în rezolvarea task-urilor, speciale pentru implementarea fiecăruia. 

Informații descoperite
- cum să manipulez datele mai ușor.
- cum funcționează un checker.
- cum creez un Makefile și un ReadMe.

Spațiu pentru îmbunătățire:
- optimizarea algoritmilor folosiți pentru lucrul cu fișiere de dimensiuni mult mai mari.
- adăugarea unor 'câmpuri' suplimentare pentru stocarea unor alte tipuri de date.

Licență
Acest program este distribuit sub Licența MIT.
