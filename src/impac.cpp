    #include <string>
    #include <iostream>
    #include <dirent.h>
    #include <Magick++.h>
    using namespace std; 
    using namespace Magick; 

    int main(int argc, const char** argv)
    {
    if (argc != 2) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        return 0;
    }

    // initialize lists of images and their dimensions
    InitializeMagick(*argv);
    vector<Image> images;
    vector<int> widths; 
    vector<int> heights;

    // read the given directory for images
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (argv[1])) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] == '.') continue;
            Image img;
            // read image using magick
            img.read( ent->d_name );

            // get width and height in pixels
            int width = img.columns();
            int height = img.rows();        

            // save image and dimensions in vectors    
            widths.push_back(width);
            heights.push_back(height);
            images.push_back(img);
            printf ("%s: %d x %d \n", ent->d_name, width, height);
            // printf ("%s \n", ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("Failed opening directory");
        return EXIT_FAILURE;
    }

    return 0;
    }