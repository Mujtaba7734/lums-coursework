#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <string>

using namespace std;

// Enum for FileType
enum class FileType {
    IMAGE,
    VIDEO,
    UNKNOWN
};

// Base class: File
class File {
    protected:
        string name;
    
    public:
        File(string name);
        virtual ~File() {}

        virtual void open();
        virtual void close();
        virtual void displayInfo() const;
        virtual FileType getType() const;
        string getName() const;
};

// Derived class: Image
class Image : public File {
    private:
        bool transparent_background;

    public:
        Image(const string name, bool transparent);
        void displayInfo() const override;
        bool isTransparent() const;
        void open() override;
        void close() override;
        FileType getType() const override;
};

// Derived class: Video
class Video : public File {
    private:
        int fps;
        int length;

    public:
        Video(const string name, int fps, int length);
        void displayInfo() const override;
        int getFPSCount() const;
        int getlengthCount() const;
        void open() override;
        void close() override;
        FileType getType() const override;
};

// Directory class
class Directory {
    private:
        string name;
        File** files;
        int num_files;

    public:
        Directory(const string name);
        ~Directory();
        void addFile(File* file);
        void removeFile(const string& filename);
        void displayAll() const;
        string getName() const;
        File* searchFile(const string& filename);
        void displayFilesByType(FileType type) const;
};

#endif // FILE_HPP
