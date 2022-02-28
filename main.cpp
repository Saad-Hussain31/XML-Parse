#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* a skeleton of what I want to do */
int main()
{
    XMLDocument doc;
    if (XMLDocumentLoad(&doc, "test.xml"))
    {
        /*
        // std::cout << doc.root->tag << ": " <<
        // doc.root->inner_text;
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
        // printf("%s: %s\n", moreNode->tag, moreNode->inner_text);
        std::cout << moreNode->tag << moreNode->inner_text;
        XMLNode* anotherNode = XMLNodeChild(doc.root,1);
        // printf("%s: %s\n", anotherNode->tag, anotherNode->inner_text);
        std::cout << anotherNode->tag << anotherNode->inner_text;
        XMLDocumentFree(&doc);
    }

        
    return 0;
}
