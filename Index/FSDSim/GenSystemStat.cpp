#include "GenSystemStat.h"

GenSystemStat::GenSystemStat()
{
    cout << __PRETTY_FUNCTION__ << ": Generating statistics." <<  endl;
    //Crawler crawler;
    //m_fileInfoVec = crawler.getFileList(path);

    FileTypes *fileTypes = FileTypes::instance();
    m_typeCategoryMap = fileTypes->getTypeCategoryMap();

    // name stat is generated from the XML & the dictionary.
    typeStat();
    sizeStat();
    // TODO: date stat
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TYPE  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void GenSystemStat::typeStat()
{
    cout << __PRETTY_FUNCTION__ << ": Generating file type statistics." << endl;

    map <string, int> typeMap;

    for (FileInfo fileInfo : m_fileInfoVec)
    {
        // Filter out the unknown types
        try
        {
            m_typeCategoryMap.at(fileInfo.m_type);
        }
        catch (const std::out_of_range& oor)
        {
            #ifdef DBG_DATA
            cerr << "out_of_range:" << fileInfo.m_type << endl;
            #endif
           continue;
        }

        map<string, int>::iterator it = typeMap.find(fileInfo.m_type);
        if ( it != typeMap.end() )
            typeMap[fileInfo.m_type] = it->second + 1;
        else
        typeMap[fileInfo.m_type] = 1;
    }

    // Write

    string path = DIR_STAT_FILE;
    ofstream typeStat(path + "TypeStat.csv");
    if (!typeStat.is_open())
    {
        cerr << __PRETTY_FUNCTION__  << "File not open for writing." << endl;
        return;
    }
    for (auto typeFreq : typeMap)
    {
        typeStat << typeFreq.first;
        typeStat << ",";
        typeStat << typeFreq.second;
        typeStat << endl;
    }
    typeStat.close();
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SIZE  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void GenSystemStat::sizeStat()
{
    cout << __PRETTY_FUNCTION__ << ": Generating file size statistics." << endl;

    string path = DIR_STAT_FILE;
    ofstream sizeStat_Document  (path + "SizeStat_Document.csv");
    ofstream sizeStat_Audio     (path + "SizeStat_Audio.csv");
    ofstream sizeStat_Video     (path + "SizeStat_Video.csv");
    ofstream sizeStat_Image     (path + "SizeStat_Image.csv");
    ofstream sizeStat_Database  (path + "SizeStat_Database.csv");
    ofstream sizeStat_Executable(path + "SizeStat_Executable.csv");
    ofstream sizeStat_Web       (path + "SizeStat_Web.csv");
    ofstream sizeStat_System    (path + "SizeStat_System.csv");
    ofstream sizeStat_Compressed(path + "SizeStat_Compressed.csv");
    ofstream sizeStat_DiskImage (path + "SizeStat_DiskImage.csv");
    ofstream sizeStat_Developer (path + "SizeStat_Developer.csv");
    ofstream sizeStat_Backup    (path + "SizeStat_Backup.csv");
    ofstream sizeStat_Misc      (path + "SizeStat_Misc.csv");

    for (FileInfo fileInfo : m_fileInfoVec)
    {
        string type = fileInfo.m_type;
        int64_t size  = fileInfo.m_size; // log(fileInfo.m_size);
        string category;
        try
        {
            category = m_typeCategoryMap.at(type);
        }
        catch (const std::out_of_range& oor)
        {
            #ifdef DBG_DATA
            cout << "out_of_range:" << type << ", " << category << endl;
            #endif
            continue;
        }

        if (category.compare("Document") == 0)
            sizeStat_Document << size << endl;
        else if (category.compare("Audio") == 0)
            sizeStat_Audio << size << endl;
        else if (category.compare("Video") == 0)
            sizeStat_Video << size << endl;
        else if (category.compare("Image") == 0)
            sizeStat_Image << size << endl;
        else if (category.compare("Database") == 0)
            sizeStat_Database << size << endl;
        else if (category.compare("Executable") == 0)
            sizeStat_Executable << size << endl;
        else if (category.compare("Web") == 0)
            sizeStat_Web << size << endl;
        else if (category.compare("System") == 0)
            sizeStat_System << size << endl;
        else if (category.compare("Compressed") == 0)
            sizeStat_Compressed << size << endl;
        else if (category.compare("DiskImage") == 0)
            sizeStat_DiskImage << size << endl;
        else if (category.compare("Developer") == 0)
            sizeStat_Developer << size << endl;
        else if (category.compare("Backup") == 0)
            sizeStat_Backup << size << endl;
        else if (category.compare("Misc") == 0)
            sizeStat_Misc << size << endl;
    }

    sizeStat_Document.close();
    sizeStat_Audio.close();
    sizeStat_Video.close();
    sizeStat_Image.close();
    sizeStat_Database.close();
    sizeStat_Executable.close();
    sizeStat_Web.close();
    sizeStat_System.close();
    sizeStat_Compressed.close();
    sizeStat_DiskImage.close();
    sizeStat_Developer.close();
    sizeStat_Backup.close();
    sizeStat_Misc.close();
}
