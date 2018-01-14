## HIGH PRIORITY
- [ ] Fixes in NcursesTab items (HIGH!!!)
- [ ] Create a MyMenuItem instead of using NCursesMenuItem
- [ ] switch to scandir
- [ ] Colors like ls (prepare patch for ncurses)

## UI FIXES (NcursesTab)
- [ ] tabs ->label: current modality
- [ ] askQuestion cannot be blocking or we will miss external signals, Udisks2 and other dbus modules signals...

## Module class
- [ ] InotifyModule (each FmTab has one)
- [x] UiModule (getch)
- [x] SysModule (timerfd)
- [ ] InfoModule (to print an info)
- [ ] SignalModule
- [ ] DeviceModule
- [ ] ArchiveModule (password needed to decrypt)

## Modality class
- [ ] Hashmap { pressedButton, Func }
- [ ] Name() 
- [ ] Helper()
