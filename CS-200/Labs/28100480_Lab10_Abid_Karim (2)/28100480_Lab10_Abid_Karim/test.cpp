#include <iostream>
#include <string>
#include "main.cpp"
using namespace std;

// ----------- TEST CASES -  DO NOT EDIT --------------------------

#include <fstream>

bool compareFiles(const string your_output, const string test_output){
    ifstream your_stream(your_output);
    ifstream test_stream(test_output);

    if(!your_stream.is_open()){
        cerr<<"Error: Could not open your output file: "<<your_output<<endl;
        return false;
    }

    if(!test_stream.is_open()){
        cerr<<"Error: Could not open test output file: "<<test_output<<endl;
        return false;
    }

    string your_line, test_line;
    int line_number = 0;

    while(getline(test_stream, test_line)){
        getline(your_stream, your_line);
        line_number++;

        if(your_line != test_line){
            cerr<<"\nMismatch at line: "<<line_number<<endl;
            cerr<<"Your file output line: "<<your_line<<endl;
            cerr<<"Test file output line: "<<test_line<<endl;
            return false;
        }
    }

    return true;
}

//PART A TEST CASES

int testFileClasses() {
    int marks = 0;

    cout << "\033[35mTesting Files initialization:\033[0m ";

    File* file = new File("dummy");
    File* img = new Image("Logo.png", true);
    File* vid = new Video("Movie.mp4", 30, 120);

    if(img->getName() == "Logo.png" && vid->getName() == "Movie.mp4"){
        marks += 8;
        cout << "8/8\n\n";
    }
    else{
        cout << "Failed files initialization 0/8\n\n";
    }

    cout << "\033[35mTesting File open and close:\033[0m ";
    try {
        ofstream f("your_virtual.txt", ios::out);
        streambuf* oldCoutBuf = cout.rdbuf();
        cout.rdbuf(f.rdbuf());

        file->open();
        file->close();
        img->open();
        img->close();
        vid->open();
        vid->close();
        
        file->displayInfo();
        img->displayInfo();
        vid->displayInfo();

        cout.rdbuf(oldCoutBuf);
        f.close();

        if(!compareFiles("your_virtual.txt", "test_output/test_virtual.txt")){
            throw "opeen and close";
        }

        marks += 12;
        cout<<"12/12\n\n";
    } 
    catch(const char *e){
        cout << "Failed "<<e<<" 0/12\n\n";
    }

    return marks;
}

//PART B TEST CASES

int testDirectory() {
    int marks = 0;

    try{
        Directory dir("TestDirectory");

        File* img = new Image("Logo.png", true);
        File* vid1 = new Video("Movie1.mp4", 30, 120);
        File* vid2 = new Video("Movie2.mp4", 20, 100);

        cout << "\033[35mTesting file addition:\033[0m ";
        try{
            ofstream f("your_add.txt", ios::out);
            streambuf* oldCoutBuf = cout.rdbuf();
            cout.rdbuf(f.rdbuf());

            
            dir.addFile(img);
            dir.addFile(vid1);
            dir.addFile(vid2);

            dir.displayAll();

            cout.rdbuf(oldCoutBuf);
            f.close();

            if(!compareFiles("your_add.txt", "test_output/test_add.txt")){
                throw "file addition";
            }

            marks += 28;
            cout<<" 28/28\n";
        }
        catch(const char* e){
            cout<<"Failed "<<e<<" 0/28\n\n";
        }

        cout << "\033[35mTesting file removal:\033[0m ";
        try{
            dir.removeFile("Notes.txt");
            dir.removeFile("Logo.png");

            ofstream f("your_remove.txt", ios::out);
            streambuf* oldCoutBuf = cout.rdbuf();
            cout.rdbuf(f.rdbuf());

            dir.displayAll();

            cout.rdbuf(oldCoutBuf);
            f.close();

            if(!compareFiles("your_remove.txt", "test_output/test_remove.txt")){
                throw "file removal";
            }

            marks += 28;
            cout <<"28/28\n";
        }
        catch(const char* e){
            cout<<"Failed "<<e<<" 0/28\n\n";
        }

        cout << "\033[35mTesting file search:\033[0m ";
        try {
            File* file2 = dir.searchFile("Movie1.mp4");
            File* file3 = dir.searchFile("NonExistent.png");

            if(file3 != nullptr){
                throw "file removal";
            }

            ofstream f("your_search.txt", ios::out);
            streambuf* oldCoutBuf = cout.rdbuf();
            cout.rdbuf(f.rdbuf());

            file2->displayInfo();

            cout.rdbuf(oldCoutBuf);
            f.close();

            if(!compareFiles("your_search.txt", "test_output/test_search.txt")){
                throw "file search";
            }

            marks += 12;
            cout <<"12/12\n";
        } 
        catch (const char* e) {
            cout << "Failed " << e << " 12/12\n";
        }

        cout << "\033[35mTesting display by file type:\033[0m ";
        try {
            ofstream f("your_display_by_type.txt", ios::out);
            streambuf* oldCoutBuf = cout.rdbuf();
            cout.rdbuf(f.rdbuf());

            dir.displayFilesByType(FileType::VIDEO);

            cout.rdbuf(oldCoutBuf);
            f.close();

            if (!compareFiles("your_display_by_type.txt", "test_output/test_display_by_type.txt")) {
                throw "display by type";
            }

            marks += 12;
            cout << "12/12\n";
        } 
        catch (const char* e) {
            cout << "Failed " << e << " 0/12\n";
        }
    }
    catch(const char* e){
        cout << "Failed\n";
        return 0;
    }

    return marks;
}

int main() {
    cout << "\033[1m\033[36m\nTesting File Management System:\033[0m\n\n";
    int total = 0;

    total += testFileClasses();
    total += testDirectory();

    cout << "\n\033[1m\033[35mTotal:\033[0m " << total << "/100\n\n";
    return 0;
}

