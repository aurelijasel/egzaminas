# Teksto analizės programa

Ši programa leidžia:
- nuskaityti tekstą iš failo,
- suskaičiuoti žodžių pasikartojimus,
- sudaryti žodžių kryžminių nuorodų (cross-reference) lentelę,
- surasti URL adresus tekste,
- rezultatus išvesti į failus arba terminalą.

Programa skirta pademonstruoti asociatyvių konteinerių (std::map, std::set)
bei std::string panaudojimą teksto analizės užduotyse.

## Programos veikimas

Programa nuskaito vartotojo nurodytą tekstinį failą eilutė po eilutės.

### Žodžių apdorojimas
- Pašalinami skyrybos ženklai.
- Ignoruojami skaičiai.
- Žodžiai paverčiami mažosiomis raidėmis.
- Palaikomos lietuviškos raidės (naudojama lt_LT.UTF-8 lokalė).
- Skaičiuojami tik tie žodžiai, kurie turi bent vieną raidę.

Programa suskaičiuoja, kiek kartų kiekvienas žodis pasikartoja tekste.
Į rezultatų failą išvedami tik tie žodžiai, kurie pasikartojo daugiau nei vieną kartą.

### Cross-reference lentelė
Kiekvienam žodžiui papildomai saugoma informacija:
- kiek kartų jis pasikartojo,
- kuriose teksto eilutėse buvo paminėtas.

Į cross-reference lentelę įtraukiami tik daugiau nei vieną kartą pasikartojantys žodžiai.

### URL adresų paieška
Programa tekste ieško URL adresų naudodama regex.

Atpažįstami URL formatai:
- http://...
- https://...
- www.pavyzdys.lt
- pavyzdys.lt
- saitas.xyz

Rasti URL adresai:
- saugomi be pasikartojimų,
- vartotojo pasirinkimu išvedami į terminalą arba į failą.

## Rezultatų failai

Programa sugeneruoja šiuos failus:

- zodziu_skaicius.txt  
  Žodis ir jo pasikartojimų skaičius (tik > 1)

- zodziu_eilute.txt  
  Žodis ir eilučių numeriai, kuriose jis pasirodė

- url_sarasas.txt  
  Rasti URL adresai (jei pasirinkta išvestis į failą)

### Rezultatų pavyzdžiai

**zodziu_skaicius.txt**
```
Zodis               Skaicius  
------------------------------               
anglų               2                 
apie                8
.
.
.
```
**zodziu_eilute.txt**
```
Zodis               Eilutes
----------------------------------------
anglų              {73, 79}
apie               {24, 44, 53, 82, 85}
.
.
.
```
**url_sarasas.txt**
```
Rasti URL:
nerija.lt
visitneringa.com
.
.
.
```

### Pilni rezultatų pavyzdžiai

Pilni rezultatų failai bus pateikti atskirame aplanke, kuriame
analizuojamas tekstas yra paimtas iš Vikipedijos straipsnio
apie Kuršių neriją.

Aplanke bus pateikti šie failai:
- zodziu_skaicius.txt
- zodziu_eilute.txt
- url_sarasas.txt

Šie failai parodo pilną programos veikimą su realiu,
didelės apimties tekstu.

## Naudojimosi instrukcija

### Programos atsisiuntimas
1. Parsisiųsti CMake (ne senesnę nei 3.25.0 versiją):  
   https://cmake.org/download/
2. Atsisiųsti CMakeLists.txt, run.bat, .cpp ir .h failus iš GitHub.
3. Kompiuteryje sukurti aplanką, pvz. „cmaketest“.
4. Į „cmaketest“ įkelti:
   - CMakeLists.txt
   - run.bat
   - cmake.exe
5. „cmaketest“ aplanke sukurti aplankus:
   - src (įkelti .cpp failus)
   - include (įkelti .h failus)

### Kompiliavimas ir paleidimas

Terminale vykdyti komandas:
```
cmake .\CMakeLists.txt
```
```
cmake --build .
```
```
cd Debug
```
```
.\failo_rusiavimo_programa.exe
```

### Programos paleidimas
1. Paleidus programą, terminale bus paprašyta įvesti failo pavadinimą.
2. Programa apdoroja tekstą ir sugeneruoja rezultatų failus.
3. Jei randami URL adresai, vartotojas pasirenka:
  - T – URL išvesti terminale
  - F – URL išvesti į failą
