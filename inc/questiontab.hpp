#ifndef QUESTIONTAB_H
#define QUESTIONTAB_H

#include <cursesp.h>
#include <log.hpp>

class QuestionTab : public NCursesPanel
{
public:
    static QuestionTab& getInstance() {
        static QuestionTab instance;
        return instance;
    }
    
    void askQuestion(std::wstring& question, std::wstring& answer);
    
private:
    QuestionTab();

};

#endif // QUESTIONTAB_H
