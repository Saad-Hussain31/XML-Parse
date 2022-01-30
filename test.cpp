#include "parser.cpp"

/* a prototype of what I want to do */
int main()
{
    XMLDocument doc;
    if (doc.XMLDocument_load(&doc, "test.xml"))
    {
        std::cout << doc.source;
        doc.XMLDocument_free(&doc);
    }
        
    return 0;
}