#include "questiontab.hpp"

QuestionTab::QuestionTab(): NCursesPanel(3, cols(), lines() - 6, 0) {
    curs_set(0);
    box();
}

void QuestionTab::askQuestion(std::wstring& question, std::wstring& answer) {
    show();
    echo();
    curs_set(1);
        
    // cleanup old question
    printw(1, 1, "%*s", cols() - 2, "");
    // print question in bold
    CUR_attron(A_BOLD);
    printw(1, 1, "> %.*ls ", cols(), question.c_str());
    CUR_attroff(A_BOLD);
    refresh();
    
    wchar_t top[cols() - 2 - question.size() + 1];
    memset(top, 0, sizeof(top));
    wgetn_wstr(p->win, (wint_t *)top, sizeof(top) - 1);
    answer = std::wstring(top);
    
    curs_set(0);
    noecho();
    hide();
}
