# Semestrálna úloha

## Ako aplikáciu ovládať:
V main.cpp sú premenné ROWS a COLS. Tie ovľádajú ako veľký bude výstupy obrázok. ROWS a COLS musia byť rovnaké číslo.
V main() funkcii je string s názvom folder_path do ktorého treba uložiť cestu k súboru s obrázkami.
Samotné obrázky vyžadujú aby boli typu wang spolu s appropriate indexami.


_**Algoritmus**_
* načítam si do vektora všetky obrázky zo súboru
* vytvorím si šachovnicu (dvojrozmerné pole) a na každé "čierne" políčko priradím náhodné čislo v rozsahu počtu wang tiles
* prejdem postupne všetky biele políčka a spýtam sa u každého na jeho susedov a ci na políčko od susedov smeruje nejaká cesta
* priradím podľa predchádzajúceho kroku index
* prejdem celú šachovnicu a políčko po políčku nahádžem do vektora
* vykreslím postupne z vektora celý obrázok
* na vykreslenie používam OpenCV

## príklad wang tiles
![](https://github.com/Tach3/ALD_semestralka_Spurny/blob/main/Capture.PNG)
