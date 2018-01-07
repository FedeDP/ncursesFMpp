#ifndef MYNCURSESMENU_H
#define MYNCURSESMENU_H

#include <cursesm.h>
#include <log.hpp>

class MyTab : public NCursesMenu
{
public:
    MyTab(std::string title, std::string label, std::string mark,
                  int nlines, int ncols, int starty = 0, int startx = 0, bool active = false);
    void init();
    virtual int process(int c);
    virtual void setActive(bool active);
    
protected:
    void updateItems(std::string title = std::string());
    
    std::vector<NCursesMenuItem *> itemList;
    
private:
    std::string title;
    std::string label;
    std::string mark;
    bool active;
};

#endif // MYNCURSESMENU_H
