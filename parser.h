#ifndef __PARSER_H
#define __PARSER_H
#include <iostream>
#include <string.h>

struct XMLNode
{
    char* tag;
    char* innerText;
    XMLNode* parent;
    XMLAttributeList attriutes;
};

struct XMLDocument
{
    XMLNode* root;
};

struct XMLAttribute
{
    char* key;
    char* value;
};

struct XMLAttributeList
{
    int heap_size;
    int size;
    XMLAttribute* data;
};


XMLNode* XMLNodeNew(XMLNode* parent);
void XMLNodeFree(XMLNode* node);

int XMLDocumentLoad(XMLDocument* doc, const char* path);
void XMLDocumentFree(XMLDocument* doc);

void XMLAttributeFree(XMLAttribute* attr);
void XMLAttributeListInit(XMLAttributeList* list);
void XMLAttributeListAdd(XMLAttributeList* list, XMLAttribute* attr);


#endif









