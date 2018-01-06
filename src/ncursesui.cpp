#include "ncursesui.hpp"
#include "questiontab.hpp"

NcursesUI::NcursesUI(bool hasSysLine) : Module(STDIN_FILENO) {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_RED, -1);
    ESCDELAY = 25;
    raw();
    
    //     init_modalities(); // to be passed to tabs!
    tabs.push_back(std::make_unique<NcursesTab>(hasSysLine));
    tabs.push_back(std::make_unique<NcursesTab>(hasSysLine, 0, COLS / 2, false));
    modTab = std::make_unique<NcursesModTab>(hasSysLine);
    
    activeWin = tabs.front().get();
}

int NcursesUI::recv() {
    int ret = 0;
    std::wstring answer;
    std::wstring question = L"Is this a question?";
    
    int c = activeWin->getch();
    switch (c) {
        case 9: // tab to switch!
            activeWin->setActive(false);
            if (activeWin == modTab.get()) {
                activeWin = lastActive;
                activeWin->setActive(true);
            } else {
                lastActive = activeWin;
                activeWin = modTab.get();
                activeWin->setActive(true);
            }
            break;
        case 27: /* ESC to exit */
            ret = -1;
            break;
        case '?':
            QuestionTab::getInstance().askQuestion(question, answer);
            break;
        case KEY_LEFT: // left to switch tab only if we're not choosing modality
            if (activeWin != modTab.get()) {
                if (activeWin != tabs.front().get()) {
                    activeWin->setActive(false);
                    activeWin = tabs.front().get();
                    activeWin->setActive(true);
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        case KEY_RIGHT: // right to switch tab only if we're not choosing modality
            if (activeWin != modTab.get()) {
                if (activeWin != tabs.back().get() && tabs.size() == 2) {
                    activeWin->setActive(false);
                    activeWin = tabs.back().get();
                    activeWin->setActive(true);
                } 
                break;
            }
            // DO not break so it will be redirected to default case
        default:
            activeWin->process(c);
            break;
    }
    activeWin->refresh();
    return ret;
}
