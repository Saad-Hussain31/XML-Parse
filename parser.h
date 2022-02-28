#ifndef __PARSER_H
#define __PARSER_H
#include <iostream>
#include <string.h>


struct XMLAttribute
{
    char* key;
    char* value;
};


void XMLAttributeFree(XMLAttribute* attr);


struct XMLAttributeList
{
    int heap_size;
    int size; //size of num of eles
    XMLAttribute* data;
};

void XMLAttributeListInit(XMLAttributeList* list);
void XMLAttributeListAdd(XMLAttributeList* list, XMLAttribute* attr);


//for nested tags
struct XMLNodeList
{
    int heap_size;
    int size;
    struct XMLNodeList** data;
};

void XMLNodeListInit(XMLNodeList* list);
// void XMLNodeListAdd(XMLNodeListAdd* list, XMLNode* node);
void XMLNodeListAdd(XMLNodeList* list, struct _XMLNode* node);
void XMLNodeListFree(XMLNodeList* list);

struct XMLNode
{
    char* tag;
    char* inner_text;
    XMLNode* parent;
    XMLAttributeList attributes;
    XMLNodeList children;
};

XMLNode* XMLNodeNew(XMLNode* parent);
void XMLNodeFree(XMLNode* node);
XMLNode* XMLNodeChild(XMLNode* parent, int index);


struct XMLDocument
{
    XMLNode* root;
};

int XMLDocumentLoad(XMLDocument* doc, const char* path);
void XMLDocumentFree(XMLDocument* doc);

#endif









