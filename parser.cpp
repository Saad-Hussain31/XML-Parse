#pragma once
#include <iostream>
#include <string>
// using namespace std;


class XMLDocument
{
public:
    char* source;
    int XMLDocument_load(XMLDocument* doc, const char* path)
    {
        FILE* file = fopen(path, "r");
        if(!file) 
        {
            std::cerr << "could not load file." << path << std::endl;
            return false;
        }
        fseek(file,0,SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        doc->source = (char*)malloc(sizeof(char) * size+1);   
        fread(doc->source,1,size,file);
        fclose(file);
        doc->source[size] = '\0';
        return true;
    }


    void XMLDocument_free(XMLDocument* doc)
    {
        free(doc->source);
    }

};

// int XMLDocument_load(XMLDocument* doc, const char* path);
// void XMLDocument_free(XMLDocument* doc);
// int XMLDocument_load(XMLDocument* doc, const char* path)
// {
//     FILE* file = fopen(path, "r");
//     if(!file) 
//     {
//         std::cerr << "could not load file." << path << std::endl;
//         return false;
//     }
//     fseek(file,0,SEEK_END);
//     int size = ftell(file);
//     fseek(file, 0, SEEK_SET);
//     doc->source = (char*)malloc(sizeof(char) * size+1);   
//     fread(doc->source,1,size,file);
//     fclose(file);
//     doc->source[size] = '\0';
//     return true;
// }


// void XMLDocument_free(XMLDocument* doc)
// {
//     free(doc->source);
// }



