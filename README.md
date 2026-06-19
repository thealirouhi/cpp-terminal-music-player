# ♫ Terminal Music Player

A **terminal-based music player** written in **C++17** as the final project (CA4) for the Advanced Programming course.  
Plays MP3 files via [miniaudio](https://miniaud.io/), manages a music library from CSV, and supports playlists, search, sort, and filter — entirely through a text-based TUI.

---

## Naming Convention

This project follows the guidelines from the *Clean Code* reference sheet:

| Category         | Style              | Example                     |
|------------------|--------------------|-----------------------------|
| Class names      | `PascalCase`       | `MusicLibrary`, `CsvLoader` |
| Function names   | `camelCase`        | `getCurrentSong()`, `loadSongs()` |
| Variable names   | `lower_snake_case` | `song_count`, `file_path`   |
| Constant names   | `UPPER_SNAKE_CASE` | `BOX_WIDTH`, `EXPECTED_FIELDS` |

All source files include a comment block at the top declaring this convention.

---

## Project Structure

```
Music_Player/
├── src/
│   ├── main.cpp                  ← Entry point (9 lines)
│   ├── Song.h / Song.cpp         ← Song data model
│   ├── Playlist.h / Playlist.cpp ← Playlist model (does NOT own Songs)
│   ├── MusicLibrary.h / .cpp     ← Owns Songs, filter/search
│   ├── CsvLoader.h / .cpp        ← Parses Data/library.csv
│   ├── M3uLoader.h / .cpp        ← Parses Data/Playlists/*.m3u
│   ├── Player.h / .cpp           ← State machine + miniaudio playback
│   ├── ConfigManager.h / .cpp    ← Reads/writes Data/settings.cfg
│   ├── Screen.h                  ← Abstract base (pure virtual)
│   ├── MainMenu.h / .cpp         ← Main navigation screen
│   ├── NowPlayingScreen.h / .cpp ← Now playing + controls
│   ├── PlaylistListScreen.h/.cpp ← List/switch playlists
│   ├── PlaylistViewScreen.h/.cpp ← Browse, sort, search, play
│   ├── FilterScreen.h / .cpp     ← Filter by artist/album
│   ├── SettingsScreen.h / .cpp   ← Change playback mode
│   ├── UIRenderer.h / .cpp       ← Terminal box-drawing output
│   ├── InputHandler.h / .cpp     ← Validated input reading
│   ├── Application.h / .cpp      ← Orchestrator, main loop
│   └── miniaudio.h               ← Single-header audio library (v0.11.25)
├── Data/
│   ├── library.csv               ← 20 songs with metadata
│   ├── settings.cfg              ← Created at runtime (key=value)
│   ├── Playlists/*.m3u           ← 4 playlists
│   └── music/*.mp3               ← 20 MP3 files
├── AP_CA4.pdf                    ← Assignment description
├── .gitignore
└── README.md
```

---

## Features

### Data Loading
- **CSV library** — reads `Data/library.csv` with 7 fields per song (title, artist, album, genre, year, duration, file path)
- **M3U playlists** — loads `.m3u` files from `Data/Playlists/`, matches file paths to the library
- **Settings** — saves/restores `active_playlist`, `playback_mode`, and `last_song` to `Data/settings.cfg`

### Playback Controls
| Key | Action       |
|-----|--------------|
| `p` | Play / Pause |
| `s` | Stop         |
| `n` | Next song    |
| `b` | Previous song|
| `q` | Back to menu |

### Playback Modes
| Mode          | Behavior                                      |
|---------------|-----------------------------------------------|
| `NO_REPEAT`   | Play in order, stop at end                    |
| `REPEAT_ONE`  | Repeat the current song forever               |
| `REPEAT_ALL`  | Loop the entire playlist                      |
| `SHUFFLE`     | Random order (avoids repeating the same song) |

### Browse Features
- **Sort** — by Title, Artist, Album, Year (ascending/descending)
- **Search** — case-insensitive search across title and artist
- **Filter** — filter the playlist by Artist or Album

### Error Handling
- Invalid menu input → "Invalid choice. Please try again."
- Non-numeric input → cin cleared and re-prompted
- Missing audio file → skipped, next song loaded
- Empty playlist → "Playlist is empty."
- Corrupted CSV/M3U lines → silently skipped with a warning
- **No crash under any circumstance**

---

## How to Build and Run

### Prerequisites
- **Compiler:** Apple Clang (or GCC) with C++17 support
- **Libraries:** None required — `miniaudio` is header-only and handles MP3/WAV/FLAC natively

### Build
```bash
cd Music_Player
g++ -std=c++17 src/*.cpp -o music_player
```

### Run
```bash
./music_player
```

> **Note:** The MP3 files are not tracked in git. If cloning fresh, place your `.mp3` files in `Data/music/` and ensure paths match `library.csv`.

---

## Screens Overview

| # | Screen         | Description |
|---|----------------|-------------|
| 1 | **Main Menu**  | Shows last played song. Navigate: Now Playing, Playlists, Browse, Settings, Quit |
| 2 | **Now Playing**| Displays current song metadata (title, artist, album, genre). Controls: p/n/b/s/q |
| 3 | **Playlists**  | Lists all playlists with song counts. Select a number to switch the active playlist |
| 4 | **Browse**     | Shows songs in the active playlist. Type a number to play, `s` to sort, `/` to search, `f` to filter |
| 5 | **Filter**     | Choose Artist or Album, then pick from the unique values in the current playlist |
| 6 | **Settings**   | Change playback mode: 1 = NO_REPEAT, 2 = REPEAT_ONE, 3 = REPEAT_ALL, 4 = SHUFFLE |

---

## Class Architecture

```
Application  (owns everything, main loop)
├── UIRenderer      — terminal box-drawing output
├── InputHandler    — validated user input
├── MusicLibrary    — owns all Song* objects
├── CsvLoader       — reads library.csv → creates Songs
├── M3uLoader       — reads .m3u files → creates Playlists
├── Player          — state machine + miniaudio
├── ConfigManager   — settings.cfg read/write
└── Screen[6]       — array of polymorphic screen objects
    ├── MainMenu
    ├── NowPlayingScreen
    ├── PlaylistListScreen
    ├── PlaylistViewScreen
    ├── FilterScreen
    └── SettingsScreen
```

### Key Ownership Rules
- **MusicLibrary** — allocates `Song*` on the heap; its destructor `delete`s them
- **Playlist** — stores `Song*` pointers only; its destructor does **NOT** delete songs
- **Application** — owns `Playlist*` objects (created by M3uLoader) and `Screen*` objects; deletes them in its destructor
- **Player** — has a pointer to the active `Playlist`, does not own it

### OOP Concepts Used
- **Encapsulation** — all data members are `private`, accessed via getters
- **Inheritance** — `Screen` (abstract base) → 6 concrete screen classes
- **Polymorphism** — `virtual void render() = 0`, `virtual void handleInput()`, virtual destructor
- **Abstraction** — pure virtual interface in `Screen`
- **Dynamic Memory** — heap allocation via `new` / `delete` for Songs, Playlists, and Screens
- **File I/O** — `ifstream`/`ofstream` for CSV, M3U, and settings.cfg
- **STL Containers** — `vector<Song*>`, `vector<Playlist*>`, `map<string, string>`
- **Error Handling** — `try/catch` for `stoi`, input validation, file open checks

---

## Data Files

### `Data/library.csv`
```
title,artist,album,genre,year,duration_sec,file_path
Hey You,Pink Floyd,The Wall,Progressive Rock,1979,278,Musics/01 Pink Floyd - Hey You.mp3
...
```
20 songs. Comma-separated, header row, one song per line.

### `Data/Playlists/*.m3u`
```
Musics/01 Pink Floyd - Hey You.mp3
Musics/02 Queen - We Are The Champions (Remastered 2011).mp3
...
```
One file path per line. Paths must match the `file_path` column in `library.csv`.

### `Data/settings.cfg`
```
active_playlist=rock_hits
playback_mode=SHUFFLE
last_song=Hey You — Pink Floyd
```
Created and managed by `ConfigManager`. Written on quit, read on startup.

---

## Team

| User | Role | Contributions |
|------|------|---------------|
| **Ali Rouhi** | Developer & Reviewer | CsvLoader, Playlist, M3uLoader, ConfigManager, UIRenderer, InputHandler, Application, main.cpp, README |
| **Yas** | Developer | Song, MusicLibrary, Player (miniaudio), all Screen subclasses |

---

## Dependencies

- [miniaudio](https://miniaud.io/) v0.11.25 — Public domain / MIT-0 licensed single-header audio library. Included in `src/miniaudio.h`. Handles MP3, WAV, and FLAC decoding with no external dependencies.
