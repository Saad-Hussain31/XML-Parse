#include "parser.h"

/* a skeleton of what I want to do */
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