 #include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <Magick++.h>
#include "sprite_sheet.hpp"
#include "pack/first_fit.hpp" 
using namespace Magick; 
// default width and height for the sprite sheet
size_t DEFAUT_WIDTH = 1024;
size_t DEFAUT_HEIGHT = 1024;


// ./impac /pathfrom /pathto 
// ./impac /pathfrom /pathto 600 400
int main(int argc, const char** argv) {
    using namespace std;
    if (argc < 3) {
        cerr << "ERROR: Invalid number of arguments" << endl;
        return 0;
    }

    // initialize lists of images and their dimensions
    // this may not be needed
    InitializeMagick(*argv);
    vector<Image> images;
    // vector<int> widths; 
    // vector<int> heights;
    size_t maxwidth = 0;
    size_t maxheight = 0;

    // read the given directory for images
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (argv[1])) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            // skipping . and .. in the directory
            if (ent->d_name[0] == '.') continue;

            //initialize the image object
            Image img;

            // read image using magick
            string path = string(argv[1])+"/"+string(ent->d_name);
            cout << path << endl;
            img.read(path);

            // get width and height in pixels
            size_t width = img.columns();
            size_t height = img.rows();        

            // save image and dimensions in vectors    
            // widths.push_back(width);
            // heights.push_back(height);
            images.push_back(img);
            // printf ("%s: %d x %d \n", ent->d_name, width, height);

            // update the max height and width of the images
            if (maxwidth < width) maxwidth = width;
            if (maxheight < height) maxheight = height;
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("Failed opening directory");
        return EXIT_FAILURE;
    }

    // initialize sprite sheet dimension
    size_t sprite_width = max(maxwidth, DEFAUT_WIDTH);
    size_t sprite_height = max(maxheight, DEFAUT_HEIGHT);
    // size_t sprite_number = 0;
    if (argc == 5) {
        char *end1;
        char *end2;
        size_t arg_width = strtol(argv[3], &end1, 10);
        size_t arg_height = strtol(argv[4], &end2, 10);
        sprite_width = max(maxwidth, arg_width);
        sprite_height = max(maxheight, arg_height);
        if (*end1 != '\0' || *end2 != '\0') {
            std::cout << "invalid input.\n";
            return EXIT_FAILURE;
        }
    }
    

    // initialize sprite sheet
    auto sprite_sheet = impac::sprite_sheet{sprite_width, sprite_height};
    // start filling in sprite sheet
    for (auto it = images.begin(); it != images.end(); ++it) {
        // std::cout << ' ' << *it;
        sprite_sheet.add_sprite((*it).fileName(), *it);
    }
    Image result_image;
    if (sprite_sheet.pack(impac::pack::first_fit) == true) {
        result_image = sprite_sheet.impac::sprite_sheet::image(true);
    } else {
        cout << "Failed to pack image" << endl;
        return EXIT_FAILURE;
    }

    cout<< result_image.columns()<<"--"<<result_image.rows()<<endl;

    // write to image file
    string result_path = argv[2];
    auto image_name = result_path + "/spritesheet.jpg";
    result_image.write( image_name ); 

    // write to json file
    auto result_json = json(sprite_sheet);
    auto json_name = result_path + "/sprite_sheet.json";
    ofstream output (json_name, ofstream::out);
    output << result_json;
    output.close();


    // auto output = ofstream{json_name};
    // output << result_json;
    // output.close();
    
    return 0;
}