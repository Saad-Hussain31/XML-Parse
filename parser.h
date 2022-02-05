#pragma once
#include <iostream>
#include <string.h>
// XMLNode* XMLNode::XMLNodeNew(XMLNode* parent);

struct XMLNode
{
    char* tag;
    char* innerText;
    XMLNode* parent;
};
XMLNode* XMLNodeNew(XMLNode* parent);
void XMLNodeFree(XMLNode* node);

struct XMLDocument
{
    XMLNode* root;
};
int XMLDocumentLoad(XMLDocument* doc, const char* path);
void XMLDocumentFree(XMLDocument* doc);


XMLNode* XMLNodeNew(XMLNode* parent)
{
    XMLNode* node = (XMLNode*) malloc(sizeof(XMLNode));
    node->parent = parent;
    node->tag = nullptr;
    node->innerText = nullptr;
    return node;
}

void XMLNodeFree(XMLNode* node)
{
    if(node->tag)
        free(node->tag);
    if(node->innerText)
        free(node->innerText);
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
    fread(buff,1,size,file);
    fclose(file);
    buff[size] = '\0';

    doc->root = XMLNodeNew(NULL);
    char lex[256];
    int lexi = 0;
    int i =0;
    XMLNode* currentNode = nullptr;
    while(buff[i] != '\0')
    {
        if(buff[i] == '<')
        {
            lex[lexi] = '\0';
            if(lexi > 0)
            {
                if(!currentNode)
                {
                    std::cout << "Text outside of document\n";
                    return false;
                }
                currentNode->innerText = strdup(lex);
                lexi = 0;
            }

            //End of node
            if(buff[i+1] == '/')
            {
                i+=2;
                while(buff[i] != '>')
                    lex[lexi++] = buff[i++];
                lex[lexi] = '\0';
                if(!currentNode)
                {
                    std::cerr << "Already at the root\n ";
                    return false; 
                }
                if(strcmp(currentNode->tag, lex))
                {
                    std::cerr << "Mismathced tags " << currentNode->tag << "!=" << lex;
                    return false;
                }
                currentNode = currentNode->parent;
                i++;
                continue;
            }


            if(!currentNode)
                currentNode = doc->root;
            else   
                currentNode = XMLNodeNew(currentNode);
            i++;
            while(buff[i] != '>')
                lex[lexi++] = buff[i++];
            lex[lexi] = '\0';
            currentNode->tag = strdup(lex);

            //resetting lexer
            lexi =0;
            i++;
            continue;
        }
        else
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








