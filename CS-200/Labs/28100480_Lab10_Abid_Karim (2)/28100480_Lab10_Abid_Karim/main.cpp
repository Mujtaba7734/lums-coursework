#include "file.hpp"

// Constructor for File

File::File(string name) : name(name) {}

void File::open() 
{
    cout << "Opening file: " << this->name << endl;
}

void File::close() 
{
    cout << "Closing file: " << this->name << endl;
}

void File::displayInfo() const 
{
    cout << "File - Name: " << this->name << endl;
}

FileType File::getType() const 
{
    return FileType::UNKNOWN;
}

string File::getName() const 
{
    return this->name;
}


// Image class implementations

Image::Image(const string name, bool transparent): File(name) 
{
    transparent_background = transparent;
}

void Image::displayInfo() const 
{
    if (transparent_background == true)
    {
        cout << "Image File - Name: " << getName() << ", Transparent Background: Yes" << endl;
    } 
    else
    {
        cout << "Image File - Name: " << getName() << ", Transparent Background: No" << endl;
    }
}

bool Image::isTransparent() const 
{
    return transparent_background;
}

void Image::open() 
{
    cout << "Opening image file: " << getName() << endl;
}

void Image::close() 
{
    cout << "Closing image file: " << getName() << endl;
}

FileType Image::getType() const 
{
    return FileType::IMAGE;
}


// Video class implementations

Video::Video(const string name, int fps, int length): File(name)
{
    this->fps = fps;
    this->length = length;
}

void Video::displayInfo() const 
{
    cout << "Video File - Name: " << getName() << ", FPS: " << fps << ", Length: " << length << " minutes" << endl;  
}

int Video::getFPSCount() const 
{
    return this->fps;
}

int Video::getlengthCount() const 
{
    return this->length;
}

void Video::open() 
{
    cout << "Opening video file: " << getName() << endl;
}

void Video::close() 
{
    cout << "Closing video file: " << getName() << endl;
}

FileType Video::getType() const 
{
    return FileType::VIDEO;
}


// Directory class implementations

Directory::Directory(const string name) 
{
    this->name = name;
    files = NULL;
    num_files = 0; 
}

Directory::~Directory() 
{
    if (files != NULL)
    {
        for (int i =0; i < num_files; i++)
        {
            delete files[i];
        }
    }
    files = NULL;
}

void Directory::addFile(File* file) 
{
    file->open();
    File **newfiles = new File *[num_files + 1];
    for (int i = 0; i < num_files; i++)
    {
        newfiles[i] = files[i];
    }
    delete [] files;
    files = newfiles;  
    files[num_files] = file;
    file->close();
    num_files++; 
    
}

void Directory::removeFile(const string& filename) 
{
    int filesindex = -1;
    File **newfiles = new File *[num_files - 1];
    for (int i = 0; i < num_files; i++)
    {
        if (files[i]->getName() == filename)
        {
            filesindex = i;
            break;
        }
        newfiles[i] = files[i];
        
    }
    if (filesindex == -1)
    {
        return;
    }
    
    for (int i = filesindex; i < num_files; i++)
    {
        newfiles[i] = files[i + 1];
    }
     
    delete [] files;
    files = newfiles;
    num_files--;
}

void Directory::displayAll() const 
{
    cout << "Directory: " << this->name << endl;
    for (int i =0; i < num_files; i++)
    {
        files[i]->displayInfo();
    }
}

string Directory::getName() const 
{
    return name;
}

File* Directory::searchFile(const string& filename) 
{
    int filesindex = 0;
    for (int i = 0; i < num_files; i++)
    {
        if (files[i]->getName() == filename)
        {
            filesindex = i;
            break;
        }
    }

    return files[filesindex];
}

void Directory::displayFilesByType(FileType type) const 
{
    cout << "Directory: " << this->name << endl; 
    for (int i =0; i < num_files; i++)
    {
        if (files[i]->getType() == type)
        {
            files[i]->displayInfo();
        }
    }
}
//  counting all is giving 100 .. but showing 88