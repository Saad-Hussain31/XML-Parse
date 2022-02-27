#include "parser.h"

/* a skeleton of what I want to do */
int main()
{
    XMLDocument doc;
    if (XMLDocumentLoad(&doc, "test.xml"))
    {
        /*
        // std::cout << doc.root->tag << ": " <<
        // doc.root->innerText;
        std::cout << "Attributes: \n ";
        XMLNode node = *doc.root;
        for(int i =0; node.attributes.size; i++)
        {
            XMLAttribute attr = node.attributes.data[i];
            // std::cout << attr.key << attr.value;
            // attributes are loaded from tag into node 
            printf(" %s => \"%s\"\n", attr.key, attr.value); //loading attributes from tag, into the node.
        }
        XMLDocumentFree(&doc);
    } */   
        XMLNode* moreNode = XMLNodeChild(XMLNodeChild(doc.root,0),0);
        printf("%s: %s\n", moreNode->tag, moreNode->innerText);
        XMLNode* anotherNode = XMLNodeChild(doc.root,1);
        printf("%s: %s\n", anotherNode->tag, anotherNode->innerText);
        XMLDocumentFree(&doc);
    }

        
    return 0;
}