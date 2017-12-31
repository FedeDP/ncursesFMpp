#ifndef MYNCURSESMENU_H
#define MYNCURSESMENU_H

#include <cursesm.h>
#include <log.hpp>

class MyNcursesMenu : public NCursesMenu
{
public:
    MyNcursesMenu(std::string title, std::string label, std::string mark, 
                  int nlines, int ncols, int starty = 0, int startx = 0);
    void init();
    virtual int process(int c);
    virtual void setEnabled(bool enabled);
    
protected:
    std::vector<NCursesMenuItem *> itemList;
    
private:
    std::string title;
    std::string label;
    std::string mark;
};

#endif // MYNCURSESMENU_H
