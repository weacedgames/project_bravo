#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image
{
public:
    int image_width;
    int image_height;
    int nrChannels;

    unsigned char* data;

    int assetImageID;

    Image(std::string const &texture_filePath, int setImageID)
    {
        this->assetImageID = setImageID;

        stbi_set_flip_vertically_on_load(true);
        
        this->data = stbi_load( texture_filePath.c_str(), &this->image_width, &this->image_height, &this->nrChannels, 0);

        if(this->data)
        {
            stbi_image_free(this->data);
        }
        else
        {
            std::cout << "ERROR::IMAGE:Failed_TO_LOAD\n" << std::endl;
        }
    };
};


#endif