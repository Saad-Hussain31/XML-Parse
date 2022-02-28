#include <iostream>
#include <string.h>
#include "parser.h"


void XMLAttributeFree(XMLAttribute* attr)
{
    free(attr->key);
    free(attr->value);
}

void XMLAttributeListInit(XMLAttributeList* list)
{
    list->heap_size = 1; //number of elements we can put in
    list->size = 0; //number of elements we have.
    list->data = (XMLAttribute*) malloc(sizeof(XMLAttribute) * list->heap_size);
}

//to add attributes to list
void XMLAttributeListAdd(XMLAttributeList* list, XMLAttribute* attr)
{
    while(list->size >= list->heap_size) 
    {
        list->heap_size *= 2;
        list->data =  (XMLAttribute*) realloc(list->data, sizeof(XMLAttribute) * list->heap_size);
    }
    list->data[list->size++] = *attr;
}


void XMLNodeListInit(XMLNodeList* list)
{
    list->heap_size = 1; 
    list->size = 0;
    list->data = (XMLNodeList**) malloc(sizeof(XMLNode*) * list->heap_size);

}

//list of pointers to XMLNode
void XMLNodeListAdd(XMLNodeList* list, XMLNode* node)
{
    //keep growing the amount of memory available
    while(list->size >= list->heap_size) 
    {
        list->heap_size *= 2;
        list->data =  (XMLNodeList**) realloc(list->data, sizeof(XMLNode*) * list->heap_size);
    }
    list->data[list->size++] = (XMLNodeList*)node;
}



XMLNode* XMLNodeNew(XMLNode* parent)
{
    XMLNode* node = (XMLNode*) malloc(sizeof(XMLNode));
    node->tag = NULL;
    node->inner_text = NULL;
    node->parent = parent;
    XMLAttributeListInit(&node->attributes);
    XMLNodeListInit(&node->children);
    if(parent)
        XMLNodeListAdd(&parent->children, node);//if parent, add itself to children's list
    return node;
}

void XMLNodeFree(XMLNode* node)
{
    if(node->tag)
        free(node->tag);
    if(node->inner_text)
        free(node->inner_text);
    for(int i=0; i < node->attributes.size; i++)
        XMLAttributeFree(&node->attributes.data[i]);
}

XMLNode* XMLNodeChild(XMLNode* parent, int index)
{
    return (XMLNode*)parent->children.data[index];
}

int XMLDocumentLoad(XMLDocument* doc, const char* path)
{
    FILE* file = fopen(path, "r");
    if(!file) 
    {
        std::cerr << "could not load file." << path << std::endl;
        return false;
    }
    fseek(file,0,SEEK_END); //total nums of chars
    int size = ftell(file);
    // std::cout << size;
    fseek(file, 0, SEEK_SET); //setting pos indicator to start of file
    char* buff = (char*)malloc(sizeof(char) * size+1);// +1 for extra null char.
    // char* buff = (char*) new XMLNode; 
    fread(buff,1,size,file);
    fclose(file);
    buff[size] = '\0';

    doc->root = XMLNodeNew(NULL);
    char lex[256];
    int lexi = 0;
    int i =0;
    XMLNode* currentNode = NULL;
    while(buff[i] != '\0')
    {
        if(buff[i] == '<') //beginning of node
        {
            lex[lexi] = '\0';

	    /* setting inner_text */
            if(lexi > 0)//if len is > 0 then there is some text
            {
                if(!currentNode) //if currnode is null then that text is outside tag
                {
                    std::cout << "Text outside of document\n";
                    return false;
                }
                currentNode->inner_text = strdup(lex);
                lexi = 0;
            }

            /* setting end of node */
            if(buff[i+1] == '/')
            {
                i+=2;
                while(buff[i] != '>') //keep building lex untill hit >
                    lex[lexi++] = buff[i++];
                lex[lexi] = '\0';// put \0 to omplete the str

                if(!currentNode) //checking if its the start tag or end
                {
                    std::cerr << "Already at the root\n ";
                    return false; 
                }
                if(strcmp(currentNode->tag, lex))
                {
                    fprintf(stderr, "Mismatched tags (%s != %s)\n", currentNode->tag, lex); //currNode tag isnt same as whats in lex
                    return false;
                }
		
		//when done with currNode, move to its parent
                currentNode = currentNode->parent;
                i++;
                continue;
            }

	    /* setting currentNode */
            if(!currentNode) //set to parent/root when current node is null
                currentNode = doc->root;
            else   
                currentNode = XMLNodeNew(currentNode); //creating a newnode with cuuNode as its parent
            
            //getting beginning of tag (loop i.e anything between <>)
            i++;

            XMLAttribute currAttr = {0,0};
            while(buff[i] != '>') //end of tag symbol 
            {
                lex[lexi++] = buff[i++];
            // lex[lexi] = '\0'; //completes 1st str inside tag
            // currentNode->tag = strdup(lex); //heap allocating tag's text inside node's tag field

                //tag name
                if(buff[i] == ' ' && !currentNode->tag)
                {
                    lex[lexi] = '\0';
                    currentNode->tag = strdup(lex);
                    lexi = 0;
                    i++;
                    continue;
                }

                //attribute key
                if(buff[i] == '=')
                {
                    lex[lexi] = '\0';
                    currAttr.key = strdup(lex);
                    lexi = 0;
                    continue;
                }

                //attribute value
                if(buff[i] == '"')
                {
                    if(!currAttr.key)//if key is null then quotes are in wrong place.
                    {
                        std::cerr << "Value has no key \n";
                        return false;
                    }

                    lexi =0;
                    i++;//incr to work with value's string

                    while(buff[i] != '"') //till reach end of value's string
                        lex[lexi++] = buff[i++];
                    lex[lexi] = '\0';
                    currAttr.value = strdup(lex);
                    XMLAttributeListAdd(&currentNode->attributes, &currAttr);
                    currAttr.key = NULL;
                    currAttr.value = NULL;
                    lexi = 0;
                    i++;
                    continue;

                }
            }

            /*resetting lexer */
            lexi =0;
            i++;
            continue;
        }
        else //keep appending from buf to lex
        {
            lex[lexi++] = buff[i++];
        }
    }

    return true;
}


void XMLDocumentFree(XMLDocument* doc)
{
    XMLNodeFree(doc->root);
}
