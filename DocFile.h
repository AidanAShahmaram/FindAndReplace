#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QStringList>
#include "External/pugixml.hpp"
#include <iostream>

class DocFile{
public:
    DocFile();

    DocFile(QString filePath);

    void setFilePath(QString filePath);

    QString getFilePath();

    bool openFile();

    bool saveFile();

    int findReplace(QString target);



private:
    QString a_filePath;
    pugi::xml_document a_xmlDoc;
    bool a_fileOpen;


    struct xml_string_writer : pugi::xml_writer {
        std::string result;

        virtual void write(const void *data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    };

    typedef void(*nodeFunction)(std::string);
    void recursiveSearch(pugi::xml_object_range<pugi::xml_node_iterator> children, std::string target, nodeFunction func){
        for(pugi::xml_node child : children){

            recursiveSearch(child.children(), target, func);
        }
    }

};

#endif // DOCUMENT_H
