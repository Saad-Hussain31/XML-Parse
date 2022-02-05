// #include "parser.h"
#include "parser.h"


/* a prototype of what I want to do */
int main()
{
    XMLDocument doc;
    if (XMLDocumentLoad(&doc, "test.xml"))
    {
        std::cout << doc.root->tag << ": " <<
        doc.root->innerText;
        XMLDocumentFree(&doc);
    }
        
    return 0;
}