#ifndef __PARSER_H
#define __PARSER_H
#include <iostream>
#include <string.h>


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

//for nested tags
struct XMLNodeList
{
    int heap_size;
    int size;
    struct XMLNodeList** data;
};
struct XMLNode
{
    char* tag;
    char* innerText;
    XMLNode* parent;
    XMLAttributeList attributes;
    XMLNodeList children;
};

struct XMLDocument
{
    XMLNode* root;
};






XMLNode* XMLNodeNew(XMLNode* parent);
void XMLNodeFree(XMLNode* node);

int XMLDocumentLoad(XMLDocument* doc, const char* path);
void XMLDocumentFree(XMLDocument* doc);

void XMLAttributeFree(XMLAttribute* attr);
void XMLAttributeListInit(XMLAttributeList* list);
void XMLAttributeListAdd(XMLAttributeList* list, XMLAttribute* attr);


void XMLNodeListInit(XMLNodeList* list);
void XMLNodeListAdd(XMLNodeListAdd* list, XMLNode* node);

#endif









