## HIGH PRIORITY
- [ ] Fixes in NcursesTab items (HIGH!!!)
- [x] Start porting config
- [x] start using gettext (FindGettext.cmake)
- [x] systab timerfd timer customizable
- [ ] Colors like ls (prepare patch for ncurses)
- [ ] fix valgrind issues -> lots of them are fixed by fixing NcursesTab...
- [x] fix leaving with ESC

## UI FIXES (NcursesTab)
- [x] Correctly print windows
- [x] SysTab -> use NCursesWindow!
- [x] QuestionWindow : NCursesWindow static class, window only shown when needed. It exposes a "askQuestion" method that will show it up and call wgetstr, returnsstring and hides itself.
- [x] modTab label -> TAB to switch
- [ ] tabs ->label: current modality

## generic
- [x] Do not create sysmodule (and syswin) if sysinfo_layout is empty
- [x] NcursesFM is a NcursesApplication, not NcursesUI

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
- [ ] Name() 
- [ ] Helper()

## Cmake
- [x] install needed files
- [x] create deb pkg! make package
