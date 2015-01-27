#ifndef FLEAUX_EDITOR_HH_
#define FLEAUX_EDITOR_HH_

#include <cstdlib>
#include "ieditor.hh"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "../deps/libsdnb/include/sdnb/gap_vector.hh"

using namespace std;
using namespace SDNB;

namespace Fleaux
{
    class Editor;

    ostream& operator<<(ostream& os, const Editor& ed);
    istream& operator>>(istream& is, Editor& ed);

    class Cursor;

    class Editor : public IEditor
    {
        friend class Cursor;

        public:
            /* data members */
            size_t size;   

            /* constructor(s) & destructor(s) */
            Editor(void);
            Editor(const string& path);
            ~Editor(void);

            /* member functions */
            friend ostream& operator<<(ostream& os, const Editor& ed);
            friend istream& operator>>(istream& is, Editor& ed);
            void readFromFile(const string& path);
            void writeToFile(const string& path);
            ICursor* getCursor(void) { return (ICursor*)__cursor; };
            
        private:
            /* data members */
            Cursor* __cursor;
            GapVector<char>* __data;
    };

    class Cursor : public ICursor
    {
        public:
            /* constructor(s) & destructor(s) */
            Cursor(void) : __index(0), __x(0), __y(0), __editor(NULL) {};
            Cursor(Editor* ed);
            Cursor(const ICursor& curs);
            
            /* member functions */
            void insert(const string& input);
            void remove(int length);
            void replace(int length, const string& replacement);
            IEditor* getEditor(void) const { return (IEditor*)__editor; };
            size_t getIndex(void) const { return __index; };
            size_t getX(void) const { return __x; };
            size_t getY(void) const { return __y; };
            void move(int offsetX, int offsetY);



        private:
            /* data members */
            size_t __index;
            size_t __x;
            size_t __y;
            Editor* __editor;

            /* member functions */
            void __setXY(void);
            void __setIndex(void);
            void __moveX(int offset);
            void __moveY(int offset);
    };
}
#endif
