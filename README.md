# Snake

Prosta gra Snake napisana w C++ z wykorzystaniem biblioteki `ncurses`, działająca w terminalu. Projekt zawiera prosty system okienek z możliwością przesuwania i obsługą zdarzeń oraz samą grę Snake z rosnącym ogonem, pojawiającymi się owocami, pauzą i ekranem pomocy.


## Funkcjonalności

- Gra działająca w terminalu z grafiką tekstową dzięki ncurses
- Mechanika klasycznej gry Snake:
  - Sterowanie strzałkami
  - Zbieranie owoców i wydłużanie ogona
  - Wykrywanie kolizji z własnym ogonem (koniec gry)
  - Przechodzenie przez krawędzie planszy
- Interaktywne okna i linia wejściowa tekstu
- Tryb pauzy oraz ekran pomocy z instrukcjami
- System okien z ramkami i obsługą grupy widoków 


## Wymagania

- System Linux/Unix lub kompatybilny terminal
- Kompilator `g++` z obsługą C++11 lub nowszym
- Biblioteka `ncurses`
