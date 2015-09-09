## Simple_OpenGL_Slim

### Opis:

Projekt przedstawia przykładowe wykorzystanie grafiki 3D w OpenGL.</br>
Stworzony dla zajęć **Grafika komputerowa i wizualizacja** w 2015 roku.</br>
Wersja pierwsza, większa znajduje się pod linkiem: [LINK](https://github.com/kaczla/Simple_OpenGL_Game)
</br>
</br>
Proste wczytywanie i rysowanie pojedyńczych obiektów 3D.
</br>
</br>

### Testowane na:

**Ubuntu 15.04**
</br>
x64
</br>
g++ (Ubuntu 4.9.2-10ubuntu13) 4.9.2
</br>
</br>
**Windows 7 SP1**
</br>
x64
</br>
[MinGW + MSYS](http://www.mingw.org/)
</br>
g++ (GCC) 4.8.1
</br>
</br>

### Wymagania:

1) **Zaktualizaowane sterowniki graficzne**</br>
2) **[SDL2](https://www.libsdl.org)**</br>
3) **[GLEW](http://www.glew.sourceforge.net)**</br>
4) **[GLM](http://www.glm.g-truc.net)**</br>
5) **[DevIL](http://www.openil.sourceforge.net)**</br>
6) **[Assimp](http://assimp.sourceforge.net)**</br>

#### Pakiety dla Ubuntu:

sudo apt-get install libsdl2-dev glew-utils libglew-dev libglm-dev libdevil-dev libassimp-dev
</br>
</br>

### Budowanie:

Zbudować poleceniem **make** w głównym katalogu repozytorium.
</br>
</br>

### Uruchomienie:

Uruchomić aplikację **game.app**\*\* w głównym katalogu repozytorium ( wcześniej budując ! ).
</br>
\*\* Dla systemu Windows, należy uruchomić aplikację **game.exe**.
</br>
</br>

### Sterowanie:

**W** / **Strzałka w górę** - Poruszanie się do porzodu (przed siebie)
</br>
**S** / **Strzałka w dół** - Poruszanie się do tyłu
</br>
**A** / **Strzałka w lewo** - Poruszanie się w lewo
</br>
**D** / **Strzałka w prawo** - Poruszanie się w prawo
</br>
**SPACJA** - Poruszanie się do góry
</br>
**C** / **Lewy CTRL** - Poruszanie się w dół
</br>
**ESC** - wyjście z gry
</br>
</br>

### Krótka dokumentacja:

Znajduje się w katalogu **doxygen/html/index.html**.
</br>
</br>

### Dodawanie kolejnych elementów 3D:

Każdy obiekt musi posiadać (w folderze **data**):
<ul>
<li>plik .obj</li>
<li>teksture główną</li>
<li>teksture spektralną</li>
</ul>

Dodać ww pliki do pliku **data.init** w katalogu **data** według kolejności:

> NAZWA_OBIEKTU PLIK_.OBJ PLIK_GŁÓWNEJ_TEKSTURY PLIK_SPEKTRALNEJ_TEKSTURY WSPÓŁRZEDNE_X WSPÓŁRZEDNE_Y WSPÓŁRZEDNE_Z

np.

> cube cube.obj cube.jpg cube_spec.jpg 2.5 0.5 -2.5

</br>
</br>

### Screenshot:

</br>
</br>

### Uwagi:

Część plików .obj i tekstur zostało pobranych z [tf3dm.com](http://tf3dm.com).
</br>
</br>
