#include "DocFile.h"
#include "External/zip.h"
#include "External/pugixml.hpp"
#include <cctype>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <iostream>

DocFile::DocFile(): a_fileOpen(false){}

DocFile::DocFile(QString filePath): a_filePath(filePath), a_fileOpen(false){}

void DocFile::setFilePath(QString filePath){
    a_filePath = filePath;
    std::cout << "file path set" << std::endl;
}

QString DocFile::getFilePath(){
    return a_filePath;
}

bool DocFile::openFile(){
    if(a_fileOpen){
        return false;
    }

    void *buf = NULL;
    std::size_t bufSize;

    std::cout << "started" << std::endl;

    zip_t *zip = zip_open(a_filePath.toStdString().c_str() , ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
    std::cout << "zip opened" << std::endl;

    if(!zip){
        a_fileOpen = false;
        return false;
    }

    a_fileOpen = true;

    zip_entry_open(zip, "word/document.xml");
    zip_entry_read(zip, &buf, &bufSize);

    zip_entry_close(zip);
    zip_close(zip);

    a_xmlDoc.load_buffer(buf, bufSize);
    free(buf);

    std::cout << "opened" << std::endl;

    return true;
}

bool DocFile::saveFile(){
    if(!a_fileOpen){
        return false;
    }

    xml_string_writer writer;
    a_xmlDoc.print(writer);


    std::string originalFile = a_filePath.toStdString();
    std::string tempFile = originalFile + ".tmp";

    zip_t *newZip = zip_open(tempFile.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    zip_entry_open(newZip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(newZip, buf, strlen(buf));
    zip_entry_close(newZip);

    zip_t *originalZip = zip_open(originalFile.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    int totalFilesInZip = zip_total_entries(originalZip);

    for(int i = 0; i < totalFilesInZip; i++){
        zip_entry_openbyindex(originalZip, i);
        const char *name = zip_entry_name(originalZip);

        if (std::string(name) != std::string("word/document.xml")){
            void *entryBuf;
            size_t entryBufSize;
            zip_entry_read(originalZip, &entryBuf, &entryBufSize);

            zip_entry_open(newZip, name);
            zip_entry_write(newZip, entryBuf, entryBufSize);
            zip_entry_close(newZip);

            free(entryBuf);
        }

        zip_entry_close(originalZip);
    }

    zip_close(originalZip);
    zip_close(newZip);

    remove(originalFile.c_str());
    rename(tempFile.c_str(), originalFile.c_str());

    return true;
}

int DocFile::findReplace(QString target){
    if(!a_fileOpen){
        return 0;
    }

    recursiveSearch(a_xmlDoc.children());
    return 1;
}
