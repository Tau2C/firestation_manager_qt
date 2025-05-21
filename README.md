# Aplikacja do zarządzania bazą danych OSP

Aplikacja desktopowa oparta o bibliotekę Qt, umożliwiająca zarządzanie bazą danych Ochotniczej Straży Pożarnej (OSP). Pozwala na dodawanie, edytowanie oraz usuwanie informacji o strażakach, badaniach lekarskich i szkoleniach.

---

## Funkcjonalności

- Przeglądanie listy strażaków, badań i szkoleń
- Dodawanie nowych rekordów do bazy danych
- Edytowanie istniejących danych
- Usuwanie wybranych rekordów
- Intuicyjny interfejs graficzny oparty o Qt

---

## Wymagania

- Qt 6.x (zalecana najnowsza wersja)
- CMake (jeśli budujesz projekt spoza Qt Creator)
- Kompilator C++ zgodny z Qt (np. MSVC, GCC, Clang)
- Biblioteka [libpqcxx](https://github.com/jtv/libpqxx) (do obsługi PostgreSQL z C++)
- Docker (do uruchomienia bazy danych lokalnie)
- PostgreSQL zainstalowany lokalnie (port 5432) lub uruchomiony przez Docker

---

## Instalacja i uruchomienie

### 1. Klonowanie repozytorium

```sh
git clone https://github.com/Tau2C/firestation_manager_qt.git
cd firestation_manager_qt
git submodule update --init --recursive
```

### 2. Konfiguracja bazy danych

Możesz uruchomić bazę danych PostgreSQL za pomocą Dockera:

```sh
docker compose up -d postgres
```

Baza danych będzie dostępna lokalnie pod adresem `localhost:5432`.

Jeśli korzystasz z lokalnej instalacji PostgreSQL załaduj schemat:

```sh
psql -U postgres -d postgres -f db/01_database.sql
```

### 3. Budowanie aplikacji

#### Budowanie z użyciem Qt Creator

1. Otwórz plik projektu (`CMakeLists.txt`) w Qt Creator.
2. Zbuduj i uruchom aplikację za pomocą przycisku "Run".

#### Budowanie z użyciem CMake

1. Zainstaluj Qt oraz skonfiguruj ścieżkę do Qt w systemie lub edytorze (np. przez rozszerzenie Qt dla VS Code).
2. Upewnij się, że masz zainstalowany CMake oraz libpqcxx.
3. W katalogu głównym projektu uruchom:

   ```sh
   cmake -B build
   cmake --build build
   ```

4. Plik wykonywalny znajdziesz w katalogu `build`.

---

## Konfiguracja bazy danych

- Baza danych PostgreSQL musi być uruchomiona lokalnie na urządzeniu, na którym działa aplikacja, i być dostępna pod adresem `localhost:5432`.
- Schemat bazy danych znajduje się w pliku `db/01_database.sql`.
- Przykładowe dane w pozostałych plikach w folderze `db/`.

---

## Technologie

- Qt C++
- libpqcxx (obsługa PostgreSQL z poziomu C++)
- Docker (opcjonalnie, do uruchomienia bazy danych)
- PostgreSQL

---

## Wkład

Wszelkie błędy oraz propozycje nowych funkcji zgłaszaj poprzez Issues i Pull Requesty.

---

## Licencja

Projekt dostępny na licencji MIT.

---

## Kontakt

W razie pytań lub problemów, prosimy o kontakt poprzez Issues na GitHubie.
