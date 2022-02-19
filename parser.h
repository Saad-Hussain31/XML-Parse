#ifndef __PARSER_H
#define __PARSER_H
#include <iostream>
#include <string.h>

struct XMLNode
{
    char* tag;
    char* innerText;
    XMLNode* parent;
};

struct XMLDocument
{
    XMLNode* root;
};



XMLNode* XMLNodeNew(XMLNode* parent);
void XMLNodeFree(XMLNode* node);

int XMLDocumentLoad(XMLDocument* doc, const char* path);
void XMLDocumentFree(XMLDocument* doc);

#endif









