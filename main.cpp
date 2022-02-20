#include "parser.h"

/* a skeleton of what I want to do */
int main()
{
    XMLDocument doc;
    if (XMLDocumentLoad(&doc, "test.xml"))
    {
        // std::cout << doc.root->tag << ": " <<
        // doc.root->innerText;
        std::cout << "Attributes: \n ";
        XMLNode node = *doc.root;
        for(int i =0; node.attributes.size; i++)
        {
            XMLAttribute attr = node.attributes.data[i];
            // std::cout << attr.key << attr.value;
            printf(" %s => \"%s\"\n", attr.key, attr.value); //loading attributes from tag, into the node.
        }
        XMLDocumentFree(&doc);
    }
        
    return 0;
}