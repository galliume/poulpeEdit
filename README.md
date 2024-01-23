# PoulpeEdit

PoulpeEdit is the level editor that comes with [PoulpeEngine](https://github.com/galliume/poulpeEngine)

### This project is a never ending educationnal exercice about C and GTK4.

[State of the project](https://github.com/users/galliume/projects/5)

[In video](https://www.youtube.com/watch?v=C7p9z6LhAig&list=PL4-Os8BWDCPmZt5HvJrSo6QDHkD9J4fJF)

<img src="https://github.com/galliume/poulpeEdit/blob/main/screenshots/poulpeEdit.gif" width="800" height="600">

## Build it

### GTK for Windows
[Download GTK](https://gitlab.gnome.org/GNOME/gtk)

Then in the developer command prompt shell load vcvars64.bat (should be here:)
```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
```

Then build it from the source (update ${PoulpeEditFolder} accordingly)
```
meson setup --prefix=${PoulpeEditFolder}/vendor/gtk _build -Dmedia-gstreamer=disabled -Dwin32-backend=true -Dvulkan=disabled
meson compile -C _build
meson install -C _build
```

Then build PoulpeEdit
```
chmod +x ./bin/plpEdit.sh
./bin/plpEdit.sh --config --build
```