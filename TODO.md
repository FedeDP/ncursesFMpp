## Module class
- [ ] InotifyModule (each FmTab has one)
- [ ] UiModule (getch)
- [ ] SystembarEvent (timerfd)
- [ ] InfoModule (to print an info)
- [ ] SignalModule
- [ ] DeviceModule
- [ ] ArchiveModule (password needed to decrypt

- [x] Interfaccia generica: getFd(), recv(), init(), destroy();

## Modality class
- [ ] Hashmap { pressedButton, Func }
- [ ] implementazione di tutte le funzioni per quella modality
- [ ] NcursesUI ha una hashmap di default con le funzioni condivise (eg: TAB per switchare modality e ESC per uscire)

## FmTab extends Window
- [ ] Modality &currentMod
- [ ] inotifyModule mod;

## Window class
- [ ] getRealCols/Rows
- [ ] wborder
- [ ] draw()
- [ ] update()
