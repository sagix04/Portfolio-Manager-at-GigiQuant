# README - Proiect: Analiza Datelor Financiare

**Nume:** Manuel Cerchiello  
**Grupa:** 314AA  
**Materie:** Proiectarea Algoritmilor (PA)

## Descriere Generală
Acest proiect implementează o serie de algoritmi în limbajul C pentru analiza și prelucrarea datelor financiare (prețuri ale acțiunilor pe piața bursieră). Scopul principal este modelarea informațiilor folosind structuri de date fundamentale (liste, stive, cozi, arbori și grafuri) și interacțiunea cu un API extern.

## Structura Proiectului și Rulare
Proiectul folosește un executabil principal care primește fișierele de intrare și ieșire ca argumente în linia de comandă.
Selectarea task-ului se face automat în funcție de numărul testului extras din calea fișierului de intrare (`argv[1]`).

## Detalii Implementare Task-uri

### Task 1: Analiza Sharpe Ratio
* **Structuri de date folosite:** Liste simplu înlănțuite.
* **Logică:** Datele sunt citite și stocate dinamic într-o listă. O funcție dedicată parcurge lista cu doi pointeri (`curent` și `urmator`) pentru a calcula randamentul zilnic. Ulterior, alte funcții de reducere calculează suma randamentelor și deviația standard pentru a returna indicele Sharpe.

### Task 2: Căutarea Arbitrajului
* **Structuri de date folosite:** Stive (LIFO) și Cozi (FIFO).
* **Logică:** Prețurile din cele 3 orașe/piețe sunt citite din fișier și introduse în 3 stive separate (ceea ce inversează ordinea inițială). Acestea sunt parcurse simultan pentru a identifica diferențe de preț (oportunități de arbitraj). Oportunitățile găsite sunt introduse într-o coadă (inserare la `rear`), garantând astfel că la afișare se va respecta ordinea cronologică corectă.

### Task 3: Corelarea Inversă
* **Structuri de date folosite:** Arbori Binari de Căutare (BST) și Liste simplu înlănțuite.
* **Logică:** Fiecare tranziție de preț de la o zi la alta dictează navigarea în arbore (dacă prețul crește, se avansează în copilul drept; dacă scade, în cel stâng). Frunzele arborelui conțin liste înlănțuite cu simbolurile acțiunilor care au urmat acel drum. Pentru a găsi corelațiile inverse, algoritmul recalculează traseul fiecărei acțiuni, dar navigând intenționat în direcția opusă (oglindită) și verifică dacă frunza destinație conține alte acțiuni.

### Task 4: Lanțuri Markov (Implementare Parțială)
* **Structuri de date folosite:** Grafuri orientate (implementate prin liste de adiacență).
* **Logică:** Datele continue sunt discretizate în stări unice (noduri) folosind un pas `d`. Se construiește un graf orientat în care muchiile reprezintă tranzițiile între aceste stări de preț, iar costul/frecvența este updatată la fiecare trecere. 
* *Notă:* Logica de construire a grafului și parsare a stărilor este implementată. Logica matematică pentru simularea lanțului Markov și calculul cu fracții ireductibile (CMMDC) nu a fost finalizată.

### Task 5: Integrare API Yahoo Finance (Bonus)
* **Biblioteci folosite:** `libcurl` și `cJSON`.
* **Logică:** Execută o cerere HTTP GET către Yahoo Finance pentru a prelua istoricul acțiunilor (ex: AAPL). Răspunsul este stocat dinamic folosind o funcție de callback (`realloc` pe pachetele de memorie primite). Textul JSON este apoi parsat pentru a extrage arborele de rezultate până la vectorul de prețuri "open". Datele obținute în timp real sunt apoi pasate funcției de la Task 1 pentru a le calcula indicele Sharpe.

## Observații
* Eliberarea memoriei alocate dinamic (noduri, liste, arbori, grafuri, handlere curl) se face riguros la finalul fiecărui task pentru a preveni memory leaks.
