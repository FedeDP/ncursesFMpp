## HIGH PRIORITY
- [ ] Fixes in NcursesTab items
- [ ] Start porting config
- [ ] start using gettext (FindGettext.cmake)
- [ ] systab timerfd timer customizable
- [x] 1 cmdline option to set initial cwd
- [ ] Colors like ls (prepare patch for ncurses)

## UI FIXES (NcursesTab)
- [x] Correctly print windows
- [x] SysTab -> use NCursesWindow!
- [x] QuestionWindow : NCursesWindow static class, window only shown when needed. It exposes a "askQuestion" method that will show it up and call wgetstr, returnsstring and hides itself.
- [x] modTab label -> TAB to switch
- [ ] tabs ->label: current modality

## Module class
- [ ] InotifyModule (each FmTab has one)
- [ ] UiModule (getch)
- [x] SysModule (timerfd)
- [ ] InfoModule (to print an info)
- [ ] SignalModule
- [ ] DeviceModule
- [ ] ArchiveModule (password needed to decrypt)

- [x] Interfaccia generica: getFd(), recv(), init(), destroy();

## Modality class
- [ ] Hashmap { pressedButton, Func }

## Cmake
- [ ] install needed files
- [ ] create deb pkg! make package
