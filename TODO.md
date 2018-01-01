## UI FIXES (NcursesTab)
- [x] Correctly print windows
- [ ] Colors like ls (for now it seems not possible)
- [ ] Fixes in NcursesTab
- [ ] SysTab -> use NCursesMenu items instead of directly computing where to print each string

## Module class
- [ ] InotifyModule (each FmTab has one)
- [ ] UiModule (getch)
- [x] SysModule (timerfd) -> better approach may be?
- [ ] InfoModule (to print an info)
- [ ] SignalModule
- [ ] DeviceModule
- [ ] ArchiveModule (password needed to decrypt)

- [x] Interfaccia generica: getFd(), recv(), init(), destroy();

## NcursesTab
- [ ] Modality &currentMod
- [ ] inotifyModule mod;

## Modality class
- [ ] Hashmap { pressedButton, Func }
